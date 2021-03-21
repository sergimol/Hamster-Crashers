#include "Combos.h"

bool Combos::checkCombo(int action) {
	lastAttack_ = sdlutils().currRealTime();		//Actualizacion del timer
	bool finCombo = false;
	switch (cola_.size())
	{
	case 0:							//Lista vacia
		cola_.push(action);
		break;
	case 1:							//Si hay ataques almacenados se comprueban los combos
		if (action == cola_.back()) cola_.push(action);
		else if (action == 1) {
			lightStrong(); ////////
			finCombo = true;
		}
		else {
			cola_.pop();
			cola_.push(action);
		}
		break;
	case 2:
		if (action == cola_.back()) cola_.push(action);
		else {
			for (int i = 0; i < 2; i++)
				cola_.pop();
			cola_.push(action);
		}
		break;
	case 3:
		if (action == cola_.back()) {
			finCombo = true;
			fourConsecutives(); //////
		}
		else {
			for (int i = 0; i < 3; i++)
				cola_.pop();
			cola_.push(action);
		}
		break;
	default:
		break;
	}
	return finCombo;
}

void Combos::update() {
	if (!cola_.empty() && sdlutils().currRealTime() - lastAttack_ > CADENCE) {
		while (!cola_.empty()) {
			cola_.pop();
		}
	}
}

void Combos::lightStrong() {
	//anim.play(finCombo);

	while (!cola_.empty()) {
		cola_.pop();
	}
}

void Combos::fourConsecutives() {
	if (cola_.back() == 0);
		//anim.play(finComboLigeros);
	else;
		//anim.play(finComboFuertes);
	while (!cola_.empty()) {
		cola_.pop();
	}
}