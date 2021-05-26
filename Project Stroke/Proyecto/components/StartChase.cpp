#include "StartChase.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../sdlutils/SDLUtils.h"

#include "Movement.h"
#include "MovementInChase.h"
#include "Ability.h"
#include "LightAttack.h"
#include "StrongAttack.h"
#include "Roll.h"
#include "Pray.h"
#include "Turret.h"
#include "Poison.h"
#include "CatMovement.h"
#include "AnimHamsterStateMachine.h"

void StartChase::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

}

void StartChase::update() {
	if (!collide) {
		for (Entity* hamsters : entity_->getMngr()->getPlayers()) {
			//Cogemos la posicion de cada hamster...
			auto hamsterTr = hamsters->getComponent<Transform>();

			//Cogemos la camara para hacer bien las colisiones
			SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

			if (Collisions::collides(hamsterTr->getPos(), hamsterTr->getW(), hamsterTr->getH(),
				tr_->getPos(), tr_->getW(), tr_->getH())) {
				time_ = sdlutils().currRealTime();
				collide = true;

				for (Entity* hamsters : entity_->getMngr()->getPlayers()) {
					string id = hamsters->getComponent<EntityAttribs>()->getId();

					if (id == "sardinilla") {
						hamsters->getComponent<Roll>()->deactiveAbility();
					}
					else if (id == "canelon" || id == "canelonDemon")
						hamsters->getComponent<Pray>()->stopUseAbility();
					else if (id == "keta")
						hamsters->getComponent<Poison>()->deactiveAbility();
					else
						hamsters->getComponent<Turret>()->deactiveAbility();

					hamsters->getComponent<LightAttack>()->setActive(false);
					hamsters->getComponent<StrongAttack>()->setActive(false);

					hamsters->getComponent<Movement>()->setActive(false);

					//Quitamos su velocidad
					hamsters->getComponent<Transform>()->setVel(Vector2D(0,0));

					//Desactivamos el Move y Ability (Idle se activa por defecto)
					hamsters->getComponent<AnimHamsterStateMachine>()->resetAnim();

					//Y hacemos que la camara siga al gato
					auto* cam_ = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>();
					auto tr_ = entity_->getMngr()->getHandler<Cat_>()->getComponent<Transform>();
					cam_->setGoToCat(true);
					cam_->setGoToTracker(true);
					cam_->changeCamState(State::GoingTo);
					cam_->changeCamFollowPos(tr_->getPos().getX() - (sdlutils().width() / 2 - tr_->getW() + 10 ));

					//Levantamos al gato
					entity_->getMngr()->getHandler<Cat_>()->getComponent<Animator>()->play(sdlutils().anims().at("cat_wakeup"));

					//Y movemos el trigger
					auto& pos = entity_->getMngr()->getHandler<TriggetCat>()->getComponent<Transform>()->getPos();
					pos = pos + Vector2D(500,0);
				}
			}
		}
	}
	//Una vez haya chocado con el trigger...
	else {

		//Cuando pasen X segundos...
		if (sdlutils().currRealTime() > time_ + COOLDOWN_) {

			//Cambiamos el sistema de movimiento para comenzar el segundo boss
			start();

			//Y eliminamos el trigger de evento
			entity_->setActive(false);
		}
	}
}

void StartChase::render() {
	if (debug) SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);
}

void StartChase::start() {

	//Damos velocidad al gato
	entity_->getMngr()->getHandler<Cat_>()->getComponent<CatMovement>()->start();

	entity_->getMngr()->getHandler<Cat_>()->getComponent<Animator>()->play(sdlutils().anims().at("cat_chasing"));

	for (Entity* hamsters : entity_->getMngr()->getPlayers()) {

		//Activamos el nuevo sistema de movimiento a cada hamster
		hamsters->getComponent<MovementInChase>()->setActive(true);
	}
}
