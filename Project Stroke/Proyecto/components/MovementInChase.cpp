#include "MovementInChase.h"
#include "Stroke.h"
#include "Combos.h"
#include "AnimHamsterStateMachine.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

//Para comprobar las colisiones
#include "CollisionDetec.h"

void MovementInChase::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	hms_ = entity_->getComponent<HamsterStateMachine>();
	//assert(hms_ != nullptr);

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

	attribs_ = entity_->getComponent<EntityAttribs>();
	//assert(atribs != nullptr);

	//Necesario para el cadaver
	if (attribs_ != nullptr)
		speed_ = attribs_->getVel();
	else
		speed_ = Vector2D(1, 1);

	animState_ = entity_->getComponent<AnimHamsterStateMachine>();
	//assert(animState_ != nullptr);

	grav_ = entity_->getComponent<Gravity>();
	assert(grav_ != nullptr);

	//comb_ = entity_->getComponent<Combos>();
	//assert(comb_ != nullptr);

	col_ = entity_->getComponent<CollisionDetec>();
	assert(col_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);

	//stroke_ = entity_->getComponent<Stroke>();
	//assert(stroke_ != nullptr);


	keymap.insert({ UP, false });
	keymap.insert({ DOWN, false });
	keymap.insert({ RIGHT, false });
	keymap.insert({ LEFT, false });
	keymap.insert({ SPACE, false });

}

void MovementInChase::updateKeymap(KEYS x, bool is) {
	if (x != SPACE || (!keymap.at(SPACE) && tr_->getZ() <= grav_->getFloor()))
		keymap.at(x) = is;
}

void MovementInChase::update() {

	if (state_->getState() == GameStates::RUNNING) {
		auto& vel = tr_->getVel();
		auto& state = hms_->getState();
		auto& z = tr_->getZ();
		auto& velZ = tr_->getVelZ();

		Vector2D dir = Vector2D(0, 0);

		if (keymap.at(UP)) {
			dir.setY(-1.0f);
		}
		else if (keymap.at(DOWN)) {
			dir.setY(1.0f);
		}

		if (keymap.at(RIGHT)) {
			dir.setX(1.0f);
			tr_->getFlip() = true;
		}
		else if (keymap.at(LEFT)) {
			dir.setX(-1.0f);
			tr_->getFlip() = true;
		}

		if (dir.magnitude() != 0) {
			dir = dir.normalize();

			if (attribs_ != nullptr)
				speed_ = attribs_->getVel();

			goalVel_ = baseSpeed_ + Vector2D(dir.getX() * speed_.getX(), dir.getY() * speed_.getY());
		}

		lastDir_ = dir; //Recogemos siempre la �ltima direcci�n para quien la necesite

		if (!keymap.at(UP) && !keymap.at(DOWN) && !keymap.at(LEFT) && !keymap.at(RIGHT)) {		//Deceleracion
			if (col_ != nullptr) {
				vel.setX(sdlutils().lerp(vel.getX(), baseSpeed_.getX(), 0.25));
				vel.setY(sdlutils().lerp(vel.getY(), baseSpeed_.getY(), 0.25));
			}
			//ANIMACION DE IDLE

		}
		else if (hms_->canMove()) {		//Aceleracion
			if (col_ != nullptr) {
				vel.setX(sdlutils().lerp(goalVel_.getX(), vel.getX(), 0.9));
				vel.setY(sdlutils().lerp(goalVel_.getY(), vel.getY(), 0.9));
			}
		}
		else {
			//porque esta kaput el bixo
			if (col_ != nullptr) {
				vel.setX(sdlutils().lerp(vel.getX(), 0, 0.25));
				vel.setY(sdlutils().lerp(vel.getY(), 0, 0.25));
			}
		}
		//1-0.85/2
		SDL_Rect rectPlayer = tr_->getRectCollide();
		rectPlayer.x += vel.getX();
		rectPlayer.y += vel.getY();
		
		if (col_ != nullptr)
			col_->tryToMove(dir, goalVel_, rectPlayer, false);		//Intenta moverse
		
		if(grav_->isActive())
			grav_->checkHeight(rectPlayer);					//Comprobamos que no tenga que subir un escalon

		if (grav_->getStuck())			vel.setX(0);				//Si lo tiene que subir y no salta no se mueve en x

	//SALTO	
		if (z <= grav_->getFloor()) {
			auto* combo = entity_->getComponent<Combos>();
			if (combo != nullptr) {
				// Inicio del salto
				if (keymap.at(SPACE)) {
					combo->checkCombo(2);
					//entity_->getComponent<Stroke>()->increaseChance(2, false); No necesario, no te infartas
					velZ = jump_;
					keymap.at(SPACE) = false;
				}
				// Fin del salto
				if (velZ < grav_->getFloor()) {
					combo->popUntilEmpty();
					/*keymap.at(SPACE) = false;*/
				}
			}
		}
	}
}

void MovementInChase::onEnable() {
	animState_->setAnimBool(HamStatesAnim::IDLE, false);
	animState_->setAnimBool(HamStatesAnim::MOVE, true);
}

void MovementInChase::onDisable()
{
	auto& vel = tr_->getVel();
	vel = Vector2D();
	animState_->setAnimBool(HamStatesAnim::MOVE, false);
	animState_->setAnimBool(HamStatesAnim::IDLE, true);
}

void MovementInChase::onResume() {

}