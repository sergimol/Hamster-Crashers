#pragma once

#include <SDL.h>
#include <cassert>
#include "../utils/checkML.h"

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "EntityAttribs.h"
#include "Transform.h"
#include "EnemyStateMachine.h"
#include "MovementSimple.h"
#include "EnemyBehaviour.h"

class EnemyStun : public Component {
public:
	EnemyStun();

	virtual ~EnemyStun() {}

	void init() override;
	void update() override;
	
	void restartStunTime();
	
	inline void setStunCooldown(long unsigned cd) { cooldown_ = cd; }

private:
	EnemyStateMachine* enmState_;
	MovementSimple* simpMov_;
	//EnemyBehaviour* enBehave_;
	long unsigned int cooldown_, time_;

	bool movCancelled_;
}
;