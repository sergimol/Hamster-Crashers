#include "BackGround.h"

void BackGround::update() {
	Vector2D antPos = camPos_;
	camPos_ = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCamPos();
	tr_->setPos(Vector2D(tr_->getPos().getX() + (camPos_.getX() - antPos.getX())*pxVel_/100, 0));
}