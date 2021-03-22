#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "Ability.h"

const int TURRETTIME = 3000;
const int CADENCESHOT = 100;
const int BULLETSPEED = 10;

//Con esto movemos la bala a la Cara de Monchi
const int OFFSETX = 20;
const int OFFSETY = 20;

class Turret : public Ability {
public:
	Turret();

	virtual ~Turret();

	virtual void update();

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action();

private:
	bool startFire;
	float waitTime;
	float cadenceTime;
	float x;
};
