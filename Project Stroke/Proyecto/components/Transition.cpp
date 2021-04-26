#include "Transition.h"
#include "ImageSecuence.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../ecs/Camera.h"
#include "../sdlutils/SDLUtils.h"

using namespace std;

void Transition::init() {
	tx_->setBlendMode(SDL_BLENDMODE_BLEND);

	blackRect.x = 0;
	blackRect.y = 0;
	blackRect.w = sdlutils().width();
	blackRect.h = sdlutils().height();
}

void Transition::update() {
	if (fadingIn)
		fadeIn();

	if (fadingOut)
		fadeOut();

}

void Transition::render() {
	if (fadingOut || fadingIn) {
		tx_->render(blackRect);
	}
}


void Transition::fadeIn() {
	//FADE IN

// Comprueba si hay textura
	if (tx_) {
		// Setea el alpha de la textura
		tx_->setAlpha(alpha);
	}

	// Actualiza el alpha de la textura
	if (alpha < SDL_ALPHA_OPAQUE) {
		alphaCalc += FADE_SPEED * (SDL_GetTicks() / 1000);
		alpha = alphaCalc;
	}

	// Si el alpha supera 255, lo iguala a 255;
	if (alpha >= SDL_ALPHA_OPAQUE) {
		alpha = SDL_ALPHA_OPAQUE;
		alphaCalc = (float)SDL_ALPHA_OPAQUE;
		if (change)
			sceneTransition();
		startFadeOut();
	}
}

void Transition::fadeOut() {
	//FADE OUT

// Comprueba si hay textura
	if (tx_) {
		// Setea el alpha de la textura
		tx_->setAlpha(alpha);
	}

	// Actualiza el alpha de la textura
	if (alpha > SDL_ALPHA_TRANSPARENT) {
		alphaCalc -= FADE_SPEED * (SDL_GetTicks() / 1000);
		alpha = alphaCalc;
	}

	// Si el alpha esta por debajo de 0, lo iguala a 0;
	if (alpha <= SDL_ALPHA_TRANSPARENT) {
		alpha = SDL_ALPHA_TRANSPARENT;
		alphaCalc = (float)SDL_ALPHA_TRANSPARENT;
		fadingOut = false;
	}
}

void Transition::changeScene(string nameScene) {
	change = true;
	nameScene_ = nameScene;
	startFadeIn();
}

void Transition::sceneTransition() {
	change = false;
	//Desactivamos todas las entidades (Salvo la cámara)
	for (Entity* e : entity_->getMngr()->getEntities()) {
		//Si la entidad que voy a coger no es la camara...
		if (e->getMngr()->getHandler<Camera__>() != e && e->getMngr()->getHandler<LevelHandlr>() != e 
			&& e->getMngr()->getHandler<StateMachine>() != e && e->getMngr()->getHandler<Mother>() != e)
			//La elimino
			e->setActive(false);
	}

	for (Entity* e : entity_->getMngr()->getTiles())
		e->setActive(false);

	for (Entity* e : entity_->getMngr()->getMapH())
		e->setActive(false);

	for (Entity* e : entity_->getMngr()->getBgs())
		e->setActive(false);

	entity_->getMngr()->refreshDeadBodies();
	entity_->getMngr()->refreshEnemies();
	//mngr_->refreshItems();
	entity_->getMngr()->refreshObstacles();
	entity_->getMngr()->refreshPlayers();

	//Y creamos uno nuevo
	auto* images = entity_->getMngr()->addEntity();
	images->addComponent<ImageSecuence>(nameScene_);


}

void Transition::createMap() {
	//Y creamos uno nuevo
	auto* mapa = entity_->getMngr()->addEntity();
	mapa->addComponent<MapMngr>();
	mapa->getComponent<MapMngr>()->loadNewMap("resources/images/tiled/" + nameScene_);

	//Metemos al mapa en el Handler de Map
	entity_->getMngr()->setHandler<Map>(mapa);
}

bool Transition::isFading() {
	return fadingIn;
}