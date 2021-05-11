#include "Obstacle.h"
#include "Animator.h"
#include "SoundManager.h"
#include "../ecs/Manager.h"
#include "Dying.h"
#include "Item.h"
#include "Image.h"

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
		createItem();
		canBeHit_ = false;
	}
	else if(canBeHit_){
		anim->play(sdlutils().anims().at(keyWord_ + id_ + hitWord_));
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("dep2");
	}
}

void Obstacle::createItem() {
	auto* e = entity_->getMngr()->addEntity();

	ItemInfo it;
	
	int r = sdlutils().rand().nextInt(0, 10);
	
	if (r < 5) {
		it.tex = &sdlutils().images().at("heart3");
		it.ty = ItemType::Nut;
	}
	else if (r < 8){
		it.tex = &sdlutils().images().at("heart1");
		it.ty = ItemType::Apple;
	}
	else {
		it.tex = &sdlutils().images().at("heart2");
		it.ty = ItemType::WaterMelon;
	}
	e->addComponent<Transform>(Vector2D(tr_->getPos().getX()+ (tr_->getW()/2) - 25, tr_->getPos().getY() + (tr_->getH() / 2) - 25), Vector2D(0, 0), 50, 50, 0, tr_->getScaleW(), tr_->getScaleH());
	e->addComponent<Image>(it.tex);
	e->addComponent<Item>(it.ty);

	entity_->getMngr()->getItems().push_back(e);
}

