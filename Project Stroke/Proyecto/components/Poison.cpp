#include "Poison.h"
#include "Movement.h"
#include "Animator.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
#include "EntityAttribs.h"
#include "Transform.h"
#include "Image.h"
#include "Cloud.h"

Poison::Poison(int dmg) : Ability(CLOUDCD), dmg_(dmg) {
	
};

Poison::~Poison() {

}

void Poison::update() {
	Ability::update();
	if (!lastActive) {
		if (cloud != nullptr)
			cloud->setActive(false);
	}
}

void Poison::action() {
	//Realizamos las animaciones
	if (tr_->getFlip())
		x = -1;
	else
		x = 1;

	cloud = entity_->getMngr()->addEntity();

	cloud->addComponent<Transform>(
		tr_->getPos() + Vector2D(tr_->getW() / 2 + x * COFFSETX, tr_->getH() / 2),
		Vector2D(x, 0.0f) * CBULLETSPEED, 10.0f, 10.0f, 0.0f);

	cloud->addComponent<Image>(&sdlutils().images().at("bullet"));

	cloud->addComponent<Cloud>(dmg_);
}

