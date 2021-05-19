#include "MovementSimple.h"
#include "Stroke.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "AnimEnemyStateMachine.h"

//Para comprobar las colisiones
#include "MapMngr.h"

void MovementSimple::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	enmState_ = entity_->getComponent<EnemyStateMachine>();
	assert(enmState_ != nullptr);

	colDetec_ = entity_->getComponent<CollisionDetec>();
	/*
	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);
	*/
	grav_ = entity_->getComponent<Gravity>();
	//assert(grav_ != nullptr);

	attribs_ = entity_->getComponent<EntityAttribs>();
	speed_ = attribs_->getVel();
	assert(speed_ != Vector2D());

	if (colDetec_ != nullptr)
		colDetec_->setMovement(this);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);

	keymapSimple_.insert({ UP, false });
	keymapSimple_.insert({ DOWN, false });
	keymapSimple_.insert({ RIGHT, false });
	keymapSimple_.insert({ LEFT, false });
	keymapSimple_.insert({ SPACE, false });
}

// Activa el movimiento en la direcci�n indicada
void MovementSimple::updateKeymap(KEYS x, bool is) {
	if (!keymapSimple_.empty()) {

		if (x != SPACE)
			keymapSimple_.at(x) = is;
		//if (!keymapSimple.at(SPACE)) {
		//	keymapSimple.at(SPACE) = true;
		//}
	}
}
void MovementSimple::update() {
	if (state_->getState() == GameStates::RUNNING) {
		auto& vel = tr_->getVel();
		//auto& state = enmState_->getState();
		auto& z = tr_->getZ();
		auto& velZ = tr_->getVelZ();

		Vector2D dir = Vector2D(0, 0);

		//Cogemos el mapa para comprobar luego las colisiones
		auto map = entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>();

		if (keymapSimple_.at(UP)) {
			dir.setY(-1.0f);
		}
		else if (keymapSimple_.at(DOWN)) {
			dir.setY(1.0f);
		}

		if (keymapSimple_.at(RIGHT)) {
			dir.setX(1.0f);
			tr_->getFlip() = false;
		}
		else if (keymapSimple_.at(LEFT)) {
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


		if (!keymapSimple_.at(UP) && !keymapSimple_.at(DOWN) && !keymapSimple_.at(LEFT) && !keymapSimple_.at(RIGHT)) {		//Deceleracion
			vel.setX(sdlutils().lerp(vel.getX(), 0, 0.25));
			vel.setY(sdlutils().lerp(vel.getY(), 0, 0.25));

			//ANIMACION DE IDLE

		//ANIMACION DE IDLE
			if (entity_->getComponent<AnimEnemyStateMachine>() != nullptr)
			{
				entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::MOVE, false);
				entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::IDLE, true);
			}
			/*if (state != EnemyStates::ENM_IDLE)
				anim_->play(Vector2D(0, 0), Vector2D(2, 0), 220);*/

				/*if(state != EnemyStates::JUMPING) state = EnemyStates::IDLE;
				*/

		}
		else {		//Aceleracion
			vel.setX(sdlutils().lerp(goalVel_.getX(), vel.getX(), 0.9));
			vel.setY(sdlutils().lerp(goalVel_.getY(), vel.getY(), 0.9));

			//ANIMACION DE MOVIMIENTO

		//ANIMACION DE MOVIMIENTO
			if (entity_->getComponent<AnimEnemyStateMachine>() != nullptr)
			{
				entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::MOVE, true);
				entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::IDLE, false);
			}

			/*if (state != EnemyStates::ENM_MOVING)
				anim_->play(Vector2D(0, 1), Vector2D(2, 2), 100);*/


				//if(state != EnemyStates::JUMPING) state = EnemyStates::MOVING;
		}

		//Si me voy a chocar con una pared...
		if (colDetec_ != nullptr) {
			//Cojo el rect del player y le sumo la supuesta siguiente posicion
			SDL_Rect rectEnemy = tr_->getRectCollide();
			rectEnemy.x += vel.getX();
			rectEnemy.y += vel.getY() + tr_->getFloor();

			SDL_Rect rectFoot = tr_->getRectCollide();
			rectFoot.x += goalVel_.getX();
			rectFoot.y += goalVel_.getY() + tr_->getFloor();
			
			colDetec_->tryToMove(dir, goalVel_, rectEnemy, true);
			colDetec_->tryToMoveObs(dir, goalVel_, rectFoot, true);

			if (grav_ != nullptr && grav_->isActive())
				grav_->checkHeight(rectEnemy);					//Comprobamos que no tenga que subir un escalon
		}
	}
}

void MovementSimple::onEnable() {
	if (tr_->getVel() == Vector2D(0, 0)) {}
	//anim_->play(Vector2D(0, 0), Vector2D(2, 0), 220); // Idle
//else
	//anim_->play(Vector2D(0, 1), Vector2D(2, 2), 100);
}

void MovementSimple::onDisable()
{
	auto& vel = tr_->getVel();
	vel = Vector2D();
}

void MovementSimple::onResume() {
	timer = sdlutils().currRealTime() - timer;
}