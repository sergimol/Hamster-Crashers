// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class DeAcceleration: public Component {
public:
	DeAcceleration() :
			tr_(nullptr) {
	}
	virtual ~DeAcceleration() {
	}
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		auto &vel = tr_->getVel();
		vel = vel * 0.995f;
	}

private:
	Transform *tr_;
};

