// This file is part of the course TPV2@UCM - Samir Genaim
#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>


#include "Component.h"
#include "ecs.h"

#include "Entity.h"
#include "Manager.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include <SDL_rect.h>


class Camera : public Component {
public:

	Camera(SDL_Rect cam) : camera_(cam)
	{}

	virtual ~Camera() {}
	void update() override;
	SDL_Rect getCam() { return camera_; }
private:
	SDL_Rect camera_;
};

