#include "Movement.h"
#include "Stroke.h"
#include "Combos.h"
#include "AnimHamsterStateMachine.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

//Para comprobar las colisiones
#include "CollisionDetec.h"

void Movement::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

	speed_ = entity_->getComponent<EntityAttribs>()->getVel();
	assert(speed_ != Vector2D());

	grav_ = entity_->getComponent<Gravity>();
	assert(grav_ != nullptr);

	col_ = entity_->getComponent<CollisionDetec>();
	assert(col_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);

	keymap.insert({ UP, false });
	keymap.insert({ DOWN, false });
	keymap.insert({ RIGHT, false });
	keymap.insert({ LEFT, false });
	keymap.insert({ SPACE, false });

}

void Movement::updateKeymap(KEYS x, bool is) {
	if (x != SPACE || !keymap.at(SPACE))
		keymap.at(x) = is;
}

void Movement::update() {

	if (state_->getState() != GameStates::PAUSE) {
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
			tr_->getFlip() = false;
		}
		else if (keymap.at(LEFT)) {
			dir.setX(-1.0f);
			tr_->getFlip() = true;
		}

		if (dir.magnitude() != 0) {
			dir = dir.normalize();

			goalVel_ = Vector2D(dir.getX() * speed_.getX(), dir.getY() * speed_.getY());
		}

		lastDir_ = dir; //Recogemos siempre la última dirección para quien la necesite

		if (!keymap.at(UP) && !keymap.at(DOWN) && !keymap.at(LEFT) && !keymap.at(RIGHT)) {		//Deceleracion

			vel.setX(col_->lerp(vel.getX(), 0, 0.25));
			vel.setY(col_->lerp(vel.getY(), 0, 0.25));

			//ANIMACION DE IDLE
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::MOVE, false);
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::IDLE, true);
		}
		else if (hms_->canMove()) {		//Aceleracion

			vel.setX(col_->lerp(goalVel_.getX(), vel.getX(), 0.9));
			vel.setY(col_->lerp(goalVel_.getY(), vel.getY(), 0.9));

			//ANIMACION DE MOVIMIENTO
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::MOVE, true);
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::IDLE, false);
		}
		else {
			//porque esta kaput el bixo

			vel.setX(col_->lerp(vel.getX(), 0, 0.25));
			vel.setY(col_->lerp(vel.getY(), 0, 0.25));
		}
		//1-0.85/2
		SDL_Rect rectPlayer = tr_->getRectCollide();
		rectPlayer.x += vel.getX();
		rectPlayer.y += vel.getY();

		col_->tryToMove(dir, goalVel_, rectPlayer, false);		//Intenta moverse
		grav_->checkHeight(rectPlayer);					//Comprobamos que no tenga que subir un escalon

		if (grav_->getStuck()) vel.setX(0);				//Si lo tiene que subir y no salta no se mueve en x

	//SALTO
		if (z <= grav_->getFloor()) {
			// Inicio del salto
			if (keymap.at(SPACE)) {
				entity_->getComponent<Combos>()->checkCombo(2);
				entity_->getComponent<Stroke>()->increaseChance(2, false);
				velZ = jump_;
				keymap.at(SPACE) = false;
			}
			// Fin del salto
			if (velZ < grav_->getFloor()) {
				entity_->getComponent<Combos>()->popUntilEmpty();
				/*keymap.at(SPACE) = false;*/
			}
		}
	}
}

void Movement::onEnable() {
	if (tr_->getVel() == Vector2D(0, 0))
		anim_->play(sdlutils().anims().at("sardinilla_idle")); // Idle
	else
		anim_->play(sdlutils().anims().at("sardinilla_move")); //Movimiento
}

void Movement::onDisable()
{
	auto& vel = tr_->getVel();
	vel = Vector2D();
}

void Movement::onResume() {

}