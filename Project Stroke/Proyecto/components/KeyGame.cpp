#include "KeyGame.h"
#include "../utils/Collisions.h"

void KeyGame::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	tr_->setVel(Vector2D(vel_, 0));
	rect_end = rect_;
	rect_end.x = rect_end.x - 10;
	rect_end.y = rect_end.y - 10;
}

void KeyGame::update() {
	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(key_) && Collisions::collides(tr_->getPos(), tr_->getW(), tr_->getH(), Vector2D(rect_.x, rect_.y), rect_.w, rect_.h)) {
			hitSkillCheck();
		}
		else missedSkillCheck();
	}

	if (Collisions::collides(tr_->getPos(), tr_->getW(), tr_->getH(), Vector2D(rect_end.x, rect_end.y), rect_end.w, rect_end.h)) {
		missedSkillCheck();
	}
	//if collisiona al final
}


void KeyGame::missedSkillCheck() {
	misstakes_++;
	entity_->setActive(false);
}

void KeyGame::hitSkillCheck() {
	entity_->setActive(false);
}