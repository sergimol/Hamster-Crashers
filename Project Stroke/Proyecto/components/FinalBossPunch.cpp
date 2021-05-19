#include "FinalBossPunch.h"
#include "Stroke.h"
#include "Combos.h"
#include "Stun.h"
#include "Knockback.h"
#include "ControlHandler.h"
#include "StrongAttack.h"
#include "LightAttack.h"
#include "AnimHamsterStateMachine.h"

FinalBossPunch::FinalBossPunch() :
	tr_(nullptr), cooldown_(1300), time_(sdlutils().currRealTime()), attRect_(), DEBUG_isAttacking_(false),
	attackStarted_(false), hitTime_(0), beforeHitCD_(1000), afterHitCD_(4250), stunStarted_(false), eAttribs_(nullptr), 
	state_(nullptr), attackFinished_(false) {}

void FinalBossPunch::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	eAttribs_ = entity_->getComponent<EntityAttribs>();
	assert(eAttribs_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void FinalBossPunch::update() {
	if (state_->getState() == GameStates::RUNNING) {
		//Deja de mostrar el collider
		if (sdlutils().currRealTime() > time_ + cooldown_ / 1.5) {
			DEBUG_isAttacking_ = false;
		}
		if (attackStarted_) {

			//Telegrafiado hasta el ataque
			if (!stunStarted_ && sdlutils().currRealTime() > hitTime_ + beforeHitCD_) {
				cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
				auto sizeW = tr_->getW();
				auto& pos = tr_->getPos();

				attRect_.w = sizeW; //Esto que cuadre con la mano cuando sea
				attRect_.h = tr_->getH()/6;

				//Cogemos el rect completo del jefe

				attRect_.x = pos.getX() - cam.x;
				attRect_.y = pos.getY() - cam.y + (5.0f/6.0f)*tr_->getH(); //Pos inicial de esquina arriba

				//Comprobamos si colisiona con alguno de los enemigos que tiene delante

				//Si se colisiona..
				if (CheckCollisions(attRect_))
					//Suena el hit y le pega
					entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("lighthit");
				//Si no colisiona..
				else
					//Suena el attackSound
					entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("attack");

				//this.anims.play(pegarse)

				DEBUG_isAttacking_ = true;
				time_ = sdlutils().currRealTime();

				stunStarted_ = true;
			}
			else if (eAttribs_->checkInvulnerability() && sdlutils().currRealTime() <= hitTime_ + afterHitCD_) {
				eAttribs_->setInvincibility(false);
			}
			else if (stunStarted_ && sdlutils().currRealTime() > hitTime_ + afterHitCD_) {
				eAttribs_->setInvincibility(true);
				attackStarted_ = false;
				stunStarted_ = false;
				attackFinished_= true;
			}
		}
	}
}

bool FinalBossPunch::LaunchAttack() {
	if (sdlutils().currRealTime() > time_ + cooldown_) {
		//Comienza el ciclo completo de ataque

		attackStarted_ = true;
		stunStarted_ = false;
		hitTime_ = sdlutils().currRealTime();
		return true;
	}
	else
		return false;
}

bool FinalBossPunch::CheckCollisions(const SDL_Rect& enemyRect) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getPlayers();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un aliado...
			//Cogemos el transform del aliado
		auto eTR = ents[i]->getComponent<Transform>();

		//Creamos su Rect
		SDL_Rect allyRect;
		allyRect.h = eTR->getH();
		allyRect.w = eTR->getW();
		allyRect.x = eTR->getPos().getX() - cam.x;
		allyRect.y = eTR->getPos().getY() - cam.y;

		EntityAttribs* eAttribs = ents[i]->getComponent<EntityAttribs>();

		//Y comprobamos si colisiona y si no es invulnerable
		if (!eAttribs->checkInvulnerability() && SDL_HasIntersection(&enemyRect, &allyRect)) {
			int dmg = entity_->getComponent<EntityAttribs>()->getDmg();
			//if (finCombo) {
			//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
			//	//Empujar y stun al aliado
			//}
			canHit = true;
			//Le restamos la vida al aliado
			eAttribs->recieveDmg(dmg);
			ents[i]->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::HITTED, true);

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
			}
			//Si tiene Knockback, se aplica
			Knockback* hamKnockback = ents[i]->getComponent<Knockback>();
			if (hamKnockback != nullptr && hamKnockback->isActive()) {
				//Damos la vuelta si es atacado por detras
				auto& hamFlip = eTR->getFlip();
				if (hamFlip == tr_->getFlip())
					hamFlip = !hamFlip;

				hamKnockback->knockback();

				SDL_Rect rectPlayer = tr_->getRectCollide();
				rectPlayer.x += hamKnockback->getKnockback();

				SDL_Rect rectFoot = tr_->getRectCollide();
				rectFoot.x += hamKnockback->getKnockback();

				ents[i]->getComponent<CollisionDetec>()->tryToMove(Vector2D(0, 0), Vector2D(hamKnockback->getKnockback(), 0), rectPlayer, false);
				ents[i]->getComponent<CollisionDetec>()->tryToMoveObs(Vector2D(0, 0), Vector2D(hamKnockback->getKnockback(), 0), rectFoot, false);
			}
		}
	}
	entity_->getMngr()->refreshPlayers();
	return canHit;
}

void FinalBossPunch::render() {
	if (DEBUG_isAttacking_ && debug) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 170, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
	}
}

void FinalBossPunch::onResume() {
	hitTime_ += sdlutils().currRealTime() - hitTime_;
	time_ += sdlutils().currRealTime() - time_;
}
