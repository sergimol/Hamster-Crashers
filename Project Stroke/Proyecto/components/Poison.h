#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "Ability.h"

const float CLOUDCD = 2000;
const float COFFSETX = 200;
const float CBULLETSPEED = 1;

class Poison : public Ability {
public:
	Poison(int dmg);

	virtual ~Poison();

	virtual void update();

	virtual void render();

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action();

private:
	int dmg_;
	int x = 0;
	Entity* cloud;
};
