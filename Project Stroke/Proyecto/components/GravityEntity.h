#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"

class GravityEntity : public Component
{
public:
	GravityEntity() : floor(0) {};

	virtual ~GravityEntity() {};

	void init() override;

	void update() override;


private:
	Transform* tr_;
	float floor;
	const float gravity_ = 4.9;
	float timer = 0;
	const float jumpTimer_ = 0.15;
};
