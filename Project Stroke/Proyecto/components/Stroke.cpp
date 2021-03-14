#include "Stroke.h"
#include "Abilty.h"

void Stroke::init() {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
}

void Stroke::update() {
	// Comprobamos que haya pasado el tiempo suficiente entre comprobaciones
	if (sdlutils().currRealTime() >= timeLastUpdate_ + UPDATETIME) {
		// Número aleatorio para ver si infarta o no
		int i = r_.nextInt(0, 100);
		// Si i es menor que la probabilidad, infarta
		if(i <= chance_ + chanceFromAb_)
			entity_->setActive(false);

		timeLastUpdate_ = sdlutils().currRealTime();
	}
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

	//std::cout << chance_ + " " + chanceFromAb_ << std::endl;
}
