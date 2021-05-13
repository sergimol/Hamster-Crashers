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

void Gravity::checkHeight(SDL_Rect& playerPos) {
	auto& z = tr_->getZ();
	auto& velZ = tr_->getVelZ();

	if (gravLocked() && sdlutils().currRealTime() > lockTimer_ + lockCooldown_)
		lockGrav(false);

	if (z > floor_ && sdlutils().currRealTime() > timer_ + jumpTimer_) {			//Aceleracion del salto afectado por gravedad
		if (gravityLocked_ && velZ <= 0)
		{
			velZ = 0;
		}
		else
		{
			velZ -= gravity_;
			timer_ = sdlutils().currRealTime();
		}
	}
	else if (z < floor_) {			//Final del salto	
		velZ = 0;
		z = floor_;
	}

	//Comprobamos la colision con los triggers de altura
	auto& heights = entity_->getMngr()->getMapH();
	int maxHigh = -1;
	for (Entity* alt : heights) {
		auto* aTr = alt->getComponent<Transform>();
		if (Collisions::collides(aTr->getPos(), aTr->getW(), aTr->getH(), Vector2D(playerPos.x, playerPos.y), playerPos.w, playerPos.h) && alt->getComponent<HeightObject>()->getZ() >= maxHigh) {
			maxHigh = alt->getComponent<HeightObject>()->getZ();
		}
	}

	//Si va a subir y no salta stuck=true, si ha subido más que el escalón actualizamos floor_
	stuck_ = false;
	if (maxHigh == -1) {
		inHeighChange_ = false;
	}
	else {
		inHeighChange_ = true;
		if (maxHigh > floor_) {
			if (z > maxHigh + 1) {
				floor_ = maxHigh;
				//Se actualiza el suelo actual del transform
				tr_->setFloor(floor_);
			}
			else {
				stuck_ = true;
			}
		}
		else if (maxHigh < floor_) {
			floor_ = maxHigh;
			tr_->setFloor(floor_);
		}
	}
}

void Gravity::onDisable() {
	tr_->getVelZ() = 0.0;
}