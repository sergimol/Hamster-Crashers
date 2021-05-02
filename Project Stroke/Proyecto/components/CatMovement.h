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

	void update() override;

	void startChase();

private:
	Transform* tr_;
	int iniPos = 0;

	const int MOVE = 100, TIME = 3000, VEL = 2;

	// Supuestamente con animaciones
	// Timer temporal

	int timer = 0;

	bool walk = false;
	bool walking = false;
	bool start = false;
};

