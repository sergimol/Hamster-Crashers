#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include <map>
#include "Transform.h"
#include "HamsterStateMachine.h"

class Movement : public Component {
public:
	Movement() :
		tr_(nullptr), hms_(nullptr), speed_(7.0f, 3.5f), goalVel_(0, 0), jump_(0) {
	}

	virtual ~Movement() {
	}

	void init() override;

	void update() override;

	float lerp(float a, float b, float f);

private:
	Transform* tr_;
	HamsterStateMachine* hms_;
	Vector2D speed_, goalVel_;
	float jump_;
	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	std::map<KEYS, bool> keymap;
};

