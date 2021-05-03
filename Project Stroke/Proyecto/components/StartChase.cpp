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

void StartChase::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void StartChase::update() {
	for (Entity* hamsters : entity_->getMngr()->getPlayers()) {
		//Cogemos la posicion de cada hamster...
		auto hamsterTr = hamsters->getComponent<Transform>();

		//Cogemos la camara para hacer bien las colisiones
		SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

		if (!Collisions::collides(hamsterTr->getPos(), hamsterTr->getW(), hamsterTr->getH(),
			tr_->getPos(), tr_->getW(), tr_->getH())) {
		}
	}

	//Si todos los hamsters estan en el trigger
	if (!entity_->getMngr()->getPlayers().empty()) { //TODO ELIMINAR ULTIMA CONDICION TRIGGER
		//Empieza el Chase
		start();
	}
}

void StartChase::render() {
	if(debug) SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);
}

void StartChase::start() {
	for (Entity* hamsters : entity_->getMngr()->getPlayers()) {
		hamsters->getComponent<Movement>()->setActive(false);
		hamsters->getComponent<Ability>()->setActive(false);
		hamsters->getComponent<LightAttack>()->setActive(false);
		hamsters->getComponent<StrongAttack>()->setActive(false);
		hamsters->getComponent<MovementInChase>()->setActive(true);
	}
}