#pragma once

#include <SDL.h>
#include <cassert>
#include "../utils/checkML.h"

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "EntityAttribs.h"
#include "Transform.h"
#include "HamsterStateMachine.h"
#include "../game/Game.h"

class EnemyStrongAttack : public Component {
public:
	EnemyStrongAttack();

	virtual ~EnemyStrongAttack() {}

	void init() override;
	void update() override;
	void render() override;

	bool CheckCollisions(const SDL_Rect& enemyRect, bool finCombo);
	bool LaunchAttack();

	inline bool getAttackStarted() {
		return attackStarted_;
	}

private:
	Transform* tr_;
	SDL_Rect attRect_;
	Animator* anim_;
	bool DEBUG_isAttacking_;
	long unsigned int cooldown_, time_;
	SoundEffect& attackSound_, & hitSound_;
	SDL_Rect cam;

	float durationTime_;
	float attackDurationCD_;
	float beforeHitCD_;

	bool attackStarted_;
}
;