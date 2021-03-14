#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "Life.h"
#include "Transform.h"

class Camera : public Component {
public:
	Camera();

	virtual ~Camera() {}

	void init() override;
	void update() override;
	bool CheckCollisions(const SDL_Rect& rectPlayer);

private:
	Transform* tr_;
	short unsigned int w_, h_;
	long unsigned int cooldown_, time_;
	SoundEffect& attackSound_;
	SoundEffect& hitSound_;
	float dmg_ = 0;
}
;