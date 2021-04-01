#include "EnemyStun.h"

EnemyStun::EnemyStun() :
	tr_(nullptr), enmState_(nullptr), cooldown_(1500), time_(sdlutils().currRealTime()),
	flwPlayer_(nullptr), isStunned_(false), knockbackVel_(50) {}

void EnemyStun::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	enmState_ = entity_->getComponent<EnemyStateMachine>();
	assert(enmState_ != nullptr);

	flwPlayer_ = entity_->getComponent<FollowPlayer>();
	assert(flwPlayer_ != nullptr);
}

void EnemyStun::update() {
	auto& state = enmState_->getState();
	if (state == EnemyStates::ENM_STUNNED) {
		//Sufre el estado del stun
		if (!isStunned_) {

			flwPlayer_->setActive(false);

			isStunned_ = true;

			knockback();
			time_ = sdlutils().currRealTime();
		}
		else if(sdlutils().currRealTime() > time_ + cooldown_) {
			//Deja de estar stunneado
			isStunned_ = false;
			flwPlayer_->setActive(true);
			state = EnemyStates::ENM_IDLE;
		}
	}
}

void EnemyStun::knockback() {
	bool flip = tr_->getFlip();
	auto& vel = tr_->getVel();
	//anim de caerse de culo
	if (flip) {
		vel.setX(knockbackVel_);
	}
	else {
		vel.setX(-knockbackVel_);
	}
}
