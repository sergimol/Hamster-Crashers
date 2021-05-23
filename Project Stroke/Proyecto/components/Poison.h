#pragma once

#include "Ability.h"

class Poison : public Ability {
public:
	Poison(int dmg);

	virtual ~Poison();

	virtual void update();

	virtual void endAbility();

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action();

private:
	int dmg_;
	int x = 0;
	Entity* cloud_;

	//Constantes
	const float CLOUDCD = 2000;
	const float COFFSETX = 0;
	const float CBULLETSPEED = 1;
};
