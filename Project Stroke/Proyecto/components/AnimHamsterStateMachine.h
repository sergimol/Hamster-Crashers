#pragma once

#include "../ecs/Component.h"
#include "Animator.h"
#include "EntityAttribs.h"
#include <string>

const enum class HamStatesAnim {
	IDLE, MOVE, ABILITY,
	JUMPUP, JUMPDOWN,
	LIGHTATTACK, LIGHTCOMBO,
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
	GameStates* gState_;
	std::string id;

	//VARIABLES AUXILIARES PARA ALGUNAS ANIMACIONES
	bool attackOrder_ = true; //para los ataques ligeros //true 1 false 2

	//BOOLEANOS PARA LAS ANIMACIONES, 1 POR ESTADO
	bool idle;
	bool move;
	bool lAttack;
	bool sAttack;
	bool hit;
	bool stun;
	bool lCombo;
	bool sCombo;
	bool stroke;
	bool ability;

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

	void resetAnim();

	bool isOnAttack() {
		return(currentState == HamStatesAnim::LIGHTATTACK || currentState == HamStatesAnim::LIGHTCOMBO
			|| currentState == HamStatesAnim::STRONGATTACK || currentState == HamStatesAnim::STRONGCOMBO);
	}
};

