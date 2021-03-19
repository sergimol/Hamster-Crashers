#include "Roll.h"
#include "Movement.h"
#include "Animator.h"

Roll::Roll() : Ability() {
};

Roll::~Roll() {
	//me follo a tu madre
}

float Roll::lerp(float a, float b, float f){
	return (a + f * (b - a));
}

void Roll::action() 
{
	entity_->getComponent<Movement>()->setActive(!entity_->getComponent<Movement>()->isActive());
}
