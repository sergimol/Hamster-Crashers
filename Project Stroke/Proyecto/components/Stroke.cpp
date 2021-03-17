#include "Stroke.h"
#include "Abilty.h"

void Stroke::init() {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
		hms_ = entity_->getComponent<HamsterStateMachine>();
		assert(hms_ != nullptr);
}

void Stroke::update() {
	int t = sdlutils().currRealTime();
	// Comprobación de la reducción de la probabilidad
	if (t >= timeLastIncrease_ + TIMETODECREASE && t >= timeLastDecrease_ + TIMEBETWEENDECREASES) {
		chance_--;
		chanceFromAb_--;
		if (chance_ < 1)
			chance_ = 1;
		if (chanceFromAb_ < 0)
			chanceFromAb_ = 0;

		timeLastDecrease_ = t;
	}

	// Comprobamos que haya pasado el tiempo suficiente entre actualizaciones
	if (t >= timeLastUpdate_ + UPDATETIME) {
		// Número aleatorio para ver si infarta o no
		int i = r_.nextInt(0, 100);
		// Si i es menor que la probabilidad, infarta
		if (i <= chance_ + chanceFromAb_) {
			//TODO madremia que no lo podemos desactivar porque hay que quitarlo de la lsita de player y noseque algo habra que ahcer para que la camara no explote
			//entity_->setActive(false);
			hms_->getState() = HamStates::INFARCTED;
		}
			

		timeLastUpdate_ = t;
	}

	std::cout << chance_ << " " << chanceFromAb_ << std::endl;
}

void Stroke::increaseChance(int n, Component* c) {
	Ability* a = dynamic_cast<Ability*>(c);
	if (a == nullptr) {
		chance_ += n;
		if(chance_ > MAXCHANCE)
			chance_ = MAXCHANCE;
	}
	else {
		chanceFromAb_ += n;
		if(chanceFromAb_ > MAXAB)
			chanceFromAb_ = MAXAB;
	}
	
	timeLastIncrease_ = sdlutils().currRealTime();
	//std::cout << chance_ + " " + chanceFromAb_ << std::endl;
}
