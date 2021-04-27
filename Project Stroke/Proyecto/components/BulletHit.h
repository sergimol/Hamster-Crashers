#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class BulletHit : public Component {

public:

	BulletHit(float pos);

	virtual ~BulletHit();

	virtual void init() override;

	virtual void update() override;
private:
	int dmg_;
	Transform* tr_;
	SDL_Rect cam_;
	float y_;

	//Daño por bala
	const int DMG = 2;
};

