#pragma once

#include "../ecs/Component.h"

const enum HamStates { IDLE, DEAD, STUNNED, INFARCTED, MOVING, JUMPING};

class HamsterStateMachine : public Component
{
private:
	HamStates currentState;
public: 
	HamsterStateMachine() : currentState(IDLE) {};
	~HamsterStateMachine() {};
	inline HamStates& getState() { return currentState; };
};

