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
	Ability() : tr_(nullptr), st_(nullptr), timer_(-1000), cooldown_(1000) {};

	Ability(int cd) : tr_(nullptr), st_(nullptr), timer_(-cd), cooldown_(cd) {};

	virtual ~Ability() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override {};

	//virtual void onEnable() override {};

	//virtual void onDisable() override {};

	//Ejecuta la habilidad en funcion del hamster que sea
	virtual void action() = 0;
	
	virtual void endAbility() {};

	inline bool isAbilityActive() const { return active; };

	void deactiveAbility();
	void activateAbility();

	void use();

protected:
	const SDL_Keycode key_ = SDLK_m;

	Transform* tr_;
	HamsterStateMachine* st_;
	Animator* anim_;
	long unsigned int timer_, cooldown_; //Contador para ver CADA CUANTO puede usar una habilidad

	bool active = true;
	bool onUse = false;
};

