#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "Ability.h"

const float WAIT = 2000;

class Pray : public Ability {
public:
	Pray(int dmg, int heal);

	virtual ~Pray();

	virtual void update();

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action();

private:
	SDL_Rect came_;
	bool evil;
	int dmg_;
	int heal_;
	float waitTime;
	bool magicTime;

	void prayAbility();
};
