#include "LightAttack.h"
#include "Stroke.h"
#include "Combos.h"
#include "FollowPlayer.h"
#include "Knockback.h"
#include "EnemyStun.h"
#include "AnimHamsterStateMachine.h"
#include "Swallow.h"

LightAttack::LightAttack() :
	hms_(nullptr), tr_(nullptr), cooldown_(350), time_(sdlutils().currRealTime()), attRect_(), DEBUG_isAttacking_(false),
	attackSound_(sdlutils().soundEffects().at("light_attack")), hitSound_(sdlutils().soundEffects().at("hit")) {}

void LightAttack::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);

	player_ = entity_->getComponent<EntityAttribs>()->getNumber();
	cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
}

void LightAttack::update() {
	//Deja de mostrar el collider
	if (sdlutils().currRealTime() > time_ + cooldown_ / 1.5) {
		DEBUG_isAttacking_ = false;
	}

	//Fin animacion
	if (entity_->getComponent<AnimHamsterStateMachine>()->getState() == HamStatesAnim::LIGHTATTACK1)
	{
		if (entity_->getComponent<Animator>()->OnAnimationFrameEnd())
		{

			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::LIGHTATTACK1, false);

			/*if(attackOrder_ == 0)
				entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::LIGHTATTACK1, false);
			else
				entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::LIGHTATTACK2, false);*/

		}

	}
}

bool LightAttack::CheckCollisions(const SDL_Rect& rectPlayer, bool finCombo) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEntities();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un enemigo...
		if (ents[i]->hasGroup<Enemy>()) {
			//Cogemos el transform del enemigo
			auto eTR = ents[i]->getComponent<Transform>();


			//Creamos su Rect
			SDL_Rect rectEnemy;
			rectEnemy.h = eTR->getH();
			rectEnemy.w = eTR->getW();
			rectEnemy.x = eTR->getPos().getX() - cam.x;
			rectEnemy.y = eTR->getPos().getY() - cam.y;

			//Y comprobamos si colisiona
			if (SDL_HasIntersection(&rectPlayer, &rectEnemy)) {
				EntityAttribs* playerAttribs = entity_->getComponent<EntityAttribs>();
				int dmg = playerAttribs->getDmg();
				if (finCombo) {
					if (!canHit) playerAttribs->addCritProbability(0.01); //Aumentar probabilidad critico
					//Empujar y stunn al enemigo 
				}
				canHit = true;

				EntityAttribs* enmAttribs = ents[i]->getComponent<EntityAttribs>();
				Swallow* playerSwallow = entity_->getComponent<Swallow>();

				//Si puede tragar, el enemigo tiene la mitad de la vida y es fin de combo - probabilidad de tragar
				if (finCombo && playerSwallow != nullptr && enmAttribs->getLife() <= enmAttribs->getMaxLife() / 2 && playerSwallow->canSwallow()) {
					enmAttribs->recieveDmg(enmAttribs->getLife()); // Esta puesto asi y no con setlife para que se vea la barra bajar
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
							enmAttribs->poison();
						}
					}

					auto& enmStateM = ents[i]->getComponent<EnemyStateMachine>()->getState();

					if (enmStateM != EnemyStates::ENM_DEAD) {
						//Si tiene stun, se aplica
						EnemyStun* enmStun = ents[i]->getComponent<EnemyStun>();
						if (enmStun != nullptr && enmStun->isActive()) {

							//Si no estaba aturdido ya
							if (enmStateM != EnemyStates::ENM_STUNNED) {
								//Aturdimos al enemigo
								enmStateM = EnemyStates::ENM_STUNNED;

								//TODO el stun del coso
								//Desactivamos componente de seguimiento de jugador
								/*
								FollowPlayer* flwPlayer = ents[i]->getComponent<FollowPlayer>();
								if (flwPlayer != nullptr);
								*/
									//flwPlayer->setActive(false);
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
				}

				//Le restamos la vida al enemigo
				enmAttribs->recieveDmg(dmg);
			}
		}
	}
	return canHit;
}

void LightAttack::render() {
	if (DEBUG_isAttacking_) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 212, 255, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
	}
}

void LightAttack::attack() {
	auto state = hms_->getState();
	if (hms_->canAttack() && sdlutils().currRealTime() > time_ + cooldown_) {

		auto sizeW = tr_->getW();
		auto sizeH = tr_->getH();
		auto& pos = tr_->getPos();
		auto range = entity_->getComponent<EntityAttribs>()->getAttackRange(); // Cogemos el rango del ataque


		attRect_.w = sizeW / 2 + sizeW / 2 * range;
		attRect_.h = sizeH / 2 + sizeH / 2 * range;

		auto flip = tr_->getFlip();

		//Si esta flipeado...
		if (flip)
			//Le damos la vuelta al rect
			attRect_.x = pos.getX() - attRect_.w + sizeW / 4 - cam.x; //esto no funciona bien para el resto de entidades solo con sardinilla supongo, mas tarde investigamos
		else
			attRect_.x = pos.getX() + sizeW - sizeW / 4 - cam.x;

		attRect_.y = pos.getY() + sizeH / 4 - cam.y;

		//Comprobamos si colisiona con alguno de los enemigos que tiene delante
		//A�adimos a los combos
		bool finCombo = entity_->getComponent<Combos>()->checkCombo(0);

		//Si se colisiona..
		if (CheckCollisions(attRect_, finCombo))
			//Suena el hit y le pega
			hitSound_.play();
		//Si no colisiona..
		else
			//Suena el attackSound
			attackSound_.play();

		//this.anims.play(pegarse)

		//GESTION DE LA ANIMACION
		if (attackOrder_ == 0)
		{
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::LIGHTATTACK1, true);
			attackOrder_++;
		}
		else
		{
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::LIGHTATTACK2, true);
			attackOrder_--;
		}

		DEBUG_isAttacking_ = true;
		time_ = sdlutils().currRealTime();
		entity_->getComponent<Stroke>()->increaseChance(5, false);
	}
	//else if (sdlutils().currRealTime() > time_ + cooldown_ / 2) {
	//	state = HamStates::IDLE;
	//}
}
