// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
//Daño por bala
const int DMG = 2;

class BulletHit : public Component {

public:

	BulletHit(float pos);

	virtual ~BulletHit();

	virtual void init() override;

	virtual void update() override;
private:
	int dmg_;
	Transform* tr_;
	SDL_Rect cam;
	float y;
};

