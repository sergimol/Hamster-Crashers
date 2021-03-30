#pragma once

#include "../ecs/Component.h"

const enum class HamStates { IDLE, DEAD, STUNNED, INFARCTED, MOVING, JUMPING, STRONGATTACK, LIGHTATTACK, ABILITY};

class HamsterStateMachine : public Component
{
private:
	HamStates currentState;
public: 
	HamsterStateMachine() : currentState(HamStates::IDLE) {};
	~HamsterStateMachine() {};
	
	inline HamStates& getState() { return currentState; };
	
	inline bool canMove() const { return (currentState == HamStates::IDLE || 
										  currentState == HamStates::MOVING || 
										  currentState == HamStates::JUMPING); };

	inline bool canAttack() const { return (!(currentState == HamStates::DEAD || 
												 currentState == HamStates::STUNNED || 
												 currentState == HamStates::INFARCTED)); };

	inline bool canJump() const { return (currentState == HamStates::IDLE ||
										  currentState == HamStates::MOVING); };

	inline bool cantBeTargeted() const { return (currentState == HamStates::DEAD ||
												 currentState == HamStates::INFARCTED); };
};

