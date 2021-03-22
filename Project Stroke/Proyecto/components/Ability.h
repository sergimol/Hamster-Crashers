#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>
#include <cmath>

#include "../components/Transform.h"
#include "../components/HamsterStateMachine.h"
#include "../components/Animator.h"

class Ability : public Component {
public:
	Ability() : tr_(nullptr), st_(nullptr), timer_(0.0f), cooldown_(1000.0f) {};

	virtual ~Ability() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override {};

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action() = 0;
protected:
	Transform* tr_;
	HamsterStateMachine* st_;
	Animator* anim_;
	float timer_, cooldown_; //Contador para ver cada cuanto puede usar una habilidad
	const SDL_Keycode key_ = SDLK_m;
	HamStates state_;
};

