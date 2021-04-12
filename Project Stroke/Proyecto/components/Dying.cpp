#include "Dying.h"


void Dying::init() {
	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);
	timer = sdlutils().currRealTime();
}

void Dying::update() {

	if (!blinkActive && sdlutils().currRealTime() >= timer + TIMEBEFOREBLINK) {
		blinkActive = true;
		timer = sdlutils().currRealTime();
	}

	if (blinkActive && sdlutils().currRealTime() >= timer + BLINK) {
		blink();
	}
	if (blinksToDie > DEADCOUNT)
		//Desactivamos el componente
		entity_->setActive(false);
}

void Dying::blink() {
	//Se actualiza el tiempo
	timer = sdlutils().currRealTime();

	//Parpadea una vez
	blinksToDie++;

	animActive = !animActive;
	//Y activamos o desactivamos el animator para dar sensacion de parpadeo
	anim_->setActive(animActive);

}
