#include "TriggerScene.h"
#include "Transition.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../components/MapMngr.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../ecs/Camera.h"
#include "../sdlutils/SDLUtils.h"

void TriggerScene::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void TriggerScene::update() {
	int hamInside = 0;
	for (Entity* hamsters : entity_->getMngr()->getPlayers()) {
		//Cogemos la posicion de cada hamster...
		auto hamsterTr = hamsters->getComponent<Transform>();

		if (!hamsters->getComponent<HamsterStateMachine>()->cantBeTargeted()) {
			if (!Collisions::collides(hamsterTr->getPos(), hamsterTr->getW(), hamsterTr->getH(),
				tr_->getPos(), tr_->getW(), tr_->getH())) {
				canChange = false;
			}
			else
				hamInside++;
		}
	}

	//Si todos los hamsters estan en el trigger
	if (hamInside != 0 && canChange && !entity_->getMngr()->getPlayers().empty()) { //TODO ELIMINAR ULTIMA CONDICION TRIGGER
		entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->changeCamState(State::Players);
		//Cambio de escena
		entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>()->changeScene(nameScene, true, numT, false);
		entity_->setActive(false);
	}
	else
		canChange = true;
}

void TriggerScene::render() {
	if (debug) SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);
}