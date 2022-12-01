#pragma once

#include "../ecs/Component.h"
#include "Animator.h"
#include "EntityAttribs.h"
#include <string>

const enum class EnemyStatesAnim {
	IDLE, MOVE,
	JUMPUP, JUMPDOWN,
	ATTACK,
	STRONGATTACK,
	HITTED, STUNNED, DEAD,
	DEFAULT,
	ONFLOOR, UP, SEQUENCE, SHIELD
};


class AnimEnemyStateMachine : public Component
{
private:
	EnemyStatesAnim currentState;
	EnemyStatesAnim lastState;
	Animator* anim;
	EntityAttribs* ent;
	GameStates* gState_;
	std::string id;

	//VARIABLES AUXILIARES PARA ALGUNAS ANIMACIONES
	int attackOrder_ = 0; //para los ataques ligeros

	//BOOLEANOS PARA LAS ANIMACIONES, 1 POR ESTADO
	bool idle;
	bool move;
	bool lAttack;
	bool sAttack;
	bool hit;
	bool stun;
	bool lCombo;
	bool onfloor;
	bool up;
	bool sequence;
	bool shield;
	bool dead;

public: 
	AnimEnemyStateMachine() : currentState(EnemyStatesAnim::IDLE), lastState(EnemyStatesAnim::DEFAULT), anim(nullptr), ent(nullptr) {};

	void init() override;

	~AnimEnemyStateMachine() {};
	
	inline EnemyStatesAnim& getState() { return currentState; };

	virtual void update();

	//HACE PLAY DE LA ANIMACION NECESARIA EN CADA ESTADO
	void CheckAnimState();

	//MANEJA LAS TRANSICIONES DE LOS ESTADOS
	void HandleAnimState();

	void setAnimBool(EnemyStatesAnim h, bool b);

	bool isOnAttack() {
		return(currentState == EnemyStatesAnim::ATTACK || currentState == EnemyStatesAnim::STRONGATTACK);
	}
};

