#pragma once

#include "../ecs/Component.h"
#include "Animator.h"
#include "EntityAttribs.h"
#include <string>

const enum class HamStatesAnim {
	IDLE, MOVE, ABILITY,
	JUMPUP, JUMPDOWN,
	LIGHTATTACK1, LIGHTATTACK2, LIGHTCOMBO,
	STRONGATTACK, STRONGCOMBO,
	HITTED, STUNNED, DEAD,
	STROKE, GHOST
};

class AnimHamsterStateMachine : public Component
{
private:
	HamStatesAnim currentState;
	HamStatesAnim lastState;
	Animator* anim;
	EntityAttribs* ent;
public: 
	AnimHamsterStateMachine() : currentState(HamStatesAnim::IDLE), lastState(HamStatesAnim::IDLE), anim(nullptr), ent(nullptr) {};

	void init() override;

	~AnimHamsterStateMachine() {};
	
	inline HamStatesAnim& getState() { return currentState; };

	virtual void update();

	void handleAnimState();
};

