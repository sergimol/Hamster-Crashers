#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "EntityAttribs.h"
#include "Transform.h"
#include "HamsterStateMachine.h"
#include "ControlHandler.h"
#include "LightAttack.h"
#include "strongAttack.h"

class Stun : public Component {
public:
	Stun();

	virtual ~Stun() {}

	void init() override;
	void update() override;

	void restartStunTime();

	inline void setStunCooldown(long unsigned cd) { cooldown_ = cd; }

private:
	HamsterStateMachine* hamState_;
	ControlHandler* hamCtrl_;
	LightAttack* lghtAtt_;
	StrongAttack* strAtt_;
	long unsigned int cooldown_, time_;
}
;