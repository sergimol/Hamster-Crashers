#include "CatMovement.h"
#include "../utils/Vector2D.h"

void CatMovement::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	tr_->setVel(Vector2D(VEL, 0));
}
