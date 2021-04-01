#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "EntityAttribs.h"
#include "Transform.h"
#include "EnemyStateMachine.h"
#include "FollowPlayer.h"
#include "MovementSimple.h"
#include "EnemyAttack.h"

class EnemyStun : public Component {
public:
	EnemyStun();

	virtual ~EnemyStun() {}

	void init() override;
	void update() override;
	void knockback();

private:
	Transform* tr_;
	EnemyStateMachine* enmState_;
	FollowPlayer* flwPlayer_;
	bool isStunned_;
	long unsigned int cooldown_, time_;
}
;