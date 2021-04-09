#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"

class Swallow : public Component
{
public:
	Swallow(float prob) : swallowProbabilty_(prob), healVal_(20) {};

	virtual ~Swallow() {};

	bool canSwallow();

	inline int healQuantity() {
		return healVal_;
	}

private:
	float swallowProbabilty_;
	int healVal_;
};

