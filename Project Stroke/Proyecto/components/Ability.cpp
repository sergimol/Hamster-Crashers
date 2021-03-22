#include "Ability.h"

void Ability::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	st_ = entity_->getComponent<HamsterStateMachine>();
	assert(st_ != nullptr);

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

	state_ = st_->getState();
}

void Ability::update() {
	if (ih().keyDownEvent() && (state_ == HamStates::IDLE || state_ == HamStates::MOVING)) {
		if (ih().isKeyDown(key_) && sdlutils().currRealTime() > timer_)
		{
			timer_ = sdlutils().currRealTime() + cooldown_;
			action();

		}
	}
}