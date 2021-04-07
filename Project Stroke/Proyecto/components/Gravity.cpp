#include "Gravity.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "../ecs/Manager.h"
#include "HeightObject.h"

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
	else if (z < floor) {			//Final del salto	
		velZ = 0;
		z = floor;
	}
	
	auto& heights = entity_->getMngr()->getMapH();
	for (Entity* alt : heights) {
		auto* aTr = alt->getComponent<Transform>();
		if (Collisions::collides(tr_->getPos(), tr_->getW(), tr_->getH(), aTr->getPos(), aTr->getW(), aTr->getH())) {
			floor = alt->getComponent<HeightObject>()->getZ();
			return;
		}
	}
}

void Gravity::onDisable() {
	tr_->getVelZ() = 0.0;
}