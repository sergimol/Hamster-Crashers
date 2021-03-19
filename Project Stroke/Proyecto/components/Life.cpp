#include "Life.h"

Life::Life() :
	health_(),
	maxHealth_()
{}

Life::Life(int life) :
	health_(life),
	maxHealth_(life)
{}

void Life::init() {
		hms_ = entity_->getComponent<HamsterStateMachine>();                                  
}

//Resta el da�o y devuelve true si ha muerto
bool Life::recieveDmg(int dmg) {
	health_ -= dmg;
	//std::cout << health_ << std::endl;
	//Actualizamos la healthBar
	if (entity_->hasComponent<UI>())
		entity_->getComponent<UI>()->bar(-dmg);
	std::cout << "me cago en tus muertos" << health_ << std::endl;
	//Si la vida ha bajado de 0...
	if (health_ <= 0) {
			if (hms_ != nullptr) {
				hms_->getState() = HamStates::DEAD;
			}
		//Actualizamos UI
		if (entity_->hasComponent<UI>())
			entity_->getComponent<UI>()->dep();

		health_ = 0;
		//Desactivamos la entidad
		//entity_->setActive(false);

		return true;
	}
	else
		return false;
}

//Sana 'hp' unidades
void Life::heal(int hp) {	
	if (health_ + hp >= maxHealth_) {
		hp = maxHealth_ - health_;
		health_ = maxHealth_;
	}
	else {
		health_ += hp;
	}
	if (entity_->hasComponent<UI>())
		entity_->getComponent<UI>()->bar(hp);

	std::cout << "ave maria" <<health_ << std::endl;
}