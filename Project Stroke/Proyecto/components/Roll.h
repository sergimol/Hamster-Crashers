#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "Ability.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"


class Roll : public Ability {
public:
	Roll() : tr_(nullptr), hms_(nullptr), anim_(nullptr), speed_(), goalVel_(0, 0), dir_(0,0), timer(sdlutils().currRealTime()), rolling(false),
		hitSound_(sdlutils().soundEffects().at("strong_attack")) {};

	virtual ~Roll();

	virtual void init()override;

	float lerp(float a, float b, float f);

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action();

	virtual void update() override;

private:
	bool rolling;

	const float jump_ = 45.0f, gravity_ = 4.8f, jumpTimer_ = 10.0f;
	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	long unsigned int timer;

	Transform* tr_;
	HamsterStateMachine* hms_;
	Animator* anim_;
	Vector2D speed_, goalVel_, dir_;

	std::map<KEYS, bool> keymap;

	SoundEffect& hitSound_;

	bool CheckCollisions();
};

