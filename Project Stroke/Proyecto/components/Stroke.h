// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

#include "HamsterStateMachine.h"
#include "Ability.h"
//#include "Transform.h"
		  
const int UPDATETIME = 5000, // Tiempo entre comprobaciones de infarto
		  MAXAB = 65, // Máximo de probabilidad de infarto que se puede recibir por habilidades
		  MAXCHANCE = 35, // Máximo de probabilidad de infarto que se puede recibir por salto y ataque
		  TIMETODECREASE = 10000, // Tiempo que debe pasar para empezar a reducir el infarto
		  TIMEBETWEENDECREASES = 2500; // Tiempo entre reducciones de la probabilidad

class Stroke: public Component {
public:
	Stroke() :
			hms_(nullptr), ab_(nullptr) {
	}
	virtual ~Stroke() {
	}
	void init() override;

	void update() override;

	void increaseChance(int n, bool fromAbility);

	void infarctHamster();

private:
	HamsterStateMachine* hms_;
	Ability* ab_;
	Transform* tr_;
	// Probabilidad de que haya un infarto
	int chance_ = 1,
		chanceFromAb_ = 0,
		// Tiempo de la última comprobación
		timeLastUpdate_ = 0,
		// Tiempo del último aumento
		timeLastIncrease_ = 0,
		// Tiempo de la última reducción
		timeLastDecrease_ = 0;
	// Generador de números aleatorios
	RandomNumberGenerator& r_ = sdlutils().rand();
};

