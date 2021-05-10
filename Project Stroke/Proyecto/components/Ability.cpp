#include "Ability.h"
#include "AnimHamsterStateMachine.h"
#include "UI.h"
#include "Stroke.h"

void Ability::init() {

	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	st_ = entity_->getComponent<HamsterStateMachine>();
	assert(st_ != nullptr);

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);

	auto* ui = entity_->getComponent<UI>();
	auto name = entity_->getComponent<EntityAttribs>()->getId();

	txtOn = &sdlutils().images().at(name + "On");
	txtOff = &sdlutils().images().at(name + "Off");

	txtPos = build_sdlrect(ui->getBarPos().getX() + offsetTextX, ui->getBarPos().getY() + offsetTextY, txtOn->width()/3, txtOn->height()/3);
}

void Ability::render() {
	if (active_ && !onUse_)
		txtOn->render(txtPos, 0);
	else
		txtOff->render(txtPos, 0);
}

void Ability::update() {
	if (state_->getState() == GameStates::RUNNING) {
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
		onUse_ = false;
		endAbility();
	}
}

void Ability::activateAbility() {
	active_ = true;
	onUse_ = false;
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
			entity_->getComponent<Stroke>()->increaseChance(20, true);
			//PARA DESACTIVARLA, SE HACE DESDE CADA HABILIDAD, DE MANERA INDEPENDIENTE
			//SOLO ESTA PUESTO EN EL ROLL
		}
	}
}

void Ability::onResume() {
	timer_ += sdlutils().currRealTime() - timer_;
	//cooldown_ += sdlutils().currRealTime() - cooldown_;
}