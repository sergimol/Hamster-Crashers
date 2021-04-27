#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Gravity.h"
#include "GameStates.h"
#include <string>

const enum class HamStates { DEFAULT, INFARCTED, ABILITY, STUNNED, DEAD};

class HamsterStateMachine : public Component
{
private:
	HamStates currentState;
	GameStates* state_;
public: 
	HamsterStateMachine() : currentState(HamStates::DEFAULT), state_(nullptr) {};
	~HamsterStateMachine() {};
	
	inline HamStates& getState() { return currentState; };
	
	inline bool canMove() const { return (currentState == HamStates::DEFAULT || 
										  currentState == HamStates::ABILITY || 
										  currentState == HamStates::INFARCTED ); };

	inline bool canAttack() const { return currentState == HamStates::DEFAULT; };

	/*inline bool canJump() const { return (currentState == HamStates::DEFAULT
										   && entity_->getComponent<Gravity>()->isActive()); };*/

	inline bool cantBeTargeted() const { return (currentState == HamStates::DEAD ||
												 currentState == HamStates::INFARCTED); };
	
	// Para debugear
	inline std::string currentstate() const {
		if (currentState == HamStates::INFARCTED) return "infarcted";
		else if (currentState == HamStates::DEAD) return "dead";
		else if (currentState == HamStates::DEFAULT) return "default";
		else if (currentState == HamStates::STUNNED) return "stunned";
		else if (currentState == HamStates::ABILITY) return "ability";
		else return"catastrofe";
	};

	virtual void update();

	void init() override;
};

