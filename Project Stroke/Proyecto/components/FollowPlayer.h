#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include <map>
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "HamsterStateMachine.h"
#include "Animator.h"
#include "EntityAttribs.h"

class FollowPlayer : public Component {
public:

	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	FollowPlayer(Entity* Jamnster) :
		mov_(nullptr) {
		hamster_ = Jamnster;
	}

	virtual ~FollowPlayer() {
	}

	void init() override;

	void update() override;
	virtual void onEnable() override;
	virtual void onDisable() override;


protected:
private:
	/*
	const float jump_ = 45.0f, gravity_ = 4.8f, jumpTimer_ = 10.0f;
	long unsigned int timer;
	*/

	MovementSimple* mov_;
	Transform* trHamnster_;
	Entity* hamster_; //hamster al que va a perseguir* en verdad solo queremos la propiedad tranform ahora mismo pero
						// mas adelante es posible que nos interese conocer estados o componentes oportunos, por ahora no ahce daño verdad¿?¿
	
	std::map<KEYS, bool> keymap;
};

