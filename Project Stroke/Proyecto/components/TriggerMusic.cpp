#include "TriggerMusic.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "SoundManager.h"


void TriggerMusic::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

}

void TriggerMusic::update() {
	if (!play) {
		for (Entity* hamsters : entity_->getMngr()->getPlayers()) {
			//Cogemos la posicion de cada hamster...
			auto hamsterTr = hamsters->getComponent<Transform>();

			//Cogemos la camara para hacer bien las colisiones
			SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

			if (Collisions::collides(hamsterTr->getPos(), hamsterTr->getW(), hamsterTr->getH(),
				tr_->getPos(), tr_->getW(), tr_->getH())) {
				play = true;


				//Reproducimos el sonido
				entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play(musicName_);


				//Y eliminamos el trigger de evento
				entity_->setActive(false);
			}
		}
	}
}



void TriggerMusic::render() {
	if (debug) SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);
}
