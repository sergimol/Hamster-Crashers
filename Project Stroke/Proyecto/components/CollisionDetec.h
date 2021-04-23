#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include <map>
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "Gravity.h"

class CollisionDetec : public Component {
public:

	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	CollisionDetec() :
		tr_(nullptr){
	}

	virtual ~CollisionDetec() {
	}

	void init() override;

	void update() override {};

	void tryToMove(Vector2D dir, Vector2D goalVel, SDL_Rect& rectPlayer);

	float lerp(float a, float b, float f);

private:

	Transform* tr_;
	Gravity* grav_;
};

