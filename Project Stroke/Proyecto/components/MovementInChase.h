#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include <map>
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "HamsterStateMachine.h"
#include "Animator.h"
#include "EntityAttribs.h"
#include "CollisionDetec.h"

class MovementInChase : public Component {
public:

	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	MovementInChase() :
		tr_(nullptr), hms_(nullptr), anim_(nullptr), speed_(), goalVel_(0, 0), grav_(nullptr), lastDir_(1,0), state_(nullptr) {
	}

	virtual ~MovementInChase() {
	}

	void init() override;

	void update() override;

	void onResume() override;

	void updateKeymap(KEYS x, bool is);

	virtual void onEnable() override;
	virtual void onDisable() override;

	Vector2D getLastDir() { return lastDir_; };

protected:
private:

	const float jump_ = 35.0f, gravity_ = 4.8f, jumpTimer_ = 10.0f;

	Transform* tr_;
	CollisionDetec* col_;
	HamsterStateMachine* hms_;
	Animator* anim_;
	Gravity* grav_;
	GameStates* state_;
	AnimHamsterStateMachine* animState_;
	EntityAttribs* attribs_;
	/*Combos* comb_;
	Stroke* stroke_;*/
	Vector2D speed_, goalVel_, lastDir_;

	const Vector2D baseSpeed_ = Vector2D(-5, 0);
	
	std::map<KEYS, bool> keymap;
};

