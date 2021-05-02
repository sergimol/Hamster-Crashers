#include "Knockback.h"

Knockback::Knockback() :
	tr_(nullptr), knockbackVel_(5) {}

void  Knockback::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Knockback::knockback() {
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

void Knockback::knockback(int kVel) {
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