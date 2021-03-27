#include "MovementSimple.h"
#include "Stroke.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

void MovementSimple:: init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	/*
	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);
	*/

	/*
	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);
	*/

	speed_ = entity_->getComponent<EntityAttribs>()->getVel();
	assert(speed_ != Vector2D());

	keymapSimple.insert({ UP, false });
	keymapSimple.insert({ DOWN, false });
	keymapSimple.insert({ RIGHT, false });
	keymapSimple.insert({ LEFT, false });
	keymapSimple.insert({ SPACE, false });
}

void MovementSimple::updateKeymap(KEYS x, bool is) {
	if (!keymapSimple.empty()) {

		if (x != SPACE)
		keymapSimple.at(x) = is;
		/*else*/ if (!keymapSimple.at(SPACE)) {
			keymapSimple.at(SPACE) = true;
			/*
			entity_->getComponent<Stroke>()->increaseChance(2, this);
			*/
		}
	}
}
void MovementSimple:: update() {

	auto& vel = tr_->getVel();
	//auto& state = hms_->getState();
	auto& z = tr_->getZ();
	auto& velZ = tr_->getVelZ();

	Vector2D dir = Vector2D(0, 0);

	if (keymapSimple.at(UP)) {
		dir.setY(-1.0f);
	}
	else if (keymapSimple.at(DOWN)) {
		dir.setY(1.0f);
	}

	if (keymapSimple.at(RIGHT)) {
		dir.setX(1.0f);
		tr_->getFlip() = false;
	}
	else if (keymapSimple.at(LEFT)) {
		dir.setX(-1.0f);
		tr_->getFlip() = true;
	}


	if (ih().keyDownEvent() || ih().keyUpEvent()) {

		
	}

	if (dir.magnitude() != 0) {
		dir = dir.normalize();

		goalVel_ = Vector2D(dir.getX() * speed_.getX(), dir.getY() * speed_.getY());
	}

	lastDir_ = dir; //Recogemos siempre la última dirección para quien la necesite

	if (!keymapSimple.at(UP) && !keymapSimple.at(DOWN) && !keymapSimple.at(LEFT) && !keymapSimple.at(RIGHT)) {		//Deceleracion
		vel.setX(lerp(vel.getX(), 0, 0.25));
		vel.setY(lerp(vel.getY(), 0, 0.25));
		
		//ANIMACION DE IDLE
		/*
		if(state != HamStates::IDLE)
			anim_->play(Vector2D(0, 0), Vector2D(2, 0), 220);
		if(state != HamStates::JUMPING) state = HamStates::IDLE;
		*/
	
	}
	else  {		//Aceleracion
		vel.setX(lerp(goalVel_.getX(), vel.getX(), 0.9));
		vel.setY(lerp(goalVel_.getY(), vel.getY(), 0.9));

		//ANIMACION DE MOVIMIENTO
		/*
		if (state != HamStates::MOVING)
			anim_->play(Vector2D(0, 1), Vector2D(2, 2), 100);
		if(state != HamStates::JUMPING) state = HamStates::MOVING;
		*/

	}

	if (keymapSimple.at(SPACE)) {		//Inicio del salto
		velZ = jump_;
		//state = HamStates::JUMPING;
		timer = sdlutils().currRealTime();
	}

	if (z > 0 && sdlutils().currRealTime() > timer + jumpTimer_) {			//Aceleracion del salto afectado por gravedad
		velZ -= gravity_;
		timer = sdlutils().currRealTime();
	}

	else if (z < 0) {			//Final del salto	!!!!!!!!!(0 SE SUSTITUIRA POR LA Z DEL MAPA)!!!!!!!!
		keymapSimple.at(SPACE) = false;
		velZ = 0;
		z = 0;
		//state = HamStates::IDLE;
		timer = sdlutils().currRealTime();
	}

}

float MovementSimple::lerp(float a, float b, float f)
{
	return (a + f * (b - a));
}

void MovementSimple::onEnable(){
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