#pragma once

#include "../ecs/Component.h"

const enum class HamStates { IDLE, DEAD, STUNNED, INFARCTED, MOVING, JUMPING, STRONGATTACK, LIGHTATTACK, HABILITY};

class HamsterStateMachine : public Component
{
private:
	HamStates currentState;
public: 
	HamsterStateMachine() : currentState(HamStates::IDLE) {};
	~HamsterStateMachine() {};
	inline HamStates& getState() { return currentState; };
};

