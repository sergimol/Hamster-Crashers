#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>
#include <cmath>

#include "Transform.h"


class Ability : public Component {
public:
	Ability();

	virtual ~Ability();

	void init() override;

	void update();

	float lerp(float a, float b, float f);

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void accion() = 0;

	//Devuelve si puede volvera lanzar la habilidad o no
	bool getCanAttack() { return canAttack; }

	//Setters auxiliares
	void setCanAttack(bool can) { canAttack = can; }
	void setTime(float seconds) { timer = seconds; }
private:
	Transform* tr_;
	bool canAttack;
	float timer; //Contador para ver cada cuanto puede usar una habilidad
};

