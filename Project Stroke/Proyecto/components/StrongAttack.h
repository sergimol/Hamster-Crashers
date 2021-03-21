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

class StrongAttack : public Component {
public:
	StrongAttack();

	virtual ~StrongAttack() {};

	void init() override;
	void update() override;
	bool CheckCollisions(const SDL_Rect& rectPlayer, bool finCombo);

private:
	Transform* tr_;
	HamsterStateMachine* hms_;
	short unsigned int w_, h_;
	long unsigned int cooldown_, time_;
	SoundEffect& attackSound_, &hitSound_;
}
;