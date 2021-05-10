#include "Obstacle.h"
#include "Animator.h"
#include "SoundManager.h"
#include "../ecs/Manager.h"
#include "Dying.h"

void Obstacle::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

Obstacle::~Obstacle() {
	entity_->getMngr()->refreshObstacles();
}

void Obstacle::hit() {
	hits_--;

	auto* anim = entity_->getComponent<Animator>();

	assert(anim != nullptr);

	if (hits_ == 0 && canBeHit_) {
		anim->play(sdlutils().anims().at(keyWord_ + id_ + breakWord_));
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("dep2");
		entity_->addComponent<Dying>();
		canBeHit_ = false;
	}
	else if(canBeHit_){
		anim->play(sdlutils().anims().at(keyWord_ + id_ + hitWord_));
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("dep2");
	}
}

