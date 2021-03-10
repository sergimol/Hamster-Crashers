#include "Life.h"

Life::Life() :
	health_() {
}

Life::Life(int life) : health_(life) {}

//Resta el daño y devuelve true si ha muerto
bool Life::recieveDmg(int dmg) {
	health_ -= dmg;
	std::cout << health_<<std::endl;

	//Si la vida ha bajado de 0...
	if (health_ <= 0) {
		health_ = 0;
		//Desactivamos la entidad
		this->getEntity()->setActive(false);
		return true;
	}
	else
		return false;
}

//Sana 'hp' unidades
void Life::heal(int hp) {
	health_ += hp;
}