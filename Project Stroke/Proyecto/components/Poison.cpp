#include "Poison.h"
#include "Animator.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "Image.h"
#include "Cloud.h"

Poison::Poison(int dmg) : Ability(CLOUDCD), dmg_(dmg) {
};

Poison::~Poison() {
}

void Poison::update() {
	Ability::update();
	if (!onUse_) {
		if (cloud_ != nullptr)
			cloud_->setActive(false);
	}
}

void Poison::render() {
}
void Poison::action() {

	//Realizamos las animaciones

	if (tr_->getFlip())
		x = -1;
	else
		x = 1;

	//Y creamos la nube
	cloud_ = entity_->getMngr()->addEntity();

	cloud_->addComponent<Transform>(
		tr_->getPos() + Vector2D(tr_->getW() / 2 + x * COFFSETX, tr_->getH() / 2),
		Vector2D(x, 0.0f) * CBULLETSPEED, 10.0f, 10.0f, 0.0f,1,1);

	cloud_->addComponent<Image>(&sdlutils().images().at("keta"));

	cloud_->addComponent<Cloud>(dmg_);
}

