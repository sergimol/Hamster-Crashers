#pragma once

#include "Ability.h"

class Turret : public Ability {
public:
	Turret();

	virtual ~Turret();

	void init() override;
	void update() override;

	//Ejecuta la habilidad en funcion del hamster que sea
	void action() override;
	void endAbility() override;

private:
	Vector2D actualSpeed_;
	float cadenceTime_;
	float x_;

	//CONSTANTES
	const int CADENCESHOT = 100;
	const int BULLETSPEED = 10;
	const int CD = 2000;

	//Con esto movemos la bala a la Cara de Monchi
	const int OFFSETX = 20;
	const int OFFSETY = 20;
};
