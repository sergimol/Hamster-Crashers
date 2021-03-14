#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>
#include <cmath>

#include "Transform.h"



class Ability : public Component {
public:
	Ability() :
		tr_(nullptr) {
	}

	virtual ~Ability() {
	}

	void init() override {
		
	}

	void update() override {

	}

	float lerp(float a, float b, float f)
	{

	}

private:
	Transform* tr_;
};

