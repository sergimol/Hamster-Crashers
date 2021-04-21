#include "Combos.h"
#include "AnimHamsterStateMachine.h"
#include "Transform.h"

void Combos::init() {
	grv_ = entity_->getComponent<Gravity>();
	assert(grv_ != nullptr);
	anim_ = entity_->getComponent<AnimHamsterStateMachine>();
	assert(anim_ != nullptr);
}

bool Combos::checkCombo(int action) {
	lastAttack_ = sdlutils().currRealTime();		//Actualizacion del timer
	bool finCombo = false;
	switch (cola_.size())
	{
	case 0:							//Lista vacia
		cola_.push(action);
		firstActionAnim(action);
		break;
	case 1:							//Si hay ataques almacenados se comprueban los combos
		if (action == cola_.back() && action != 2) cola_.push(action);
		else if (action == 1) { //Si entra uno fuerte
			if (cola_.back() == 0) {
				lightStrong(); //Fin Combo L + S
			}
			else {
				jumpStrong(); //Fin Combo J + S
			}
			finCombo = true;
		}
		else if (action == 0 && cola_.back() == 2) {
			cola_.push(action);
			grv_->setActive(false);
			entity_->getComponent<Transform>()->getVelZ() = 0;
			anim_->setAnimBool(HamStatesAnim::LIGHTATTACK1, true);
		}
		else { //Combo imposible -> cambio de acción
			cola_.pop();
			cola_.push(action);
			firstActionAnim(action);
		}
		break;
	case 2:					//3ª acción de combo
		if (action == cola_.back()) cola_.push(action);
		else if (action == 1 && cola_.front() == 2) { //Si entra fuerte a cbo salto, acaba
			jumpStrong();
			finCombo = true;
		}
		else {
			popUntilEmpty();
			cola_.push(action);
			firstActionAnim(action);
		}
		break;
	case 3:
		if (action == cola_.back()) {
			finCombo = true;
			fourConsecutives(); // 4 L, 4 S o J + 3 L 
		}
		else if (action == 1 && cola_.front() == 2) { //Si entra fuerte a cbo salto, acaba
			jumpStrong();
			finCombo = true;
		}
		else {
			popUntilEmpty();
			cola_.push(action);
			firstActionAnim(action);
		}
		break;
	default:
		break;
	}
	return finCombo;
}

void Combos::update() {
	if (!cola_.empty() && sdlutils().currRealTime() - lastAttack_ > CADENCE) {
		if (!grv_->isActive())
			grv_->setActive(true);
		popUntilEmpty();
	}

	//Fin de animaciones de combos
	if (anim_->getState() == HamStatesAnim::LIGHTCOMBO)
	{
		if (entity_->getComponent<Animator>()->OnAnimationFrameEnd())
		{

			anim_->setAnimBool(HamStatesAnim::LIGHTCOMBO, false);

		}

	}
}

void Combos::lightStrong() {
	anim_->setAnimBool(HamStatesAnim::STRONGCOMBO, true);
	popUntilEmpty();
}

void Combos::fourConsecutives() {
	if (cola_.back() == 0) {

		if (cola_.front() == 2) {
			grv_->setActive(true);
		}
		anim_->setAnimBool(HamStatesAnim::LIGHTCOMBO, true);
	}
	else;
		anim_->setAnimBool(HamStatesAnim::STRONGCOMBO, true);
	popUntilEmpty();
}

void Combos::jumpStrong() {
	anim_->setAnimBool(HamStatesAnim::STRONGATTACK, true);
	if (!grv_->isActive())
		grv_->setActive(true);

	popUntilEmpty();
}

void Combos::popUntilEmpty() {
	while (!cola_.empty()) 
		cola_.pop();
}

// Comprueba y llama a la animación que corresponda al entrar la primera acción
void Combos::firstActionAnim(int action) {
	switch (action)
	{
	case 0:
		anim_->setAnimBool(HamStatesAnim::LIGHTATTACK1, true);
		break;
	case 1:
		anim_->setAnimBool(HamStatesAnim::STRONGATTACK, true);
		break;
	case 2:
		anim_->setAnimBool(HamStatesAnim::JUMPUP, true);
		break;
	default:
		break;
	}
}
