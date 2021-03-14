// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "HamsterStateMachine.h"

// Tiempo entre comprobación
const int UPDATETIME = 5000,
		  MAXAB = 65,
		  MAXCHANCE = 35;

class Stroke: public Component {
public:
	Stroke() :
			tr_(nullptr) {
	}
	virtual ~Stroke() {
	}
	void init() override;

	void update() override;

	void increaseChance(int n, Component* c);

private:
	Transform *tr_;
	HamsterStateMachine* hms_;
	// Probabilidad de que haya un infarto
	int chance_ = 1,
		chanceFromAb_ = 0,
		// Tiempo desde la última comprobación
		timeLastUpdate_ = 0;
	// Generador de números aleatorios
	RandomNumberGenerator& r_ = sdlutils().rand();
};

