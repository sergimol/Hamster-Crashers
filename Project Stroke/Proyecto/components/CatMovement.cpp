#include "CatMovement.h"
#include "../utils/Vector2D.h"

void CatMovement::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void CatMovement::update() {
	if (start) {
		if (walk) {
			iniPos = tr_->getPos().getX();
			tr_->setVel(Vector2D(VEL, 0));
			walk = false;
			walking = true;
		}
		if (tr_->getPos().getX() < iniPos + MOVE && walking) {
			tr_->setVel(Vector2D(0, 0));
			timer = sdlutils().currRealTime();
			walking = false;
		}
		if (sdlutils().currRealTime() > timer + TIME && !walking) {
			walk = true;
		}
	}
}

void CatMovement::startChase() {
	start = true;
}
