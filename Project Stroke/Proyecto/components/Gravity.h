#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"

class Gravity : public Component
{
public:
Gravity() : floor(0) {};

virtual ~Gravity() {};

void init() override;

void update() override;


private:
	Transform* tr_;
	float floor;
	const float gravity_ = 4.9;
	float timer = 0;
	const float jumpTimer_ = 0.15;
};

