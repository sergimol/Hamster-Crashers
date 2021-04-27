#include "Ability.h"
#include "AnimHamsterStateMachine.h"

void Ability::init() {

	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	st_ = entity_->getComponent<HamsterStateMachine>();
	assert(st_ != nullptr);

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void Ability::update() {
	if (state_->getState() != GameStates::PAUSE) {
		/*
		* Cada "cooldown" milisegundos, se comprueba que se pueda activar la habilidad
		* Si la habilidad estaba activa, se desactiva
		* De lo contrario, no sucede nada
		*/
		auto& state = st_->getState();
		if (onUse_ && state == HamStates::ABILITY && sdlutils().currRealTime() > timer_ + cooldown_) {
			onUse_ = false;
			endAbility();
			state = HamStates::DEFAULT;
		}
	}
}

void Ability::deactiveAbility() {

	if (active_) {
		active_ = false;
		endAbility();
		auto& state = st_->getState();	
		state = HamStates::INFARCTED;
	}
}

void Ability::activateAbility() {
	active_ = true;
}

void Ability::use() {

	if (active_ && sdlutils().currRealTime() > timer_ + cooldown_) {
		auto& state = st_->getState();

		if (!onUse_ && state == HamStates::DEFAULT) {
			timer_ = sdlutils().currRealTime();
			state = HamStates::ABILITY;
			action();
			onUse_ = true;

			//LLAMAMOS LA ANIMACION DE LA HABILIDAD
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::ABILITY, true);

			//PARA DESACTIVARLA, SE HACE DESDE CADA HABILIDAD, DE MANERA INDEPENDIENTE
			//SOLO ESTA PUESTO EN EL ROLL
		}
	}
}

void Ability::onResume() {
	timer_ += sdlutils().currRealTime() - timer_;
	//cooldown_ += sdlutils().currRealTime() - cooldown_;
}