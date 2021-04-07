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
#include "EnemyStateMachine.h"
#include "../game/Game.h"

class LightAttack : public Component {
public:
	LightAttack();

	virtual ~LightAttack() {}

	void init() override;
	void update() override;
	void render() override;

	bool CheckCollisions(const SDL_Rect& rectPlayer, bool finCombo);

	void attack();

private:
	Transform* tr_;
	SDL_Rect attRect_;
	HamsterStateMachine* hms_;
	bool DEBUG_isAttacking_;
	long unsigned int cooldown_, time_;
	SoundEffect& attackSound_, & hitSound_;
	int player_;
}
;