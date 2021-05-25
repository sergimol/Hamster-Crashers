#include "FinalBossAttack.h"
#include "Stroke.h"
#include "Combos.h"
#include "Stun.h"
#include "Knockback.h"
#include "ControlHandler.h"
#include "StrongAttack.h"
#include "LightAttack.h"
#include "AnimHamsterStateMachine.h"
#include "AnimEnemyStateMachine.h"
#include "CollisionDetec.h"

#include "../sdlutils/SDLUtils.h"

FinalBossAttack::FinalBossAttack() :
	tr_(nullptr), cooldown_(1300), time_(sdlutils().currRealTime()), attRect_(), DEBUG_isAttacking_(false),
	attackStarted_(false), hitTime_(0), beforeHitCD_(1000), afterHitCD_(4250), stunStarted_(false), eAttribs_(nullptr),
	state_(nullptr), attackFinished_(false), attackCount_(0), maxSlaps_(0), collides_(nullptr), collideStartCD_(1250) {}

void FinalBossAttack::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	eAttribs_ = entity_->getComponent<EntityAttribs>();
	assert(eAttribs_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);

	maxSlaps_ = sdlutils().rand().nextInt(2, 5);
}

void FinalBossAttack::update() {
	if (state_->getState() == GameStates::RUNNING) {

		//Quitar la animacion de subida
		if (entity_->getComponent<AnimEnemyStateMachine>()->getState() == EnemyStatesAnim::UP)
		{
			if (entity_->getComponent<Animator>()->OnAnimationFrameEnd())
			{
				entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::UP, false);
				entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::IDLE, true);
			}
		}
		//Deja de mostrar el collider
		if (sdlutils().currRealTime() > time_ + cooldown_ / 1.5) {
			DEBUG_isAttacking_ = false;
		}
		if (attackStarted_) {
			if (attackCount_ != maxSlaps_)  // Si esta a rango, se mueve e intentara atacar
				slam();
			else // ataque fuerte
				swipe();
		}
	}
}

void FinalBossAttack::slam() {
	if (!stunStarted_ && sdlutils().currRealTime() > hitTime_ + beforeHitCD_) {

		//EMPIEZA EL ATAQUE
		entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::ATTACK, true);

		cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
		auto sizeW = tr_->getW();
		auto& pos = tr_->getPos();

		attRect_.w = sizeW; //Esto que cuadre con la mano cuando sea
		attRect_.h = sdlutils().height();

		//Cogemos el rect completo del jefe

		attRect_.x = pos.getX() - cam.x;
		attRect_.y = pos.getY() - cam.y; //Pos inicial de esquina arriba

		//Comprobamos si colisiona con alguno de los enemigos que tiene delante

		//Si se colisiona..
		if (CheckCollisions(attRect_, false))
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
	//HA LLEGADO AL SUELO
	if (entity_->getComponent<AnimEnemyStateMachine>()->getState() == EnemyStatesAnim::ATTACK)
	{
		if (entity_->getComponent<Animator>()->OnAnimationFrameEnd())
		{
			if (stunStarted_ && eAttribs_->checkInvulnerability()) {

				eAttribs_->setInvincibility(false);

				//LE PASAMOS AL ESTADO DEL SUELO Y QUITAMOS EL ATAQUE
				entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::ONFLOOR, true);
				entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::ATTACK, false);
			}
		}
	}
	//else if (stunStarted_ && eAttribs_->checkInvulnerability() && sdlutils().currRealTime() <= hitTime_ + afterHitCD_) {
	//	eAttribs_->setInvincibility(false);
	//}
	else if (stunStarted_ && !collides_ && sdlutils().currRealTime() > hitTime_ + collideStartCD_ && sdlutils().currRealTime() <= hitTime_ + afterHitCD_) {
		// Activar colisiones
		collides_ = true;
	}
	//SE LEVANTA
	else if (stunStarted_ && sdlutils().currRealTime() > hitTime_ + afterHitCD_) {
		eAttribs_->setInvincibility(true);
		attackStarted_ = false;
		stunStarted_ = false;
		attackFinished_ = true;

		//QUITAMOS TODOS LOS ESTADOS QUE PUEDEN INTERFERIR
		entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::ONFLOOR, false);
		entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::ATTACK, false);
		entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, false);

		//FORZAMOS A LA ANIMACION DE SUBIDA
		entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::UP, true);

		// Desactivar colisiones
		collides_ = false;

		attackCount_++;
	}
}

void FinalBossAttack::swipe() {
	cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
	auto sizeW = tr_->getW();
	auto& pos = tr_->getPos();
	auto& vel = tr_->getVel();

	if (!swipeCharge_ && pos.getX() + vel.getX() < cam.x + cam.w - sizeW)
		vel.setX(sdlutils().lerp(70, vel.getX(), 0.8));
	else if (!swipeCharge_) {
		swipeCharge_ = true;
		hitTime_ = sdlutils().currRealTime();
	}
	else if (pos.getX() + vel.getX() > cam.x && sdlutils().currRealTime() > hitTime_ + beforeHitCD_) {
		vel.setX(sdlutils().lerp(-55, vel.getX(), 0.8));

		DEBUG_isAttacking_ = true;

		attRect_.w = sizeW / 4.0f; //Esto que cuadre con la mano cuando sea
		attRect_.h = sdlutils().height();

		//Cogemos el rect completo del jefe
		attRect_.x = pos.getX() - cam.x + sizeW / 4.0f;
		attRect_.y = pos.getY() - cam.y; //Pos inicial de esquina arriba

		//Si se colisiona..
		if (CheckCollisions(attRect_, true))
			//Suena el hit y le pega
			entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("lighthit");
	}
	else if (sdlutils().currRealTime() > hitTime_ + beforeHitCD_) {
		attackStarted_ = false;
		swipeCharge_ = false;
		attackFinished_ = true;
		maxSlaps_ = sdlutils().rand().nextInt(2, 5);
		attackCount_ = 0;
	}
}

bool FinalBossAttack::LaunchAttack() {
	if (sdlutils().currRealTime() > time_ + cooldown_) {
		//Comienza el ciclo completo de ataque

		attackStarted_ = true;
		swipeCharge_ = false;
		stunStarted_ = false;
		hitTime_ = sdlutils().currRealTime();
		return true;
	}
	else
		return false;
}

bool FinalBossAttack::CheckCollisions(const SDL_Rect& enemyRect, bool swipe) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getPlayers();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un aliado...
			//Cogemos el transform del aliado
		auto eTR = ents[i]->getComponent<Transform>();
		auto eRectCollide = eTR->getRectCollide();

		//Creamos su Rect
		SDL_Rect allyRect;
		allyRect.h = eRectCollide.h;
		allyRect.w = eRectCollide.w;
		allyRect.x = eRectCollide.x - cam.x;
		allyRect.y = eRectCollide.y - cam.y;

		EntityAttribs* eAttribs = ents[i]->getComponent<EntityAttribs>();
		bool jumping = swipe ? ents[i]->getComponent<Combos>()->isJumping() : false;

		//Y comprobamos si colisiona y si no es invulnerable
		if (!jumping && !eAttribs->checkInvulnerability() && SDL_HasIntersection(&enemyRect, &allyRect)) {
			int dmg = entity_->getComponent<EntityAttribs>()->getDmg();
			//if (finCombo) {
			//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
			//	//Empujar y stun al aliado
			//}
			canHit = true;
			//Le restamos la vida al aliado
			eAttribs->recieveDmg(dmg);
			//ents[i]->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::HITTED, true);

			auto& hamStateM = ents[i]->getComponent<HamsterStateMachine>()->getState();

			if (hamStateM != HamStates::DEAD && hamStateM != HamStates::INFARCTED) {
				ents[i]->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::HITTED, true);
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

				if (swipe && !hamFlip)
					hamKnockback->knockback(-75);
				else
					hamKnockback->knockback(75);


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

void FinalBossAttack::render() {
	if (DEBUG_isAttacking_ && debug) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 170, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
	}
}

void FinalBossAttack::onResume() {
	hitTime_ += sdlutils().currRealTime() - hitTime_;
	time_ += sdlutils().currRealTime() - time_;
}
