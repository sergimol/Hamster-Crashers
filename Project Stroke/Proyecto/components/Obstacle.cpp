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
	
}

void Obstacle::hit() {
	hits_--;

	auto* anim = entity_->getComponent<Animator>();

	assert(anim != nullptr);

	//Destruimos el objeto si los golpes llegan 0
	if (hits_ == 0 && canBeHit_) {
		anim->play(sdlutils().anims().at(keyWord_ + breakWord_));
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("dep2");
		entity_->addComponent<Dying>();
		createItem();
		canBeHit_ = false;
		
		//Falseo de eliminacion. 
		//Desactivamos la entidad, la borramos de Obstacles y la volvemos a activar, de esa forma se borrará más tarde entities
		entity_->setActive(false);
		entity_->getMngr()->refreshObstacles();
		entity_->setActive(true);
	}
	//En caso de que los golpes nunca lleguen a 0, siempre entrará en la animación de golpeo
	else if(canBeHit_){
		anim->play(sdlutils().anims().at(keyWord_ + hitWord_));
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("dep2");
	}
}

void Obstacle::createItem() {
	auto* e = entity_->getMngr()->addEntity();

	ItemInfo it;
	
	int r = sdlutils().rand().nextInt(0, 10);
	
	if (r < 6){
		it.tex = &sdlutils().images().at("apple");
		it.ty = ItemType::Apple;
	}
	else {
		it.tex = &sdlutils().images().at("cheese");
		it.ty = ItemType::Cheese;
	}
	e->addComponent<Transform>(Vector2D(tr_->getPos().getX() + (tr_->getW()/2), tr_->getPos().getY() + (tr_->getH() / 2) - 70), 
		Vector2D(0, 0), 
		200, 
		200, 
		0, 
		tr_->getScaleW(), 
		tr_->getScaleH());

	e->addComponent<Image>(it.tex);
	e->addComponent<Item>(it.ty);

	entity_->getMngr()->getItems().push_back(e);
}

