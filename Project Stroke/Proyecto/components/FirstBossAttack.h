﻿#pragma once

#include <SDL.h>
#include <cassert>

#include "../game/Game.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "EntityAttribs.h"
#include "Transform.h"
#include "HamsterStateMachine.h"
#include "EntityAttribs.h"
#include "GameStates.h"

class FirstBossAttack : public Component {
public:
	FirstBossAttack();

	virtual ~FirstBossAttack() {}

	void init() override;
	void update() override;
	void render() override;
	void onResume() override;

	bool CheckCollisions(const SDL_Rect& enemyRect, bool finCombo);
	bool LaunchAttack();

	inline bool getAttackStarted() {
		return attackStarted_;
	}

private:
	Transform* tr_;
	EntityAttribs* eAttribs_;

	SDL_Rect attRect_;
	Animator* anim_;
	bool DEBUG_isAttacking_;
	long unsigned int cooldown_, time_;
	SoundEffect& attackSound_, & hitSound_;
	SDL_Rect cam;

	float hitTime_;
	float beforeHitCD_;
	float afterHitCD_;

	bool attackStarted_;
	bool stunStarted_;
	GameStates* state_;
}
;