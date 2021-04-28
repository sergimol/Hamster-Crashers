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

	trans_ = entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>();
}

void ImageSecuence::update() {

	if (!trans_->isFading() && (ih().keyDownEvent()|| ih().isButtonDownEvent())) {
		if (!keyTextures.empty()) {
			trans_->startFadeIn();
			next = true;
		}
	}

	if (next && !trans_->isFadingOut()) {
		keyTextures.pop();
		next = false;
	}

	if (keyTextures.empty() && !trans_->isFadingOut()) {
		trans_->createMap();
		entity_->setActive(false);
	}
}

void ImageSecuence::render() {
	if (!keyTextures.empty())
		keyTextures.top()->render(imageRect);
}