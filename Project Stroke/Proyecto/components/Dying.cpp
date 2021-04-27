﻿#include "Dying.h"

void Dying::init() {

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

	timer_ = sdlutils().currRealTime();
}

void Dying::update() {

	//Timer
	if (!blinkActive_ && sdlutils().currRealTime() >= timer_ + TIMEBEFOREBLINK) {
		blinkActive_ = true;
		timer_ = sdlutils().currRealTime();
	}

	//Empieza a parpadear
	if (blinkActive_ && sdlutils().currRealTime() >= timer_ + BLINK) {
		blink();
	}

	//Cuando se acaba el timer...
	if (blinksToDie_ > DEADCOUNT)
		//Desactivamos el componente
		entity_->setActive(false);
}

void Dying::blink() {
	//Se actualiza el tiempo
	timer_ = sdlutils().currRealTime();

	//Parpadea una vez
	blinksToDie_++;

	animActive_ = !animActive_;
	//Y activamos o desactivamos el animator para dar sensacion de parpadeo
	anim_->setActive(animActive_);

}
