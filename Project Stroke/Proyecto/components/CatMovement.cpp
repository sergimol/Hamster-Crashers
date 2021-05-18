#include "CatMovement.h"
#include "../utils/Vector2D.h"

void CatMovement::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	grav_ = entity_->getComponent<Gravity>();
	assert(grav_ != nullptr);
}

void CatMovement::update()
{
	auto& z = tr_->getZ();
	auto& velZ = tr_->getVelZ();
	auto rect = tr_->getRectCollide();

	if (grav_ != nullptr && grav_->isActive())
		grav_->checkHeight(rect);
}