#include "StrongAttack.h"
#include "Stroke.h"
#include "Combos.h"
#include "FollowPlayer.h"
#include "Knockback.h"
#include "EnemyStun.h"
#include "Swallow.h"
#include "AnimHamsterStateMachine.h"
#include "AnimEnemyStateMachine.h"



StrongAttack::StrongAttack() :
	hms_(nullptr), tr_(nullptr), cooldown_(400), time_(sdlutils().currRealTime()), attRect_(), DEBUG_isAttacking_(false),
	attackSound_(sdlutils().soundEffects().at("strong_attack")), hitSound_(sdlutils().soundEffects().at("hit")) {
}

void StrongAttack::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);

	player_ = entity_->getComponent<EntityAttribs>()->getNumber();
}

void StrongAttack::update() {
	if ((ih().playerHasController(player_) && ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_Y)) || ih().mouseButtonEvent()) {
	}
	//Deja de mostrar el collider
	if (sdlutils().currRealTime() > time_ + cooldown_ / 1.5) {
		DEBUG_isAttacking_ = false;
	}

	//Fin Animacion
	if (entity_->getComponent<AnimHamsterStateMachine>()->getState() == HamStatesAnim::STRONGATTACK)
	{
		if (entity_->getComponent<Animator>()->OnAnimationFrameEnd())
		{
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::STRONGATTACK, false);
		}
	}
}

bool StrongAttack::CheckCollisions(const SDL_Rect& rectPlayer, bool finCombo) {
	bool canHit = false;

	cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEnemies();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un enemigo...
		if (ents[i]->hasGroup<Enemy>()) {
			//Cogemos el transform del enemigo
			auto eTR = ents[i]->getComponent<Transform>();
			auto eColRect = eTR->getRectCollide();

			Vector2D newPos = Vector2D(eColRect.x - cam.x, eColRect.y - cam.y);

			EntityAttribs* eAttribs = ents[i]->getComponent<EntityAttribs>();

			//Y comprobamos si colisiona y si no es invulnerable
			if (!eAttribs->checkInvulnerability() && Collisions::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, newPos, eColRect.w, eColRect.h)) {
				
				//Comprobamos si está en la misma Z o relativamente cerca
				if (eAttribs->ignoresMargin() || (abs((tr_->getPos().getY() + tr_->getH()) - (eTR->getPos().getY() + eTR->getH())) < MARGINTOATTACK)) {

					EntityAttribs* playerAttribs = entity_->getComponent<EntityAttribs>();
					int dmg = playerAttribs->getDmg();
					if (finCombo) {
						if (!canHit) playerAttribs->addCritProbability(0.02); //Aumentar probabilidad critico
						//Empujar y stunn al enemigo 
					}
					canHit = true;

					Swallow* playerSwallow = entity_->getComponent<Swallow>();

					//Si puede tragar, el enemigo tiene la mitad de la vida y es fin de combo - probabilidad de tragar
					if (finCombo && playerSwallow != nullptr && eAttribs->getLife() <= eAttribs->getMaxLife() / 2 && playerSwallow->canSwallow()) {
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

						if (enmStateM != EnemyStates::ENM_DEAD) {
							//Si tiene stun, se aplica
							EnemyStun* enmStun = ents[i]->getComponent<EnemyStun>();
							if (enmStun != nullptr && enmStun->isActive()) {

								ents[i]->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, true);

								//Si no estaba aturdido ya
								if (enmStateM != EnemyStates::ENM_STUNNED) {
									//Aturdimos al enemigo
									enmStateM = EnemyStates::ENM_STUNNED;
									//Desactivamos componente de seguimiento de jugador
									/*
									FollowPlayer* flwPlayer = ents[i]->getComponent<FollowPlayer>();
									if (flwPlayer != nullptr)
										flwPlayer->setActive(false);
									*/
								}
								//Reiniciamos tiempo de stun
								enmStun->restartStunTime();
							}
						}

						//Si tiene Knockback, se aplica
						Knockback* enmKnockback = ents[i]->getComponent<Knockback>();
						if (enmKnockback != nullptr) {
							//Damos la vuelta si es atacado por detras
							auto& enmFlip = eTR->getFlip();
							if (enmFlip == tr_->getFlip())
								enmFlip = !enmFlip;

							if (finCombo) {
								enmKnockback->setKnockbackDistance(50);
								enmKnockback->knockback();
								enmKnockback->setKnockbackDistance(5);
							}
							else
								enmKnockback->knockback();
						}

						//Cogemos probabilidad de crítico
						int criticProb = playerAttribs->getCriticProb();

						//Le restamos la vida al enemigo
						if (sdlutils().rand().nextInt(1, 10000) < criticProb * 100) {	//Comprobacion golpe crítico
							eAttribs->recieveDmg(dmg * playerAttribs->getCriticDmg() * 1.5);
							playerAttribs->resetCriticProb();
						}
						else
							eAttribs->recieveDmg(dmg * 1.5);
					}
				}
			}
		}
	}
	entity_->getMngr()->refreshEnemies();
	return canHit;
}

void StrongAttack::render() {
	if (DEBUG_isAttacking_) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 0, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
	}
}

void StrongAttack::attack() {
	if (!entity_->getComponent<AnimHamsterStateMachine>()->isOnAttack()) {
		auto state = hms_->getState();
		if (hms_->canAttack() && sdlutils().currRealTime() > time_ + cooldown_) {

			cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
	
			//auto sizeW = tr_->getW();
			//auto sizeH = tr_->getH();
			//auto& pos = tr_->getPos();
			auto pos = tr_->getRectCollide();

			auto range = entity_->getComponent<EntityAttribs>()->getAttackRange(); // Cogemos el rango del ataque


			attRect_.w = pos.w + pos.w * range;
			attRect_.h = pos.h + pos.h * range;

			auto flip = tr_->getFlip();

			//Si esta flipeado...
			if (flip)
				//Le damos la vuelta al rect
				attRect_.x = pos.x - attRect_.w + pos.w / 2 - cam.x; //esto no funciona bien para el resto de entidades solo con sardinilla supongo, mas tarde investigamos
			else
				attRect_.x = pos.x + pos.w - pos.w / 2 - cam.x;

			attRect_.y = pos.y /*+ pos.h / 4*/ - cam.y;

			//Comprobamos si colisiona con alguno de los enemigos que tiene delante

			//A�adimos a los combos
			bool finCombo = entity_->getComponent<Combos>()->checkCombo(1);

			//Si se colisiona..
			if (CheckCollisions(attRect_, finCombo))
				//Suena el hit y le pega
				hitSound_.play();
			//Si no colisiona..
			else
				//Suena el attackSound
				attackSound_.play();

			//this.anims.play(pegarse)
			//entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::STRONGATTACK, true);


			DEBUG_isAttacking_ = true;
			time_ = sdlutils().currRealTime();
			entity_->getComponent<Stroke>()->increaseChance(10, false);
		}
	}
	//else if (sdlutils().currRealTime() > time_ + cooldown_ / 2) {
	//	state = HamStates::IDLE;
	//}
}