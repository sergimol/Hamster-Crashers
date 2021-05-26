#include "EnemyStrongAttack.h"
#include "Stroke.h"
#include "Combos.h"
#include "Stun.h"
#include "Knockback.h"
#include "ControlHandler.h"
#include "StrongAttack.h"
#include "LightAttack.h"
#include "AnimHamsterStateMachine.h"
#include "AnimEnemyStateMachine.h"

EnemyStrongAttack::EnemyStrongAttack() :
	tr_(nullptr), cooldown_(3000), time_(sdlutils().currRealTime()), attRect_(), DEBUG_isAttacking_(false),
	durationTime_(sdlutils().currRealTime()), attackDurationCD_(2500), beforeHitCD_(500), state_(nullptr) {}

void EnemyStrongAttack::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void EnemyStrongAttack::update() {

	if (state_->getState() == GameStates::RUNNING) {
		//Deja de mostrar el collider
		if (sdlutils().currRealTime() > time_ + cooldown_ / 1.5) {
			DEBUG_isAttacking_ = false;
		}


		if (entity_->getComponent<AnimEnemyStateMachine>() != nullptr)
		{

			if (attackStarted_)
			{
				//SE MANTIENE PEGANDO
				if (sdlutils().currRealTime() > durationTime_ + beforeHitCD_) {
					cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
					//auto sizeW = tr_->getW();
					//auto sizeH = tr_->getH();
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

					attRect_.y = pos.y - cam.y;

					//Comprobamos si colisiona con alguno de los enemigos que tiene delante

					//Si se colisiona..

					if (CheckCollisions(attRect_, true)) {
						//Suena el hit y le pega
						if (entity_->getComponent<EntityAttribs>()->getId() == "monosinpatico")
							entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("platillos");
						else
							entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("stronghit");
					}

					DEBUG_isAttacking_ = true;
				}
				//DEJA DE PEGAR
				if (sdlutils().currRealTime() > durationTime_ + attackDurationCD_) {
					attackStarted_ = false;
					time_ = sdlutils().currRealTime();

					//SE ACABA EL ATAQUE 
					entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::STRONGATTACK, false);
				}
			}
		}
	}
}

bool EnemyStrongAttack::LaunchAttack() {
	if (sdlutils().currRealTime() > time_ + cooldown_) {
		attackStarted_ = true;
		durationTime_ = sdlutils().currRealTime();


		//ANIMACION DE ATTAQUE
		entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::STRONGATTACK, true);
		return true;
	}
	else
		return false;
}

bool EnemyStrongAttack::CheckCollisions(const SDL_Rect& enemyRect, bool finCombo) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getPlayers();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un aliado...
			//Cogemos el transform del aliado
		auto eTR = ents[i]->getComponent<Transform>();
		auto eColRect = eTR->getRectCollide();

		Vector2D newPos = Vector2D(eColRect.x - cam.x, eColRect.y - cam.y);
		Vector2D enemyPos = Vector2D(enemyRect.x, enemyRect.y);

		EntityAttribs* eAttribs = ents[i]->getComponent<EntityAttribs>();

		//Y comprobamos si colisiona y si no es invulnerable
		if (!eAttribs->checkInvulnerability() && Collisions::collides(newPos, eColRect.w, eColRect.h, enemyPos, enemyRect.w, enemyRect.h)) {
			int dmg = entity_->getComponent<EntityAttribs>()->getDmg();
			//if (finCombo) {
			//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
			//	//Empujar y stun al aliado
			//}
			canHit = true;
			//Le restamos la vida al aliado
			eAttribs->recieveDmg(dmg / 2);

			auto& hamStateM = ents[i]->getComponent<HamsterStateMachine>()->getState();

			if (hamStateM != HamStates::DEAD && hamStateM != HamStates::INFARCTED) {
				//Si tiene stun, se aplica
				Stun* stun = ents[i]->getComponent<Stun>();
				if (stun != nullptr && stun->isActive()) {

					//Si no estaba aturdido ya
					if (hamStateM != HamStates::STUNNED) {
						//Aturdimos al hamster
						hamStateM = HamStates::STUNNED;

						//Animaci�n de stun
						//anim_->play(sdlutils().anims().at("sardinilla_stun"));

						//Desactivamos control de movimiento 
						ControlHandler* ctrl = ents[i]->getComponent<ControlHandler>();
						if (ctrl != nullptr)
							ctrl->setActive(false);

						//Desactivamos componentes de ataque
						StrongAttack* strAtt = ents[i]->getComponent<StrongAttack>();
						if (strAtt != nullptr)
							strAtt->setActive(false);

						LightAttack* lghtAtt = ents[i]->getComponent<LightAttack>();
						if (lghtAtt != nullptr)
							lghtAtt->setActive(false);

					}
					//Reiniciamos tiempo de stun
					stun->restartStunTime();
				}

				//ANIMACION DE HIT DEL HAMSTER
				ents[i]->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::HITTED, true);
			}
			//Si tiene Knockback, se aplica
			Knockback* hamKnockback = ents[i]->getComponent<Knockback>();
			if (hamKnockback != nullptr && hamKnockback->isActive()) {
				//Damos la vuelta si es atacado por detras
				auto& hamFlip = eTR->getFlip();
				if (hamFlip == tr_->getFlip())
					hamFlip = !hamFlip;

				hamKnockback->knockback(15);

				SDL_Rect rectPlayer = eTR->getRectCollide();
				rectPlayer.x += hamKnockback->getKnockback();
				rectPlayer.y += eTR->getFloor();

				SDL_Rect rectFoot = tr_->getRectCollide();
				rectFoot.x += hamKnockback->getKnockback();
				rectFoot.y += eTR->getFloor();

				ents[i]->getComponent<CollisionDetec>()->tryToMove(Vector2D(0, 0), Vector2D(hamKnockback->getKnockback(), 0), rectPlayer, false);
				ents[i]->getComponent<CollisionDetec>()->tryToMoveObs(Vector2D(0, 0), Vector2D(hamKnockback->getKnockback(), 0), rectFoot, false);
			}
		}
	}
	entity_->getMngr()->refreshPlayers();
	return canHit;
}

void EnemyStrongAttack::render() {
	if (DEBUG_isAttacking_ && debug) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 170, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
	}
}

void EnemyStrongAttack::onResume() {
	durationTime_ += sdlutils().currRealTime() - durationTime_;
	time_ += sdlutils().currRealTime() - time_;
}
