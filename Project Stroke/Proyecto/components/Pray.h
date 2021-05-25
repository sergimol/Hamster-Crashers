#pragma once

#include "Ability.h"

class Pray : public Ability {
public:
	Pray(int dmg, int heal);

	virtual ~Pray();

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action();

	virtual void endAbility() override;

	void stopUseAbility();
private:
	bool evil_;
	int dmg_;
	int heal_;

	bool dontUseAbility;

	void prayAbility();
};
