#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../utils/checkML.h"

const enum class EnemyStates { ENM_IDLE, ENM_DEAD, ENM_STUNNED, ENM_MOVING, ENM_ATTACK };

class EnemyStateMachine : public Component
{
private:
	EnemyStates currentState;

	bool controlhitanim_ = true;
public:
	EnemyStateMachine() : currentState(EnemyStates::ENM_IDLE) {};
	~EnemyStateMachine() {};
	inline EnemyStates& getState() { return currentState; };
	virtual void update();
};

