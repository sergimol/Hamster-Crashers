#include "GravityEntity.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "HeightObject.h"

void GravityEntity::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void GravityEntity::update() {
	auto& z = tr_->getZ();
	auto& velZ = tr_->getVelZ();

	//std::cout << velZ << "\n";

	if (z > floor&& sdlutils().currRealTime() > timer + jumpTimer_) {			//Aceleracion del salto afectado por gravedad
		velZ -= gravity_;
		timer = sdlutils().currRealTime();
	}
	else if (z < floor) {			//Final del salto	!!!!!!!!!(0 SE SUSTITUIRA POR LA Z DEL MAPA)!!!!!!!!
		velZ = 0;
		z = floor;
	}

	//Comprobamos la colision con los triggers de altura
	auto& heights = entity_->getMngr()->getMapH();
	int maxHigh = 0;
	for (Entity* alt : heights) {
		auto* aTr = alt->getComponent<Transform>();
		if (Collisions::collides(aTr->getPos(), aTr->getW(), aTr->getH(), Vector2D(tr_->getPos().getX(), tr_->getPos().getY()), tr_->getW(), tr_->getH()) && alt->getComponent<HeightObject>()->getZ() > maxHigh) {
			maxHigh = alt->getComponent<HeightObject>()->getZ();
		}
	}

	if (maxHigh > floor) {
		if (z > maxHigh + 1) {
			floor = maxHigh;
			//Se actualiza el suelo actual del transform
			tr_->setFloor(floor);
		}
	}
	else if (maxHigh < floor) {
		floor = maxHigh;
		tr_->setFloor(floor);
	}
}