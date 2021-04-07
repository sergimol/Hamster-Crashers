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
#include "../game/Game.h"

class ContactDamage : public Component {
public:
	ContactDamage(int danyo);

	virtual ~ContactDamage() {}

	void init() override;
	void update() override;
	void render() override;

	bool CheckCollisions(const SDL_Rect& enemyRect, bool finCombo);
	void updateRect();

private:
	Transform* tr_;
	SDL_Rect attRect_;
	Animator* anim_;
	bool DEBUG_isAttacking_;
	long unsigned int time_;
	SoundEffect& attackSound_, & hitSound_;
	int dmg_;
}
;