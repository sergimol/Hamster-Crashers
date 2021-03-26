#include "FollowPlayer.h"
#include "Stroke.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

void FollowPlayer:: init() {
	mov_ = entity_->getComponent<MovementSimple>();
	assert(mov_ != nullptr);

	trHamnster_ = hamster_->getComponent<Transform>();
	assert(trHamnster_ != nullptr);
}

void FollowPlayer:: update() {
}


void FollowPlayer::onEnable(){
}

void FollowPlayer::onDisable()
{
}