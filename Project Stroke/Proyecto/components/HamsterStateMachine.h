#pragma once

#include "../ecs/Component.h"
#include <string>

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
	
	inline std::string currentstate() const {
		if (currentState == HamStates::INFARCTED) return "infarted";
		else if (currentState == HamStates::IDLE) return "idle";
		else if (currentState == HamStates::DEAD) return "dead";
		else if (currentState == HamStates::STRONGATTACK) return "strongattk";
		else if (currentState == HamStates::LIGHTATTACK) return "light atck";
		else if (currentState == HamStates::STUNNED) return "stunned";
		else if (currentState == HamStates::JUMPING) return "jumping";
		else if (currentState == HamStates::MOVING) return "moving";
		else if (currentState == HamStates::ABILITY) return "ability";
		else return"catastrofe";
	};
};

