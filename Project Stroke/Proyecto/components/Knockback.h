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

	virtual ~Knockback() {}

	void init() override;
	void knockback();
	inline void setKnockbackDistance(int val) { knockbackVel_ = val; }

private:
	Transform* tr_;
	int knockbackVel_;
	//bool isStunned_;
}
;