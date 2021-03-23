#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include <map>
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "HamsterStateMachine.h"
#include "Animator.h"
#include "EntityAttribs.h"

class Movement : public Component {
public:

	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	Movement() :
		tr_(nullptr), hms_(nullptr), anim_(nullptr), speed_(), goalVel_(0, 0), lastDir_(1,0), timer(sdlutils().currRealTime()) {
	}

	virtual ~Movement() {
	}

	void init() override;

	void update() override;

	void updateKeymap(KEYS x, bool is);

	float lerp(float a, float b, float f);

	virtual void onDisable() override;

	Vector2D getLastDir() { return lastDir_; };

protected:
private:

	const float jump_ = 45.0f, gravity_ = 4.8f, jumpTimer_ = 10.0f;
	long unsigned int timer;

	Transform* tr_;
	HamsterStateMachine* hms_;
	Animator* anim_;
	Vector2D speed_, goalVel_, lastDir_;
	
	std::map<KEYS, bool> keymap;
};

