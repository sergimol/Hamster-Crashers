#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim
#include <SDL.h>
#include <cassert>
#include <vector>

#include "../ecs/Component.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "Gravity.h"
#include "Transform.h"

class CatMovement : public Component {
public:
	CatMovement(): tr_(nullptr), grav_(nullptr) {};

	virtual ~CatMovement() {};

	void init() override;
	void update() override;

	void start() { tr_->setVel(Vector2D(VEL, 0)); }

private:
	float jump_ = 35.0f;
	Transform* tr_;
	Gravity* grav_;

	const int VEL = -5;

};

