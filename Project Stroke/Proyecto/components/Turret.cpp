#include "Turret.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "DisableOnExit.h"
#include "Image.h"
#include "BulletHit.h"
#include "Movement.h"
/*#include "Animator.h"
*/

Turret::Turret() : Ability(CD), x_(0), cadenceTime_(sdlutils().currRealTime()) {
};

Turret::~Turret() {

}

void Turret::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	st_ = entity_->getComponent<HamsterStateMachine>();
	assert(st_ != nullptr);

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

	actualSpeed_ = entity_->getComponent<EntityAttribs>()->getVel();
}

void Turret::update() {
	Ability::update();

	if (onUse) {
		if (sdlutils().currRealTime() > cadenceTime_ + CADENCESHOT) {

			//Crea la entidad
			auto bala = entity_->getMngr()->addEntity();

			if (entity_->getComponent<Transform>()->getFlip())
				x_ = -1;
			else
				x_ = 1;


			bala->addComponent<Transform>(
				tr_->getPos() + Vector2D(tr_->getW() / 2 + x_ * OFFSETX, tr_->getH() / 2 - OFFSETY),
				Vector2D(x_, 0.0f) * BULLETSPEED, 10.0f, 10.0f, 0.0f);

			bala->addComponent<Image>(&sdlutils().images().at("bullet"));

			bala->addComponent<DisableOnExit>();

			bala->addComponent<BulletHit>();

			bala->setGroup<Bullet_group>(true);

			cadenceTime_ = sdlutils().currRealTime();

		}
	}
}

void Turret::action() {
	//Reduce vel a la mitad
	entity_->getComponent<Movement>()->setSpeed(actualSpeed_ / 2);
	//Realizo las animaciones
}

void Turret::endAbility() {
	//Vuelve a vel original
	entity_->getComponent<Movement>()->setSpeed(actualSpeed_);
}