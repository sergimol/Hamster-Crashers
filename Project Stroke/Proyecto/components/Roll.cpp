#include "Roll.h"
#include "Movement.h"
#include "Animator.h"

Roll::Roll() :
	Ability() {
};

Roll::~Roll() {
	//me follo a tu madre
}

void Roll::init() {
	Ability::init();
	state_ = st_->getState();
}

void Roll::update() {
	if (ih().keyDownEvent() && (state_ == HamStates::IDLE || state_ == HamStates::MOVING)) {
		if (ih().isKeyDown(key_)) {

			entity_->getComponent<Movement>()->setActive(!entity_->getComponent<Movement>()->isActive());
			entity_->getComponent<Transform>()->getVel().set(0, 0);
		}
	}
}

float Roll::lerp(float a, float b, float f){
	return (a + f * (b - a));
}

void Roll::accion() {

}
