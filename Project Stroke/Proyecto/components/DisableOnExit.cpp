// This file is part of the course TPV2@UCM - Samir Gena
#include "DisableOnExit.h"

DisableOnExit::DisableOnExit() :
	tr_(nullptr) {
}

DisableOnExit::~DisableOnExit() {
}

void DisableOnExit::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void DisableOnExit::update() {
	auto& pos = tr_->getPos();
	auto w = tr_->getW();
	auto h = tr_->getH();

	if (entity_->hasGroup<Bullet_group>()) {
		if (pos.getX() < 0) {
			entity_->setActive(false);
		}
		else if (pos.getX() + w > sdlutils().width()) {
			entity_->setActive(false);
		}
		else if (pos.getY() < 0) {
			entity_->setActive(false);
		}
		else if (pos.getY() + h > sdlutils().height()) {
			entity_->setActive(false);
		}
	}
}


