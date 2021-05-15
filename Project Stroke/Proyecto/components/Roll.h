#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "Ability.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "CollisionDetec.h"
#include "SoundManager.h"

class Roll : public Ability {
public:
	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	Roll() : speed_(), goalVel_(0, 0), dir_(0,0), timer(sdlutils().currRealTime()), rolling(false), col_(nullptr), abDmg_(10)
	{
		cooldown_ = 2500;
	};

	virtual ~Roll();

	virtual void init() override;

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action();

	virtual void update() override;

	virtual void endAbility() override;

	void updateKeymap(KEYS x, bool is);


private:
	bool rolling;

	const float jump_ = 45.0f, gravity_ = 4.8f, jumpTimer_ = 10.0f;
	
	const int maxAccel = 3, iniAccel = 10;
	
	long unsigned int timer;

	Vector2D speed_, goalVel_, dir_;
	CollisionDetec* col_;
	Movement* mov_;
	Gravity* grav_;

	std::map<KEYS, bool> keymap;

	int abDmg_;

	bool checkCollisions();
};

