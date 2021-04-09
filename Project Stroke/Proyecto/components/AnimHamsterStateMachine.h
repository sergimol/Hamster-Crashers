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
	STROKE, GHOST,
	DEFAULT
};


class AnimHamsterStateMachine : public Component
{
private:
	HamStatesAnim currentState;
	HamStatesAnim lastState;
	Animator* anim;
	EntityAttribs* ent;
	std::string id;

	//BOOLEANOS PARA LAS ANIMACIONES, 1 POR ESTADO
	bool idle;
	bool move;
	bool attack;

public: 
	AnimHamsterStateMachine() : currentState(HamStatesAnim::IDLE), lastState(HamStatesAnim::DEFAULT), anim(nullptr), ent(nullptr) {};

	void init() override;

	~AnimHamsterStateMachine() {};
	
	inline HamStatesAnim& getState() { return currentState; };

	virtual void update();

	//HACE PLAY DE LA ANIMACION NECESARIA EN CADA ESTADO
	void CheckAnimState();

	//MANEJA LAS TRANSICIONES DE LOS ESTADOS
	void HandleAnimState();

	void setAnimBool(HamStatesAnim h, bool b);

};

