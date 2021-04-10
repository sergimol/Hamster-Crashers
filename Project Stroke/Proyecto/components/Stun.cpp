#include "Stun.h"

Stun::Stun() :
	hamState_(nullptr), cooldown_(300), time_(sdlutils().currRealTime()), hamCtrl_(nullptr), strAtt_(nullptr), lghtAtt_(nullptr) {}

void Stun::init() {
	hamState_ = entity_->getComponent<HamsterStateMachine>();
	assert(hamState_ != nullptr);

	hamCtrl_ = entity_->getComponent<ControlHandler>();
	assert(hamCtrl_ != nullptr);

	strAtt_ = entity_->getComponent<StrongAttack>();
	assert(strAtt_ != nullptr);

	lghtAtt_ = entity_->getComponent<LightAttack>();
	assert(lghtAtt_ != nullptr);
}

void Stun::update() {
	auto& state = hamState_->getState();
	if (state == HamStates::STUNNED) {
		//Deja de estar stunneado
		if (sdlutils().currRealTime() > time_ + cooldown_) {
			strAtt_->setActive(true);
			lghtAtt_->setActive(true);
			hamCtrl_->setActive(true);
			state = HamStates::IDLE;
		}
	}
}

void Stun::restartStunTime() {
	time_ = sdlutils().currRealTime();
}