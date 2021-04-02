#include "EnemyStun.h"

EnemyStun::EnemyStun() :
	enmState_(nullptr), cooldown_(1500), time_(sdlutils().currRealTime()), flwPlayer_(nullptr) {}

void EnemyStun::init() {
	enmState_ = entity_->getComponent<EnemyStateMachine>();
	assert(enmState_ != nullptr);

	flwPlayer_ = entity_->getComponent<FollowPlayer>();
	assert(flwPlayer_ != nullptr);
}

void EnemyStun::update() {
	auto& state = enmState_->getState();
	if (state == EnemyStates::ENM_STUNNED) {
		//Deja de estar stunneado
		if (sdlutils().currRealTime() > time_ + cooldown_) {
			flwPlayer_->setActive(true);
			state = EnemyStates::ENM_IDLE;
		}
	}
}

void EnemyStun::restartStunTime() {
	time_ = sdlutils().currRealTime(); 
}