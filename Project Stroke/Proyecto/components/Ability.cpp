#include "Ability.h"

void Ability::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	st_ = entity_->getComponent<HamsterStateMachine>();
	assert(st_ != nullptr);

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

	state_ = st_->getState();
}

void Ability::update() {
	//Piscontronco 3:14 (DHH):
	/*
	* Cada "cooldown" milisegundos, se comprueba que se pueda activar la habilidad
	* Si la habilidad estaba activa, se desactiva
	* De lo contrario, no sucede nada
	* 
	*/

	if (active && sdlutils().currRealTime() > timer_ + cooldown_) {
		if (!lastUsed && ih().keyDownEvent() && (state_ == HamStates::IDLE || state_ == HamStates::MOVING)) {
			if (ih().isKeyDown(key_)) {
				timer_ = sdlutils().currRealTime();
				action();
				lastUsed = true;
			}
		}
		else if(lastUsed){
			lastUsed = false;
			endAbility();
		}
	}
}

void Ability::deactiveAbility() {
	if (active) {
		active = false;
		endAbility();
	}
}