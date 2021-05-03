#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim
#include <SDL.h>
#include <cassert>
#include <vector>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
//#include "../ecs/Behavior.h"

#include "Transform.h"

class CatMovement : public Component {
public:
	CatMovement() {};

	virtual ~CatMovement() {};

	void init() override;

private:
	Transform* tr_;

	const int VEL = -2;

};

