#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include <map>
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "MovementSimple.h"

class CollisionDetec : public Component {
public:

	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	CollisionDetec() :
		tr_(nullptr), speed_(Vector2D(0,0)){
	}

	virtual ~CollisionDetec() {
	}

	void init() override;

	void update() override {};

	void tryToMove(Vector2D dir, Vector2D goalVel, SDL_Rect& rectPlayer, bool enemy);
	
	void tryToMoveObs(Vector2D dir, Vector2D goalVel, SDL_Rect& rectFoot, bool enemy);

	void setMovement(MovementSimple* m);

private:

	Transform* tr_;

	MovementSimple* mv_;
	Camera* cam_;
	Vector2D speed_;
};

