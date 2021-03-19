#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../components/Ability.h"

class Pray : public Ability {
public:
	Roll();

	virtual ~Roll();

	virtual void init();

	virtual void update();

	float lerp(float a, float b, float f);

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action();

private:
	HamStates state_;
};

