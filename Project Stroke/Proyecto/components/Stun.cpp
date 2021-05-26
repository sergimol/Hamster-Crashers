#include "Stun.h"

Stun::Stun() :
	hamState_(nullptr), cooldown_(200), time_(sdlutils().currRealTime()), hamCtrl_(nullptr), strAtt_(nullptr), lghtAtt_(nullptr) {}

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
			if (!entity_->getComponent<MovementInChase>()->isActive()) {
				strAtt_->setActive(true);
				lghtAtt_->setActive(true);
			}

			hamCtrl_->setActive(true);

			auto animHamsterState = entity_->getComponent<AnimHamsterStateMachine>();
			//Reseteamos las animaciones
			animHamsterState->resetAnim();

			if (entity_->getComponent<MovementInChase>()->isActive()) {
				animHamsterState->setAnimBool(HamStatesAnim::IDLE, false);
				animHamsterState->setAnimBool(HamStatesAnim::MOVE, true);
			}

			state = HamStates::DEFAULT;
		}
	}
	else if (!hamCtrl_->isActive() && state == HamStates::INFARCTED) {
		//Recupera el control si recibe un infarto
		hamCtrl_->setActive(true);
	}
}

void Stun::restartStunTime() {
	time_ = sdlutils().currRealTime();
}