#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "Transform.h"

class Knockback : public Component {
public:
	Knockback();

	virtual ~Knockback() {};

	void init() override;
	void knockback();
	void knockback(int kVel);
	void doKnockback(int kVel);
	inline void setKnockbackDistance(int val) { knockbackVel_ = val; }
	inline int getKnockback() const { return knockbackVel_; }

private:
	Transform* tr_;
	int knockbackVel_;
	AnimHamsterStateMachine* hms_;
	//bool isStunned_;
};