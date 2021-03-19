#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "Ability.h"

class Roll : public Ability {
public:
	Roll();

	virtual ~Roll();

	float lerp(float a, float b, float f);

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action();
};

