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

class FollowPlayer : public Behavior {
public:
	FollowPlayer();

	virtual ~FollowPlayer() {};

	void init() override;
	void behave();

	void lockHamster();
	void lockHamster(int id);
	bool isWithinAttackRange();

protected:
private:
	/*
	const float jump_ = 45.0f, gravity_ = 4.8f, jumpTimer_ = 10.0f;
	long unsigned int timer;
	td::map<KEYS, bool> keymap;
	*/

	//hamster al que va a perseguir* en verdad solo queremos la propiedad tranform ahora mismo pero
	// mas adelante es posible que nos interese conocer estados o componentes oportunos, por ahora no ahce daño verdad¿?¿
	std::vector<Entity*> hamsters_;
	int hamsId_;
	//std::vector<> 
	MovementSimple* mov_; //Igual esto es major al reves, que el movement coja los datos del follow y se mueva en la dir que le indique
	
	Transform* tr_;
	Transform* hamsterTr_;
	
	Entity* lockedHamster_;
	
	HamsterStateMachine* lockedHamState_;
	
	int rangeOffsetX_; // Esta movida habra que balancearla
	int rangeOffsetY_; // Esta movida habra que balancearla

	EnemyAttack* enAtk_; //componente de ataque

	EnemyStateMachine* enmState_;
};

