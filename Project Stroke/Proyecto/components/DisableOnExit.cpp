// This file is part of the course TPV2@UCM - Samir Gena
#include "DisableOnExit.h"
#include "../ecs/Manager.h"
#include "../ecs/Camera.h"

DisableOnExit::DisableOnExit() :
	tr_(nullptr), state_(nullptr) {
}

DisableOnExit::~DisableOnExit() {
}

void DisableOnExit::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void DisableOnExit::update() {
	if (state_->getState() == GameStates::RUNNING) {
		auto& pos = tr_->getPos();
		auto w = tr_->getW();
		auto h = tr_->getH();
		SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

		if (entity_->hasGroup<Bullet_group>()) {
			if (pos.getX() < cam.x) {
				entity_->setActive(false);
			}
			else if (pos.getX() + w > cam.x + cam.w) {
				entity_->setActive(false);
			}
			//else if (pos.getY() < cam.y + (cam.h / 2)) {
			//	entity_->setActive(false);
			//}
			//else if (pos.getY() + h > cam.y - (cam.h / 2)) {
			//	entity_->setActive(false);
			//}
		}
	}
}


