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
	for (Entity* hamsters : entity_->getMngr()->getPlayers()) {
		//Cogemos la posicion de cada hamster...
		auto hamsterTr = hamsters->getComponent<Transform>();

		//Cogemos la camara para hacer bien las colisiones
		SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

		if (!Collisions::collides(hamsterTr->getPos(), hamsterTr->getW(), hamsterTr->getH(),
			tr_->getPos(), tr_->getW(), tr_->getH())) {
			canChange = false;
		}
	}

	//Si todos los hamsters estan en el trigger
	if (canChange)
		//Cambio de escena
		entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>()->changeScene(nameScene);
	else
		canChange = true;
}

void TriggerScene::render() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);
}