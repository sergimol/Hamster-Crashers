#include "Turret.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "DisableOnExit.h"
#include "Image.h"
#include "BulletHit.h"
/*#include "Movement.h"
#include "Animator.h"
*/

Turret::Turret() : Ability(CD), x(0) {
};

Turret::~Turret() {

}

void Turret::update() {
	Ability::update();

	if (onUse) {
		if (sdlutils().currRealTime() > cadenceTime + CADENCESHOT) {

			//Crea la entidad
			auto bala = entity_->getMngr()->addEntity();

			if (entity_->getComponent<Transform>()->getFlip())
				x = -1;
			else
				x = 1;


			bala->addComponent<Transform>(
				tr_->getPos() + Vector2D(tr_->getW() / 2 + x * OFFSETX, tr_->getH() / 2 - OFFSETY),
				Vector2D(x, 0.0f) * BULLETSPEED, 10.0f, 10.0f, 0.0f);

			bala->addComponent<Image>(&sdlutils().images().at("bullet"));

			bala->addComponent<DisableOnExit>();

			bala->addComponent<BulletHit>();

			bala->setGroup<Bullet_group>(true);

			cadenceTime = sdlutils().currRealTime();

		}
	}
}

void Turret::action() {
	//Realizo las animaciones

}



