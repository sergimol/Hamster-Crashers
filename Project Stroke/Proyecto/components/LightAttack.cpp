#include "Obstacle.h"
#include "LightAttack.h"
#include "Stroke.h"
//#include "Gravity.h"
#include "Combos.h"
#include "FollowPlayer.h"
#include "Knockback.h"
#include "EnemyStun.h"
#include "AnimHamsterStateMachine.h"
#include "Swallow.h"
#include "AnimEnemyStateMachine.h"


LightAttack::LightAttack() :
	hms_(nullptr), tr_(nullptr), cooldown_(150), time_(sdlutils().currRealTime()), attRect_(), DEBUG_isAttacking_(false) {}

void LightAttack::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);
	anim_ = entity_->getComponent<AnimHamsterStateMachine>();
	assert(anim_ != nullptr);

	player_ = entity_->getComponent<EntityAttribs>()->getNumber();
}

void LightAttack::update() {
	//Deja de mostrar el collider
	if (sdlutils().currRealTime() > time_ + cooldown_ / 1.5) {
		DEBUG_isAttacking_ = false;
	}

	//Fin animacion
	if (anim_->getState() == HamStatesAnim::LIGHTATTACK)
	{
		if (entity_->getComponent<Animator>()->OnAnimationFrameEnd())
		{
			anim_->setAnimBool(HamStatesAnim::LIGHTATTACK, false);
		}
	}
}

bool LightAttack::CheckCollisions(const SDL_Rect& rectPlayer) {
	bool canHit = false;
	bool finCombo = false;

	//Cogemos a los enemigos
	auto& ents = entity_->getMngr()->getEnemies();

	bool hasHit = false;

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un enemigo...
		if (ents[i]->isActive() && ents[i]->hasGroup<Enemy>()) {
			//Cogemos el transform del enemigo
			auto eTR = ents[i]->getComponent<Transform>();
			auto eColRect = eTR->getRectCollide();

			Vector2D newPos = Vector2D(eColRect.x - cam.x, eColRect.y - cam.y);

			EntityAttribs* eAttribs = ents[i]->getComponent<EntityAttribs>();

			//Y comprobamos si colisiona y si no es invulnerable
			if (!eAttribs->checkInvulnerability() && Collisions::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, newPos, eColRect.w, eColRect.h)) {

				//Comprobamos si está en la misma Z o relativamente cerca

				if (eAttribs->ignoresMargin() || (abs((tr_->getRectCollide().y) - (eColRect.y)) < eAttribs->getMarginToAttack())) {

					if (!hasHit) {
						if (entity_->getMngr()->getHandler<Boss>() == ents[i] || entity_->getMngr()->getHandler<FinalBoss>() == ents[i]) {
							entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("handHit");
						}
						else if (entity_->hasComponent<WarCry>())
							entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("angelAttack");
						else
							entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("lighthit");
						hasHit = true;
					}

					Combos* combos = entity_->getComponent<Combos>();
					//A�adimos a los combos
					if (!canHit)
						finCombo = combos->checkCombo(0);

					//Comprobamos si está saltando
					bool isJumping = combos->isJumping();

					EntityAttribs* playerAttribs = entity_->getComponent<EntityAttribs>();
					int dmg = playerAttribs->getDmg();
					if (finCombo) {
						if (!canHit) playerAttribs->addCritProbability(0.02); //Aumentar probabilidad critico
						//Empujar y stunn al enemigo 
					}
					canHit = true;

					Swallow* playerSwallow = entity_->getComponent<Swallow>();

					//Si puede tragar, el enemigo tiene la mitad de la vida y es fin de combo - probabilidad de tragar
					if (!isJumping && finCombo && playerSwallow != nullptr && eAttribs->getLife() <= eAttribs->getMaxLife() / 2 && playerSwallow->canSwallow()) {
						eAttribs->recieveDmg(eAttribs->getLife()); // Esta puesto asi y no con setlife para que se vea la barra bajar
						playerAttribs->heal(playerSwallow->healQuantity());
						//Movida de animación
					}
					else {
						//Si puede envenenar
						if (playerAttribs->getCanPoison()) {
							// Número aleatorio para ver si envenena o no
							float i = sdlutils().rand().nextInt(1, 100);
							//Si i es menor que la probabilidad, envenena al enemigo
							if (i <= playerAttribs->getPoisonProb()) {
								eAttribs->poison();
							}
						}

						auto& enmStateM = ents[i]->getComponent<EnemyStateMachine>()->getState();

						auto grav = ents[i]->getComponent<Gravity>();

						if (isJumping && grav != nullptr) {
							//SALTO
							//if (z <= grav_->getFloor()) {
							//eTR->setVelZ(35.0/*tr_->getVelZ()*/);
							auto& velZ = eTR->getVelZ();
							if (!grav->gravLocked()) {
								velZ = 30.0f;
								grav->lockGrav(true);
							}

							grav->resetLockTimer();
						}

						if (enmStateM != EnemyStates::ENM_DEAD) {
							//Si tiene stun, se aplica
							EnemyStun* enmStun = ents[i]->getComponent<EnemyStun>();
							if (enmStun != nullptr && enmStun->isActive()) {



								//Si no estaba aturdido ya
								if (enmStateM != EnemyStates::ENM_STUNNED) {
									//Aturdimos al enemigo
									enmStateM = EnemyStates::ENM_STUNNED;
								}
								//Reiniciamos tiempo de stun
								enmStun->restartStunTime(finCombo);
							}
						}

						//ANIMACION DE HIT DEL ENEMIGO
						if (ents[i]->hasComponent<AnimEnemyStateMachine>())
							ents[i]->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, true);

						//Si tiene Knockback, se aplica
						Knockback* enmKnockback = ents[i]->getComponent<Knockback>();
						if (enmKnockback != nullptr) {
							//Damos la vuelta si es atacado por detras
							auto& enmFlip = eTR->getFlip();
							if (enmFlip == tr_->getFlip())
								enmFlip = !enmFlip;

							//Final del combo
							if (finCombo)
							{
								//ANIMACION DE STUNN DEL ENEMIGO
								ents[i]->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::STUNNED, true);

								//enmKnockback->setKnockbackDistance(50);
								enmKnockback->knockback(50);
								//enmKnockback->setKnockbackDistance(5);
							}
							else
								enmKnockback->knockback(3);
						}
					}
					//Cogemos probabilidad de crítico
					int criticProb = playerAttribs->getCriticProb();

					//Le restamos la vida al enemigo
					if (sdlutils().rand().nextInt(1, 10000) < criticProb * 100) {	//Comprobacion golpe crítico
						eAttribs->recieveDmg(dmg * playerAttribs->getCriticDmg());
						playerAttribs->resetCriticProb();
					}
					else
						eAttribs->recieveDmg(dmg);
				}
			}
		}
	}

	entity_->getMngr()->refreshEnemies();

	//COMPROBAMOS OBSTACULOS
	auto& obstacles = entity_->getMngr()->getObstacles();
	for (auto el : obstacles) {
		auto obstRect = el->getComponent<Transform>()->getRectCollide();
		Vector2D newPos = Vector2D(obstRect.x - cam.x, obstRect.y - cam.y);
		//Si colisiona el ataque
		if (Collisions::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h,
			newPos, obstRect.w, obstRect.h)) {
			//El objeto es golpeado y actua en consecuencia
			auto* obstObject = el->getComponent<Obstacle>();
			if (obstObject != nullptr)
				obstObject->hit();
		}
	}

	return canHit;
}

void LightAttack::render() {
	if (DEBUG_isAttacking_ && debug) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 212, 255, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
	}
}

void LightAttack::attack() {
	if (isActive() && !anim_->isOnAttack()) {

		auto state = hms_->getState();
		if (hms_->canAttack() && sdlutils().currRealTime() > time_ + cooldown_) {
			cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

			//auto sizeW = tr_->getW();
			//auto sizeH = tr_->getH();
			//auto& pos = tr_->getPos();
			auto pos = tr_->getRectCollide();

			auto range = entity_->getComponent<EntityAttribs>()->getAttackRange(); // Cogemos el rango del ataque


			attRect_.w = pos.w + pos.w * range;
			attRect_.h = pos.h + pos.h * range / 2;

			auto flip = tr_->getFlip();

			//Si esta flipeado...
			if (flip)
				//Le damos la vuelta al rect
				attRect_.x = pos.x - attRect_.w + pos.w / 2 - cam.x; //esto no funciona bien para el resto de entidades solo con sardinilla supongo, mas tarde investigamos
			else
				attRect_.x = pos.x + pos.w - pos.w / 2 - cam.x;

			attRect_.y = pos.y /*+ pos.h / 4*/ - cam.y;

			//Comprobamos si colisiona con alguno de los enemigos que tiene delante

			//Si se colisiona..
			if (!CheckCollisions(attRect_)) {
				//	//Suena el hit y le pega
				//	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("lighthit");
				//}
				////Si no colisiona..
				//else {
					//Suena el attackSound
				entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("attack");
				//Animacion de ataque normalito
				anim_->setAnimBool(HamStatesAnim::LIGHTATTACK, true);
			}


			DEBUG_isAttacking_ = true;
			time_ = sdlutils().currRealTime();
			entity_->getComponent<Stroke>()->increaseChance(1, false);
		}
	}
}
