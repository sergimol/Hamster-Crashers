#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "Ability.h"

const float CLOUDCD = 2000;

class Poison : public Ability {
public:
	Poison(int dmg);

	virtual ~Poison();

	virtual void init();
	virtual void update();

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action();

private:
	SDL_Rect cloud;
	int dmg_;

};
