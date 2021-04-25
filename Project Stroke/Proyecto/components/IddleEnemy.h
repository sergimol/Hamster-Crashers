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
#include "Behavior.h"

class IddleEnemy : public Behavior {
public:
	IddleEnemy();

	virtual ~IddleEnemy() {};

	void init() override;
	void behave();

	void lockHamster();
	void lockHamster(int id);

protected:
private:
	std::vector<Entity*> hamsters_;

};

