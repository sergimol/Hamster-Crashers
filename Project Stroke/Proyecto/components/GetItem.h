#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>
#include <cmath>

#include "../components/Transform.h"
#include "../components/HamsterStateMachine.h"
#include "../components/Animator.h"

const int APPLEHP = 20;
const int WATERHP = 50;
const int NUTHP = 10;

class GetItem : public Component {
public:
	GetItem() :  tr_(nullptr) {};

	virtual ~GetItem() {};

	virtual void update();

	virtual void init();

private:
	Transform* tr_;
};

