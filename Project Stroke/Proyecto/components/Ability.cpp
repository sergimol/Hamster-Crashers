#include "Ability.h"

void Ability::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	st_ = entity_->getComponent<HamsterStateMachine>();
	assert(st_ != nullptr);

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

}

void Ability::update() {
	//Piscontronco 3:14 (DHH):
	/*
	* Cada "cooldown" milisegundos, se comprueba que se pueda activar la habilidad
	* Si la habilidad estaba activa, se desactiva
	* De lo contrario, no sucede nada
	* 
	*/
	auto& state = st_->getState();
	if (onUse && state == HamStates::ABILITY && sdlutils().currRealTime() > timer_ + cooldown_) {
		onUse = false;
		endAbility();
		state = HamStates::DEFAULT;
	}
}

void Ability::deactiveAbility() {
	if (active) {
		active = false;
		endAbility();
		auto& state = st_->getState();	
		state == HamStates::DEFAULT;
	}
}

void Ability::activateAbility() {
	active = true;
}

void Ability::use() {
	if (active && sdlutils().currRealTime() > timer_ + cooldown_) {
		auto& state = st_->getState();
		if (!onUse && state == HamStates::DEFAULT) {
			timer_ = sdlutils().currRealTime();
			state = HamStates::ABILITY;
			action();
			onUse = true;
		}
	}
}