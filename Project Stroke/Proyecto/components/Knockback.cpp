#include "Knockback.h"
#include "AnimHamsterStateMachine.h"

Knockback::Knockback() :
	tr_(nullptr), knockbackVel_(5) {
}

void  Knockback::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	hms_ = entity_->getComponent<AnimHamsterStateMachine>();
}

void Knockback::knockback() {
	if (hms_ == nullptr)
		doKnockback(knockbackVel_);
	else if (hms_->getState() != HamStatesAnim::STROKE_ALONE)
		doKnockback(knockbackVel_);
	else {
		tr_->setVel(Vector2D(0, 0));
		auto hm = entity_->getComponent<HamsterStateMachine>();
		if (hm != nullptr) hm->getState() = HamStates::INFARCTED_ALONE;
		hms_->setAnimBool(HamStatesAnim::STUNNED, false);
	}
}

void Knockback::knockback(int kVel) {
	if (hms_ == nullptr)
		doKnockback(kVel);
	else if (hms_->getState() != HamStatesAnim::STROKE_ALONE)
		doKnockback(kVel);
	else {
		tr_->setVel(Vector2D(0, 0));
		auto hm = entity_->getComponent<HamsterStateMachine>();
		if (hm != nullptr) hm->getState() = HamStates::INFARCTED_ALONE;
		hms_->setAnimBool(HamStatesAnim::STUNNED, false);
	}
}

void Knockback::doKnockback(int kVel) {
	bool flip = tr_->getFlip();
	auto& vel = tr_->getVel();
	//anim de caerse de culo
	if (flip) {
		vel.setX(kVel);
	}
	else {
		vel.setX(-kVel);
	}
}