#include "Turret.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "DisableOnExit.h"
#include "Image.h"
#include "BulletHit.h"
#include "Movement.h"
#include "AnimHamsterStateMachine.h"
#include "SoundManager.h"
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
				//Sonido
				entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("monchiSpecial");
				//Crea la entidad
				auto* bala = entity_->getMngr()->addEntity();

				if (entity_->getComponent<Transform>()->getFlip())
					x_ = -1;
				else
					x_ = 1;

				//Meto los componentes
				bala->addComponent<Transform>(
					tr_->getPos() + Vector2D(tr_->getW() / 2 + x_ * OFFSETX, tr_->getH() / 2 - OFFSETY - tr_->getFloor() - (tr_->getZ()-tr_->getFloor())),
					Vector2D(x_, 0.0f) * BULLETSPEED, 12.0f*3, 8.0f*3, 0.0f, 1, 1)->getFlip() = entity_->getComponent<Transform>()->getFlip();

				bala->addComponent<Image>(&sdlutils().images().at("bullet"));

				bala->addComponent<DisableOnExit>();

				bala->addComponent<BulletHit>();

				bala->setGroup<Bullet_group>(true);

				cadenceTime_ = sdlutils().currRealTime();
			}
		}
	}
}

void Turret::action() {

	//Reduce vel a la mitad mientras dispara
	entity_->getComponent<EntityAttribs>()->setVel(entity_->getComponent<EntityAttribs>()->getVel() / 4);
	entity_->getComponent<EntityAttribs>()->setInvincibility(true);

	//Realizo las animaciones
}

void Turret::endAbility() {

	//Vuelve a vel original
	entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::ABILITY, false);
	entity_->getComponent<EntityAttribs>()->setInvincibility(false);
	entity_->getComponent<EntityAttribs>()->resetVel();
}