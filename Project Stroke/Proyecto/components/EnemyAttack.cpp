﻿#include "EnemyAttack.h"
#include "Stroke.h"
#include "Combos.h"
#include "Stun.h"
#include "Knockback.h"
#include "ControlHandler.h"
#include "StrongAttack.h"
#include "LightAttack.h"
#include "AnimHamsterStateMachine.h"
#include "AnimEnemyStateMachine.h"


EnemyAttack::EnemyAttack() :
	tr_(nullptr), minCD_(900), maxCD_(1300), cooldown_(sdlutils().rand().nextInt(minCD_, maxCD_)), time_(sdlutils().currRealTime()), attRect_(), DEBUG_isAttacking_(false) {}

EnemyAttack::EnemyAttack(int min, int max) :
	tr_(nullptr), minCD_(min), maxCD_(max), cooldown_(sdlutils().rand().nextInt(minCD_, maxCD_)), time_(sdlutils().currRealTime()), attRect_(), DEBUG_isAttacking_(false) {}

void EnemyAttack::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void EnemyAttack::update() {
	//Deja de mostrar el collider
	if (sdlutils().currRealTime() > time_ + cooldown_ / 1.5) {
		DEBUG_isAttacking_ = false;
	}

	//Fin animacion
	if (entity_->getComponent<AnimEnemyStateMachine>() != nullptr)
	{
		if (entity_->getComponent<AnimEnemyStateMachine>()->getState() == EnemyStatesAnim::ATTACK)
		{
			if (entity_->getComponent<Animator>()->OnAnimationFrameEnd())
			{
				entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::ATTACK, false);
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

				attRect_.y = pos.y /*+ sizeH / 4*/ - cam.y;

				//Comprobamos si colisiona con alguno de los enemigos que tiene delante

				//Si se colisiona..
				if (CheckCollisions(attRect_, true))
					//Suena el hit y le pega
					entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("lighthit");
				//Si no colisiona..
				else
					//Suena el attackSound
					entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("attack");


				DEBUG_isAttacking_ = true;
				time_ = sdlutils().currRealTime();
				cooldown_ = sdlutils().rand().nextInt(minCD_, maxCD_);
			}
		}
	}
}

bool EnemyAttack::LaunchAttack() {
	if (sdlutils().currRealTime() > time_ + cooldown_) {
		//ANIMACION DE ATTAQUE
		entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::ATTACK, true);
		return true;
	}
	else
		return false;
}

bool EnemyAttack::CheckCollisions(const SDL_Rect& enemyRect, bool finCombo) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getPlayers();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un aliado...
			//Cogemos el transform del aliado
		auto hamsTR = ents[i]->getComponent<Transform>();
		auto hamColRect = hamsTR->getRectCollide();

		Vector2D newPos = Vector2D(hamColRect.x - cam.x, hamColRect.y - cam.y);
		Vector2D enemyPos = Vector2D(enemyRect.x, enemyRect.y);

		EntityAttribs* eAttribs = ents[i]->getComponent<EntityAttribs>();

		//Y comprobamos si colisiona y si no es invulnerable
		if (!eAttribs->checkInvulnerability() && Collisions::collides(newPos, hamColRect.w, hamColRect.h, enemyPos, enemyRect.w, enemyRect.h)) {
			int dmg = entity_->getComponent<EntityAttribs>()->getDmg();
			//if (finCombo) {
			//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
			//	//Empujar y stun al aliado
			//}
			canHit = true;
			//Le restamos la vida al aliado
			eAttribs->recieveDmg(dmg);

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
						ents[i]->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::HITTED, true);


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
				auto& hamFlip = hamsTR->getFlip();
				if (hamFlip == tr_->getFlip())
					hamFlip = !hamFlip;

				hamKnockback->knockback();

				SDL_Rect rectPlayer = hamsTR->getRectCollide();
				rectPlayer.x += hamsTR->getVel().getX();
				rectPlayer.y += hamsTR->getFloor();
				
				SDL_Rect rectFoot = hamsTR->getRectCollideFeet();
				rectFoot.x += hamsTR->getVel().getX();
				rectFoot.y += hamsTR->getFloor();
				int dir = -1;
				if (tr_->getVel().getX() > 0) dir = 1;
				
				ents[i]->getComponent<CollisionDetec>()->tryToMove(Vector2D(dir, 0), Vector2D(hamKnockback->getKnockback(), 0), rectPlayer, false);
				ents[i]->getComponent<CollisionDetec>()->tryToMoveObs(Vector2D(dir, 0), Vector2D(hamKnockback->getKnockback(), 0), rectFoot, false);
				//ents[i]->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::STUNNED, true);
				//ESTA LINEA DEBERIA IR EN FUNCION DEL ENEMIGO QUE ATACA SI ES EL FUERTE O NO
			}
		}
	}
	entity_->getMngr()->refreshPlayers();
	return canHit;
}

void EnemyAttack::render() {
	if (DEBUG_isAttacking_ && debug) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 170, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
	}
}
