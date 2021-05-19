#include "Poison.h"
#include "Animator.h"
#include "Movement.h"
#include "ControlHandler.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "Image.h"
#include "AnimHamsterStateMachine.h"
#include "Cloud.h"

Poison::Poison(int dmg) : Ability(2000), dmg_(dmg) {
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

void Poison::endAbility() {
	entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::ABILITY, false);
	entity_->getComponent<ControlHandler>()->setActive(true);
}

void Poison::action() {
	//Realizamos las animaciones
	entity_->getComponent<ControlHandler>()->setActive(false);

	if (tr_->getFlip())
		x = -1;
	else
		x = 1;

	//Y creamos la nube
	cloud_ = entity_->getMngr()->addEntity();

	auto rectCol = tr_->getRectCollide();

	cloud_->addComponent<Transform>(
		Vector2D(rectCol.x + ((x == -1) ? -134.0f * 3 : rectCol.w), rectCol.y - rectCol.h / 2),
		Vector2D(x, 0.0f) * CBULLETSPEED, 134.0f * 3, 58.0f * 3, 0.0f, 1, 1)->getFlip() = (x == -1);

	//Texture* tex, int w, int h, int c, int r, Uint32 f, Vector2D sf, int dur
	cloud_->addComponent<Animator>(&sdlutils().images().at("cloud"),
		134,
		58,
		14,
		1,
		60,
		Vector2D(0, 0),
		14);

	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("ketaSpecial");
	cloud_->addComponent<Cloud>(dmg_);
}

