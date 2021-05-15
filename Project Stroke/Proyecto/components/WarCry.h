#pragma once

#include "Ability.h"
#include "EntityAttribs.h"
#include "LightAttack.h"
#include "StrongAttack.h"
#include "AnimHamsterStateMachine.h"

class WarCry : public Ability {
public:
	WarCry(float attSpeedM, float dmgM);

	virtual ~WarCry();

	virtual void init() override;

	virtual void update() override;

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action();

	virtual void endAbility() override;

private:

	const enum WarCryStates {
		notStarted = 0, fearStarted, fearFinished
	};

	EntityAttribs* attribs_;
	LightAttack* lightAtt_;
	StrongAttack* strongAtt_;

	AnimHamsterStateMachine* anim_;

	int originalDmg_,
		originalLightCadence_,
		originalStrongCadence_;
	float attCadenceMultiplier_,
		dmgMultiplier_,
		fearCD_,
		buffCD_,
		abTime_;

	int abilityState_;

	void slowEnemies(bool notEndAb);
};
