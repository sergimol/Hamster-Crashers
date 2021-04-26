#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim
#include <SDL.h>
#include <cassert>
#include <vector>
#include "../utils/checkML.h"

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
//#include "../ecs/Behavior.h"

#include "Transform.h"
#include "HamsterStateMachine.h"
#include "Animator.h"
#include "EntityAttribs.h"
#include "MovementSimple.h"
#include "EnemyAttack.h"
#include "EnemyStateMachine.h"
#include "Behavior.h"
#include "EnemyBehaviour.h"

class FleeFromPlayer : public Behavior {
public:
	FleeFromPlayer();

	virtual ~FleeFromPlayer() {};

	void init() override;
	void behave();

	void lockHamster();
	void lockHamster(int id);
	bool isWithinRange();

protected:
private:
	std::vector<Entity*> hamsters_;
	int rangeOffsetX_; // Esta movida habra que balancearla
	int rangeOffsetY_; // Esta movida habra que balancearla
	int rangeOffset_; // un offset en el que permitamos que este ok qudarse quieto

	EnemyAttack* enAtk_; //componente de ataque

	EnemyStateMachine* enmState_;
};

