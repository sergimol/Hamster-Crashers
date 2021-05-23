#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "GameStates.h"
#include "../sdlutils/SDLUtils.h"

class BulletHit : public Component {

public:

	BulletHit();

	virtual ~BulletHit();

	virtual void init() override;

	virtual void update() override;
private:
	int dmg_;
	Transform* tr_;
	GameStates* state_;
	SDL_Rect cam_;
};

