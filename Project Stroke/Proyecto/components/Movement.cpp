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

void Movement::updateKeymap(KEYS x, bool is) {
	if (x != SPACE || (!keymap.at(SPACE) && tr_->getZ() <= grav_->getFloor()))
		keymap.at(x) = is;
}

void Movement::update() {

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
			tr_->getFlip() = false;
		}
		else if (keymap.at(LEFT)) {
			dir.setX(-1.0f);
			tr_->getFlip() = true;
		}

		if (dir.magnitude() != 0) {
			dir = dir.normalize();

			if (attribs_ != nullptr)
				speed_ = attribs_->getVel();

			goalVel_ = Vector2D(dir.getX() * speed_.getX(), dir.getY() * speed_.getY());
		}

		lastDir_ = dir; //Recogemos siempre la �ltima direcci�n para quien la necesite

		if (!keymap.at(UP) && !keymap.at(DOWN) && !keymap.at(LEFT) && !keymap.at(RIGHT)) {		//Deceleracion
			if (col_ != nullptr) {
				vel.setX(sdlutils().lerp(vel.getX(), 0, 0.25));
				vel.setY(sdlutils().lerp(vel.getY(), 0, 0.25));
			}
			//ANIMACION DE IDLE
			if (animState_ != nullptr) {
				animState_->setAnimBool(HamStatesAnim::MOVE, false);
				animState_->setAnimBool(HamStatesAnim::IDLE, true);
			}
		}
		else if (hms_->canMove()) {		//Aceleracion
			if (col_ != nullptr) {
				vel.setX(sdlutils().lerp(goalVel_.getX(), vel.getX(), 0.9));
				vel.setY(sdlutils().lerp(goalVel_.getY(), vel.getY(), 0.9));
			}
			//ANIMACION DE MOVIMIENTO
			if (animState_ != nullptr) {
				animState_->setAnimBool(HamStatesAnim::MOVE, true);
				animState_->setAnimBool(HamStatesAnim::IDLE, false);
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
		rectPlayer.x += goalVel_.getX();
		rectPlayer.y += goalVel_.getY() + tr_->getFloor();
		
		SDL_Rect footPlayer = tr_->getRectCollideFeet();
		footPlayer.x += goalVel_.getX();
		footPlayer.y += goalVel_.getY() + tr_->getFloor();

		if (col_ != nullptr) {
			col_->tryToMove(dir, goalVel_, rectPlayer, false);		//Intenta moverse
			col_->tryToMoveObs(dir, goalVel_, footPlayer, false);		//Intenta moverse
		}
		rectPlayer.y -= tr_->getFloor();
		if(grav_->isActive())
			grav_->checkHeight(rectPlayer);					//Comprobamos que no tenga que subir un escalon

		if (grav_->getStuck()) vel.setX(0);				//Si lo tiene que subir y no salta no se mueve en x

		if (grav_->GetHeighCh() && jump_ != 45.0f) jump_ = 45.0f;
		else if(!grav_->GetHeighCh() && jump_ != 35.0f) jump_ = 35.0f;

	//SALTO
		if (z <= grav_->getFloor()) {
			auto* combo = entity_->getComponent<Combos>();
			if (combo != nullptr) {
				// Inicio del salto
				if (keymap.at(SPACE)) {
					combo->checkCombo(2);
					//entity_->getComponent<Stroke>()->increaseChance(1, false); Qué os parece si hago que el salto no de infarto eh guapos
					velZ = jump_;
					keymap.at(SPACE) = false;
				}
				// Fin del salto
				if (velZ < 0) {
					combo->popUntilEmpty();
					/*keymap.at(SPACE) = false;*/
				}
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
	//auto& vel = tr_->getVel();
	//vel = Vector2D();
}

void Movement::onResume() {

}