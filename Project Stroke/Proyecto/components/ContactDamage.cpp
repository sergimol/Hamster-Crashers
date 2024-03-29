﻿#include "EnemyAttack.h"
#include "Stroke.h"
#include "Combos.h"
#include "Stun.h"
#include "EnemyStun.h"
#include "Knockback.h"
#include "ControlHandler.h"
#include "StrongAttack.h"
#include "ContactDamage.h"
#include "AnimEnemyStateMachine.h"
#include "AnimHamsterStateMachine.h"
#include "../utils/Collisions.h"

ContactDamage::ContactDamage(int danyo,int directionKnockbackAux, bool useFeet, bool damageInJump, bool damageEnemies) :
	tr_(nullptr), attRect_(), DEBUG_isAttacking_(false), dmg_(danyo), directionKnockback(directionKnockbackAux),
	useFeet_(useFeet), damageInJump_(damageInJump), damageEnemies_(damageEnemies){}

void ContactDamage::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void ContactDamage::update() {
	//Deja de mostrar el collider
	/*
	if (sdlutils().currRealTime() > time_ / 1.5) {
		DEBUG_isAttacking_ = false;
	}
	*/
	updateRect();
}

void ContactDamage::updateRect() {

	cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

	//crear el rectangulo que va a hacer el contact damage

	attRect_ = tr_->getRectCollide();

	attRect_.x = attRect_.x - cam.x;
	attRect_.y = attRect_.y - cam.y;

	//Comprobamos si colisiona con alguno de los players

	////Si se colisiona..
	if (CheckCollisions(attRect_, true))
		//Suena el hit y le pega
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("lighthit");

	if (damageEnemies_ && CheckCollisionsEnemies(attRect_, false))
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("lighthit");

	//this.anims.play(pegarse)

		DEBUG_isAttacking_ = true;
	time_ = sdlutils().currRealTime();
}

bool ContactDamage::CheckCollisions(const SDL_Rect& enemyRect, bool finCombo) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getPlayers();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un player...

			//Cogemos el transform del player
		auto eTR = ents[i]->getComponent<Transform>();
		SDL_Rect eColRect;
		if (!useFeet_)
			 eColRect = eTR->getRectCollide();
		else
			 eColRect = eTR->getRectCollideFeet();

		//Vector2D newPos = Vector2D(eTR->getPos().getX() - cam.x, eTR->getPos().getY() - cam.y);
		Vector2D enemyPos = Vector2D(enemyRect.x, enemyRect.y);
		EntityAttribs* eAttribs = ents[i]->getComponent<EntityAttribs>();

		//Y comprobamos si colisiona
		//es can attacks porque coninciden lso estados

		//si no esta saltando el player en caso de que asi sea

		if (!damageInJump_ || !ents[i]->getComponent<Combos>()->isJumping())
		if (ents[i]->getComponent<HamsterStateMachine>()->canAttack() && Collisions::collides(Vector2D(eColRect.x - cam.x, eColRect.y - cam.y), eColRect.w, eColRect.h, enemyPos, enemyRect.w, enemyRect.h)) {
			//TODO no voy a definir una entidad ahora
			//int dmg = entity_->getComponent<EntityAttribs>()->getDmg();

			//Comprobamos si está en la misma Z o relativamente cerca
			if (eAttribs->ignoresMargin()) {
				
				if (abs((tr_->getPos().getY() + tr_->getH()) - (eTR->getPos().getY() + eTR->getH())) < eAttribs->getMarginToAttack()) {




					//if (finCombo) {
					//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
					//	//Empujar y stun al aliado
					//}
					canHit = true;
					//Le restamos la vida al aliado
					ents[i]->getComponent<EntityAttribs>()->recieveDmg(dmg_);

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
				}
			}
			else {
				//if (finCombo) {
				//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
				//	//Empujar y stun al aliado
				//}
				canHit = true;
				//Le restamos la vida al aliado
				ents[i]->getComponent<EntityAttribs>()->recieveDmg(dmg_);

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
				
			}
			//Si tiene Knockback, se aplica
			if (canHit) {

				Knockback* hamKnockback = ents[i]->getComponent<Knockback>();
				if (hamKnockback != nullptr && hamKnockback->isActive()) {
					//Damos la vuelta si es atacado por detras

					//DEPENDE DE LA posicion de X y el width al medio
					//attRect_.x;
					//attRect_.w;
					//allyRect.w;
					//allyRect.x;
					//allyRect.x;

					//MIRADNOA AL DERECHA ES !flip, izquierda es flip, por default quuiero que sea !flip
					auto& hamFlip = eTR->getFlip();
					if (attRect_.x + (attRect_.w / 2) > eColRect.x - cam.x + (eColRect.w / 2)) //esta a ala izquierda entonces !flip
					{
						hamFlip = false;
					}
					else {
						hamFlip = true;
					}
					hamKnockback->knockback(directionKnockback);
			}

			}
		}

	}
	entity_->getMngr()->refreshPlayers();


	return canHit;
}


bool ContactDamage::CheckCollisionsCat(const SDL_Rect& enemyRect, bool finCombo) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getPlayers();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un player...

			//Cogemos el transform del player
		auto eTR = ents[i]->getComponent<Transform>();
		SDL_Rect eColRect;
		if (!useFeet_)
			eColRect = eTR->getRectCollide();
		else
			eColRect = eTR->getRectCollideFeet();

		//Vector2D newPos = Vector2D(eTR->getPos().getX() - cam.x, eTR->getPos().getY() - cam.y);
		Vector2D enemyPos = Vector2D(enemyRect.x, enemyRect.y);
		EntityAttribs* eAttribs = ents[i]->getComponent<EntityAttribs>();

		//Y comprobamos si colisiona
		//es can attacks porque coninciden lso estados

		//si no esta saltando el player en caso de que asi sea

		if (!damageInJump_ || !ents[i]->getComponent<Combos>()->isJumping())
			if (ents[i]->getComponent<HamsterStateMachine>()->canAttack() && Collisions::collides(Vector2D(eColRect.x - cam.x, eColRect.y - cam.y), eColRect.w, eColRect.h, enemyPos, enemyRect.w, enemyRect.h)) {
				//TODO no voy a definir una entidad ahora
				//int dmg = entity_->getComponent<EntityAttribs>()->getDmg();

				//Comprobamos si está en la misma Z o relativamente cerca
				if (eAttribs->ignoresMargin()) {

					if (abs((tr_->getPos().getY() + tr_->getH()) - (eTR->getPos().getY() + eTR->getH())) < eAttribs->getMarginToAttack()) {




						//if (finCombo) {
						//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
						//	//Empujar y stun al aliado
						//}
						canHit = true;
						//Le restamos la vida al aliado
						ents[i]->getComponent<EntityAttribs>()->recieveDmg(dmg_);

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
					}
				}
				else {
					//if (finCombo) {
					//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
					//	//Empujar y stun al aliado
					//}
					canHit = true;
					//Le restamos la vida al aliado
					ents[i]->getComponent<EntityAttribs>()->recieveDmg(dmg_);

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

				}
				//Si tiene Knockback, se aplica
				if (canHit) {

					Knockback* hamKnockback = ents[i]->getComponent<Knockback>();
					if (hamKnockback != nullptr && hamKnockback->isActive()) {
						//Damos la vuelta si es atacado por detras

						//DEPENDE DE LA posicion de X y el width al medio
						//attRect_.x;
						//attRect_.w;
						//allyRect.w;
						//allyRect.x;
						//allyRect.x;

						//MIRADNOA AL DERECHA ES !flip, izquierda es flip, por default quuiero que sea !flip
						auto& hamFlip = eTR->getFlip();
						if (attRect_.x + (attRect_.w / 2) > eColRect.x - cam.x + (eColRect.w / 2)) //esta a ala izquierda entonces !flip
						{
							hamFlip = false;
						}
						else {
							hamFlip = true;
						}
						hamKnockback->knockback(directionKnockback);
					}

				}
			}

	}
	entity_->getMngr()->refreshPlayers();


	return canHit;
}

bool ContactDamage::CheckCollisionsEnemies(const SDL_Rect& enemyRect, bool finCombo) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEnemies();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un player...
		if (ents[i]->isActive() && ents[i]->hasComponent<Transform>()) {
			//Cogemos el transform del player
			auto eTR = ents[i]->getComponent<Transform>();
			SDL_Rect eColRect;
			if (!useFeet_)
				eColRect = eTR->getRectCollide();
			else
				eColRect = eTR->getRectCollideFeet();

			//Vector2D newPos = Vector2D(eTR->getPos().getX() - cam.x, eTR->getPos().getY() - cam.y);
			Vector2D enemyPos = Vector2D(enemyRect.x, enemyRect.y);
			EntityAttribs* eAttribs = ents[i]->getComponent<EntityAttribs>();

			//Y comprobamos si colisiona
			//es can attacks porque coninciden lso estados

			if (Collisions::collides(Vector2D(eColRect.x - cam.x, eColRect.y - cam.y), eColRect.w, eColRect.h, enemyPos, enemyRect.w, enemyRect.h)) {
				//TODO no voy a definir una entidad ahora
				//int dmg = entity_->getComponent<EntityAttribs>()->getDmg();

				//Comprobamos si está en la misma Z o relativamente cerca
				if (eAttribs->ignoresMargin()) {
					auto& hamStateM = ents[i]->getComponent<EnemyStateMachine>()->getState();

					if ((hamStateM != EnemyStates::ENM_STUNNED && hamStateM != EnemyStates::ENM_DEAD) && abs((tr_->getPos().getY() + tr_->getH()) - (eTR->getPos().getY() + eTR->getH())) < eAttribs->getMarginToAttack()) {




						//if (finCombo) {
						//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
						//	//Empujar y stun al aliado
						//}
						canHit = true;
						//Le restamos la vida al aliado
						ents[i]->getComponent<EntityAttribs>()->recieveDmg(dmg_);


						if (hamStateM != EnemyStates::ENM_DEAD) {
							//Si tiene stun, se aplica
							EnemyStun* stun = ents[i]->getComponent<EnemyStun>();
							if (stun != nullptr && stun->isActive()) {

								//Si no estaba aturdido ya
								if (hamStateM != EnemyStates::ENM_STUNNED) {
									//Aturdimos al hamster
									hamStateM = EnemyStates::ENM_STUNNED;

									//Animaci�n de stun
									ents[i]->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, true);
								}
								//Reiniciamos tiempo de stun
								stun->restartStunTime(false);
							}
						}
					}
				}
				else {
					auto& hamStateM = ents[i]->getComponent<EnemyStateMachine>()->getState();

					if ((hamStateM != EnemyStates::ENM_STUNNED && hamStateM != EnemyStates::ENM_DEAD)) {




						//if (finCombo) {
						//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
						//	//Empujar y stun al aliado
						//}
						canHit = true;
						//Le restamos la vida al aliado
						ents[i]->getComponent<EntityAttribs>()->recieveDmg(dmg_);


						if (hamStateM != EnemyStates::ENM_DEAD) {
							//Si tiene stun, se aplica
							EnemyStun* stun = ents[i]->getComponent<EnemyStun>();
							if (stun != nullptr && stun->isActive()) {

								//Si no estaba aturdido ya
								if (hamStateM != EnemyStates::ENM_STUNNED) {
									//Aturdimos al hamster
									hamStateM = EnemyStates::ENM_STUNNED;

									//Animaci�n de stun
									ents[i]->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, true);
								}
								//Reiniciamos tiempo de stun
								stun->restartStunTime(false);
							}
						}
					}

				}
				//Si tiene Knockback, se aplica
				if (canHit) {

					Knockback* hamKnockback = ents[i]->getComponent<Knockback>();
					if (hamKnockback != nullptr && hamKnockback->isActive()) {
						//Damos la vuelta si es atacado por detras

						//DEPENDE DE LA posicion de X y el width al medio
						//attRect_.x;
						//attRect_.w;
						//allyRect.w;
						//allyRect.x;
						//allyRect.x;

						//MIRADNOA AL DERECHA ES !flip, izquierda es flip, por default quuiero que sea !flip
						auto& hamFlip = eTR->getFlip();
						if (attRect_.x + (attRect_.w / 2) > eColRect.x - cam.x + (eColRect.w / 2)) //esta a ala izquierda entonces !flip
						{
							hamFlip = false;
						}
						else {
							hamFlip = true;
						}
						hamKnockback->knockback(directionKnockback);
					}

				}
			}
		}
	}
	entity_->getMngr()->refreshEnemies();

	return canHit;
}

void ContactDamage::render() {
	if (DEBUG_isAttacking_ && debug) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 170, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
	}
}
