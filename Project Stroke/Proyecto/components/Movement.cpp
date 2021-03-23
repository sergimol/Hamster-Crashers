#include "Movement.h"
#include "Stroke.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

void Movement:: init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

	speed_ = entity_->getComponent<EntityAttribs>()->getVel();
	assert(speed_ != Vector2D());

	keymap.insert({ UP, false });
	keymap.insert({ DOWN, false });
	keymap.insert({ RIGHT, false });
	keymap.insert({ LEFT, false });
	keymap.insert({ SPACE, false });

}

void Movement::updateKeymap(KEYS x, bool is) {
	if (x != SPACE)
	keymap.at(x) = is;
	else if (!keymap.at(SPACE)) {
		keymap.at(SPACE) = true;
		entity_->getComponent<Stroke>()->increaseChance(2, this);
	}
}
void Movement:: update() {

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


	if (ih().keyDownEvent() || ih().keyUpEvent()) {

		
	}

	if (dir.magnitude() != 0) {
		dir = dir.normalize();

		goalVel_ = Vector2D(dir.getX() * speed_.getX(), dir.getY() * speed_.getY());
	}

	lastDir_ = dir; //Recogemos siempre la última dirección para quien la necesite

	if (!keymap.at(UP) && !keymap.at(DOWN) && !keymap.at(LEFT) && !keymap.at(RIGHT)) {		//Deceleracion
		vel.setX(lerp(vel.getX(), 0, 0.25));
		vel.setY(lerp(vel.getY(), 0, 0.25));
		
		//ANIMACION DE IDLE
		if(state != HamStates::IDLE)
			anim_->play(Vector2D(0, 0), Vector2D(2, 0), 220);
		if(state != HamStates::JUMPING) state = HamStates::IDLE;
	
	}
	else if (state == HamStates::IDLE || state == HamStates::MOVING || state == HamStates::JUMPING) {		//Aceleracion
		vel.setX(lerp(goalVel_.getX(), vel.getX(), 0.9));
		vel.setY(lerp(goalVel_.getY(), vel.getY(), 0.9));

		//ANIMACION DE MOVIMIENTO
		if (state != HamStates::MOVING)
			anim_->play(Vector2D(0, 1), Vector2D(2, 2), 100);
		if(state != HamStates::JUMPING) state = HamStates::MOVING;

	}

	if ((state == HamStates::IDLE || state == HamStates::MOVING) && keymap.at(SPACE)) {		//Inicio del salto
		velZ = jump_;
		state = HamStates::JUMPING;
		timer = sdlutils().currRealTime();
	}

	if (z > 0 && sdlutils().currRealTime() > timer + jumpTimer_) {			//Aceleracion del salto afectado por gravedad
		velZ -= gravity_;
		timer = sdlutils().currRealTime();
	}

	else if (z < 0) {			//Final del salto	!!!!!!!!!(0 SE SUSTITUIRA POR LA Z DEL MAPA)!!!!!!!!
		keymap.at(SPACE) = false;
		velZ = 0;
		z = 0;
		state = HamStates::IDLE;
		timer = sdlutils().currRealTime();
	}

}

float Movement::lerp(float a, float b, float f)
{
	return (a + f * (b - a));
}

void Movement::onEnable(){
	if(tr_->getVel() == Vector2D(0,0))
		anim_->play(Vector2D(0, 0), Vector2D(2, 0), 220); // Idle
	else
		anim_->play(Vector2D(0, 1), Vector2D(2, 2), 100);
}

void Movement::onDisable()
{
	auto& vel = tr_->getVel();
	vel = Vector2D();
}