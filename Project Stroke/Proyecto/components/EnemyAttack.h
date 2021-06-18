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

#include "SoundManager.h"

class EnemyAttack : public Component {
public:
	EnemyAttack();
	EnemyAttack(int cdMin, int cdMax);

	virtual ~EnemyAttack() {}

	void init() override;
	void update() override;
	void render() override;

	bool CheckCollisions(const SDL_Rect& enemyRect, bool finCombo);
	bool LaunchAttack();

private:
	Transform* tr_;
	SDL_Rect attRect_;
	Animator* anim_;
	bool DEBUG_isAttacking_;
	long unsigned int minCD_, maxCD_,
					  cooldown_, time_;

	SDL_Rect cam;
}
;