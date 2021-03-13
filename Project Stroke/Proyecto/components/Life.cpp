#include "Life.h"

Life::Life() :
	health_(),
	maxHealth_()
{}

Life::Life(int life) :
	health_(life),
	maxHealth_(life)
{}

//Resta el daño y devuelve true si ha muerto
bool Life::recieveDmg(int dmg) {
	health_ -= dmg;
	std::cout << health_ << std::endl;
	//Actualizamos la healthBar
	if (entity_->hasComponent<UI>())
		entity_->getComponent<UI>()->bar(-dmg);
	//Si la vida ha bajado de 0...
	if (health_ <= 0) {
		//Actualizamos UI
		if (entity_->hasComponent<UI>())
			entity_->getComponent<UI>()->dep();

		health_ = 0;
		//Desactivamos la entidad
		//this->getEntity()->setActive(false);
		return true;
	}
	else
		return false;
}

//Sana 'hp' unidades
void Life::heal(int hp) {
	health_ += hp;
}