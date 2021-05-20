#include "Turret.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "DisableOnExit.h"
#include "Image.h"
#include "BulletHit.h"
#include "Movement.h"
//#include "Animator.h"

Turret::Turret() : Ability(2000), x_(0), cadenceTime_(sdlutils().currRealTime()) {
};

Turret::~Turret() {
}


void Turret::update() {
	if (state_->getState() == GameStates::RUNNING) {
		Ability::update();

		if (onUse_) {
			if (sdlutils().currRealTime() > cadenceTime_ + CADENCESHOT) {

				//Crea la entidad
				auto* bala = entity_->getMngr()->addEntity();

				if (entity_->getComponent<Transform>()->getFlip())
					x_ = -1;
				else
					x_ = 1;

				//Meto los componentes
				bala->addComponent<Transform>(
					tr_->getPos() + Vector2D(tr_->getW() / 2 + x_ * OFFSETX, tr_->getH() / 2 - OFFSETY),
					Vector2D(x_, 0.0f) * BULLETSPEED, 10.0f, 10.0f, 0.0f, 1, 1);

				bala->addComponent<Image>(&sdlutils().images().at("bullet"));

				bala->addComponent<DisableOnExit>();

				bala->addComponent<BulletHit>(tr_->getPos().getY() + tr_->getH());

				bala->setGroup<Bullet_group>(true);

				cadenceTime_ = sdlutils().currRealTime();
			}
		}
	}
}

void Turret::action() {

	//Reduce vel a la mitad mientras dispara
	attribs_->setVel(attribs_->getVel() / 2);
	entity_->getComponent<EntityAttribs>()->setInvincibility(true);

	//Realizo las animaciones
}

void Turret::endAbility() {

	//Vuelve a vel original
	attribs_->resetVel();
	entity_->getComponent<EntityAttribs>()->setInvincibility(false);
}