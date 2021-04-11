#include "Gravity.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "../ecs/Manager.h"
#include "HeightObject.h"
#include "Transform.h"

void Gravity::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Gravity::update() {
	auto& z = tr_->getZ();
	auto& velZ = tr_->getVelZ();

	if (z > floor && sdlutils().currRealTime() > timer + jumpTimer_) {			//Aceleracion del salto afectado por gravedad
		velZ -= gravity_;
		timer = sdlutils().currRealTime();
	}
	else if (z < floor) {			//Final del salto	
		velZ = 0;
		z = floor;
	}
	//Comprobamos la colision con los triggers de altura
	auto& heights = entity_->getMngr()->getMapH();
	int maxHigh = 0;
	for (Entity* alt : heights) {
		auto* aTr = alt->getComponent<Transform>();
		if (Collisions::collides(aTr->getPos(), aTr->getW(), aTr->getH(), tr_->getPos(), tr_->getW(), tr_->getH())) {
			if (alt->getComponent<HeightObject>()->getZ() > maxHigh)
				maxHigh = alt->getComponent<HeightObject>()->getZ();
		}
	}
	floor = maxHigh;
}

void Gravity::onDisable() {
	tr_->getVelZ() = 0.0;
}