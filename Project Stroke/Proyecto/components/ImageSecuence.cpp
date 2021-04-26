#include "ImageSecuence.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transition.h"


ImageSecuence::ImageSecuence(string newScene) {
	if (newScene == level1) {
		keyTextures.push(&sdlutils().images().at("transition"));
		keyTextures.push(&sdlutils().images().at("transition"));
		keyTextures.push(&sdlutils().images().at("transition"));
	}
	else if (newScene == level2) {
		keyTextures.push(&sdlutils().images().at("sardinilla"));
		keyTextures.push(&sdlutils().images().at("keta"));
		keyTextures.push(&sdlutils().images().at("canelon"));
	}
}

void ImageSecuence::init() {
	imageRect.x = 0;
	imageRect.y = 0;
	imageRect.w = sdlutils().width();
	imageRect.h = sdlutils().height();
}

void ImageSecuence::update() {

	if (ih().keyDownEvent()) {
		if (!keyTextures.empty() && !entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>()->isFading()) {
			entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>()->startFadeIn();
			next = true;
		}
	}

	if (next && !entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>()->isFading()) {
		keyTextures.pop();
		next = false;
	}

	if (keyTextures.empty() && !entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>()->isFading()) {
		entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>()->createMap();
		entity_->setActive(false);
	}
}

void ImageSecuence::render() {
	if (!keyTextures.empty())
		keyTextures.top()->render(imageRect);
}