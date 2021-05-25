#include "ImageSecuence.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "Transition.h"

ImageSecuence::ImageSecuence(string newScene) :newScene_(newScene) {
	//Te comes una verga
}

void ImageSecuence::init() {
	if (newScene_ == level1) {
		auto anim = entity_->getMngr()->addEntity();
		anim->addComponent<Transform>(Vector2D(sdlutils().width() / 5, sdlutils().height() / 5), Vector2D(0, 0), 1000, 1000, 0, 1, 1);
		anim->addComponent<Animator>(
			&sdlutils().images().at("canelonSheet"),
			128,
			128,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim);
		auto anim2 = entity_->getMngr()->addEntity();
		anim2->addComponent<Transform>(Vector2D(sdlutils().width() / 5, sdlutils().height() / 5), Vector2D(0, 0), 1000, 1000, 0, 1, 1);
		anim2->addComponent<Animator>(
			&sdlutils().images().at("sardinillaSheet"),
			86,
			86,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			);
		keyAnimations.push(anim2);
	}
	else if (newScene_ == level2) {
		/*	keyAnimations.push(&sdlutils().images().at("sardinilla"));
			keyAnimations.push(&sdlutils().images().at("keta"));
			keyAnimations.push(&sdlutils().images().at("canelon"));*/
	}
	else if (newScene_ == controls) {
		controles = true;
		//keyAnimations.push(&sdlutils().images().at("controles"));
	}
	else if (newScene_ == hasMuerto) {
		gameOver = true;
		//keyAnimations.push(&sdlutils().images().at("hasMuerto"));
	}
	else if (newScene_ == hasGanado) {
		gameOver = true;
		//keyAnimations.push(&sdlutils().images().at("hasGanado"));
	}
	else if (newScene_ == level1Boss) {
		//keyAnimations.push(&sdlutils().images().at("hasGanado"));
	}

	imageRect.x = 0;
	imageRect.y = 0;
	imageRect.w = sdlutils().width();
	imageRect.h = sdlutils().height();

	trans_ = entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>();
}

void ImageSecuence::update() {
	if (entity_->isActive()) {
		if (!trans_->isFading() && (ih().keyDownEvent() || ih().isButtonDownEvent())) {
			if (!keyAnimations.empty()) {
				trans_->startFadeIn();
				next = true;
			}
		}

		if (next && !trans_->isFadingOut()) {
			keyAnimations.top()->setActive(false);
			keyAnimations.pop();
			if (!keyAnimations.empty())
				keyAnimations.top()->getComponent<Animator>()->setActive(true);
			next = false;
		}

		if (keyAnimations.empty() && !trans_->isFadingOut()) {
			if (controles) {
				entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>()->setState(GameStates::RUNNING);
				controles = false;
			}
			if (gameOver) {
				ih().startQuitEvent();
				gameOver = true;
			}
			trans_->createMap();
			entity_->setActive(false);
		}
	}
}

void ImageSecuence::render() {
	//if (!keyAnimations.empty())
	//	keyAnimations.top()->getComponent<Animator>()->render();
}