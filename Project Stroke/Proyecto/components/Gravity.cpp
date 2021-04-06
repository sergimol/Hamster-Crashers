#include "Gravity.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

void Gravity::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_!=nullptr);
}

void Gravity::update() {
	auto& z = tr_->getZ();
	auto& velZ = tr_->getVelZ();

	if (z > floor && sdlutils().currRealTime() > timer + jumpTimer_) {			//Aceleracion del salto afectado por gravedad
		velZ -= gravity_;
		timer = sdlutils().currRealTime();
	}
	else if (z < floor) {			//Final del salto	!!!!!!!!!(0 SE SUSTITUIRA POR LA Z DEL MAPA)!!!!!!!!
		velZ = 0;
		z = floor;
	}
}

void Gravity::onDisable() {
	tr_->getVelZ() = 0.0;
}