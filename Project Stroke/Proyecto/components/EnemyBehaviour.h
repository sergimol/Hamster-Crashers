#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>
#include <cmath>

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

class EnemyBehaviour : public Component {
protected:
public:
	EnemyBehaviour(Behavior* auxbh);
	virtual ~EnemyBehaviour() {}

	void init() override;

	void SetBehavior(Behavior* bs);

	void update() override;
	virtual void onEnable() override;
	virtual void onDisable() override;

	void lockHamster();
	void lockHamster(int id);
	bool isWithinAttackRange();



	//getters es posible que algunos sean prescindibles// nada es una salvajada me arrepiento pero diego del futuro TODO

	//----------------------------------------------------------


	EnemyAttack* getEnAtk() {
		return enAtk_; //componente de ataque
	}

	std::vector<Entity*> getHamstervector() {
		return hamsters_;
	}

	MovementSimple* getMov(){
		return mov_; 
	}

	Transform* getTr() {
		return tr_;
	}

	Transform* getHamsterTr() {
		return hamsterTr_;
	}

	Entity* getLockedHamster() {
		return lockedHamster_;
	}
	HamsterStateMachine* getLockedHamState() {
		return lockedHamState_;
	}

	int getRangeOffsetX() {
		return rangeOffsetX_; // Esta movida habra que balancearla
	}
	int getRangeOffsetY() {
		return rangeOffsetY_; // Esta movida habra que balancearla
	}

	//este me soluciona los problemas rapido y me ahorra usar lso demas xd pero se van a quedar igual porque ya los escribí
	Entity* getEntity() {
		return entity_;
	}

protected: //ahora mismo solo funcionan como private
	EnemyAttack* enAtk_; //componente de ataque
	//hamster al que va a perseguir* en verdad solo queremos la propiedad tranform ahora mismo pero
	// mas adelante es posible que nos interese conocer estados o componentes oportunos, por ahora no ahce daño verdad¿?¿
	std::vector<Entity*> hamsters_;
	MovementSimple* mov_; //Igual esto es major al reves, que el movement coja los datos del follow y se mueva en la dir que le indique

	Transform* tr_;
	Transform* hamsterTr_;

	Entity* lockedHamster_;

	HamsterStateMachine* lockedHamState_;

	int rangeOffsetX_; // Esta movida habra que balancearla
	int rangeOffsetY_; // Esta movida habra que balancearla
	Behavior* bh_; //el behavior

};

