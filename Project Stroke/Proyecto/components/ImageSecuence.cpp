#include "ImageSecuence.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "Transition.h"
#include "../sdlutils/SDLUtils.h"

ImageSecuence::ImageSecuence(string newScene) :newScene_(newScene) {
	//Te comes una verga
}

void ImageSecuence::init() {
	float offsetCamera = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getUpOffset();
	int x = 0;// entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam().x;
	int y = 0;// entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam().y + 205;
	Vector2D pos(x, y + offsetCamera);
	if (newScene_ == "Level1") {
		//Cinematica 8
		auto anim8 = entity_->getMngr()->addEntity();
		anim8->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim8->addComponent<Animator>(
			&sdlutils().images().at("cine8"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim8);

		//Cinematica 7
		auto anim7 = entity_->getMngr()->addEntity();
		anim7->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim7->addComponent<Animator>(
			&sdlutils().images().at("cine7"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim7);

		//Cinematica 6
		auto anim6 = entity_->getMngr()->addEntity();
		anim6->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim6->addComponent<Animator>(
			&sdlutils().images().at("cine6"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim6);

		//Cinematica 5
		auto anim5 = entity_->getMngr()->addEntity();
		anim5->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim5->addComponent<Animator>(
			&sdlutils().images().at("cine5"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim5);

		//Cinematica 4
		auto anim4 = entity_->getMngr()->addEntity();
		anim4->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim4->addComponent<Animator>(
			&sdlutils().images().at("cine4"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim4);

		//Cinematica 3
		auto anim3 = entity_->getMngr()->addEntity();
		anim3->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim3->addComponent<Animator>(
			&sdlutils().images().at("cine3"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim3);

		//Cinematica 2
		auto anim2 = entity_->getMngr()->addEntity();
		anim2->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim2->addComponent<Animator>(
			&sdlutils().images().at("cine2"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim2);

		//Cinematica 1
		auto anim1 = entity_->getMngr()->addEntity();
		anim1->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim1->addComponent<Animator>(
			&sdlutils().images().at("cine1"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			);
		keyAnimations.push(anim1);

		keyAnimations.top()->getComponent<Animator>()->play(sdlutils().anims().at("cinematic_anim"));

	}
	else if (newScene_ == "Level2") {
		//Cinematica 13
		auto anim13 = entity_->getMngr()->addEntity();
		anim13->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim13->addComponent<Animator>(
			&sdlutils().images().at("cine13"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim13);

		//Cinematica 12
		auto anim12 = entity_->getMngr()->addEntity();
		anim12->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim12->addComponent<Animator>(
			&sdlutils().images().at("cine12"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim12);

		//Cinematica 11
		auto anim11 = entity_->getMngr()->addEntity();
		anim11->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim11->addComponent<Animator>(
			&sdlutils().images().at("cine11"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim11);

		//Cinematica 10
		auto anim10 = entity_->getMngr()->addEntity();
		anim10->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim10->addComponent<Animator>(
			&sdlutils().images().at("cine10"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim10);

		//Cinematica 9
		auto anim9 = entity_->getMngr()->addEntity();
		anim9->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim9->addComponent<Animator>(
			&sdlutils().images().at("cine9"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			);
		keyAnimations.push(anim9);


		keyAnimations.top()->getComponent<Animator>()->play(sdlutils().anims().at("cinematic_anim"));
	}
	else if (newScene_ == "Level3") {
		//Cinematica 16
		auto anim16 = entity_->getMngr()->addEntity();
		anim16->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim16->addComponent<Animator>(
			&sdlutils().images().at("cine16"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim16);

		//Cinematica 15
		auto anim15 = entity_->getMngr()->addEntity();
		anim15->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim15->addComponent<Animator>(
			&sdlutils().images().at("cine15"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim15);

		//Cinematica 14
		auto anim14 = entity_->getMngr()->addEntity();
		anim14->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim14->addComponent<Animator>(
			&sdlutils().images().at("cine14"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			);
		keyAnimations.push(anim14);


		keyAnimations.top()->getComponent<Animator>()->play(sdlutils().anims().at("cinematic_anim"));
	}
	else if (newScene_ == "Level3Boss") {
		//Cinematica 18
		auto anim18 = entity_->getMngr()->addEntity();
		anim18->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim18->addComponent<Animator>(
			&sdlutils().images().at("cine18"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim18);

		//Cinematica 17
		auto anim17 = entity_->getMngr()->addEntity();
		anim17->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim17->addComponent<Animator>(
			&sdlutils().images().at("cine17"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			);
		keyAnimations.push(anim17);


		keyAnimations.top()->getComponent<Animator>()->play(sdlutils().anims().at("cinematic_anim"));
	}
	else if (newScene_ == "final") {
		//Cinematica 25
		auto anim25 = entity_->getMngr()->addEntity();
		anim25->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim25->addComponent<Animator>(
			&sdlutils().images().at("cine25"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim25);

		//Cinematica 24
		auto anim24 = entity_->getMngr()->addEntity();
		anim24->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim24->addComponent<Animator>(
			&sdlutils().images().at("cine24"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim24);

		//Cinematica 23
		auto anim23 = entity_->getMngr()->addEntity();
		anim23->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim23->addComponent<Animator>(
			&sdlutils().images().at("cine23"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim23);

		//Cinematica 22
		auto anim22 = entity_->getMngr()->addEntity();
		anim22->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim22->addComponent<Animator>(
			&sdlutils().images().at("cine22"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim22);

		//Cinematica 21
		auto anim21 = entity_->getMngr()->addEntity();
		anim21->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim21->addComponent<Animator>(
			&sdlutils().images().at("cine21"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim21);

		//Cinematica 20
		auto anim20 = entity_->getMngr()->addEntity();
		anim20->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim20->addComponent<Animator>(
			&sdlutils().images().at("cine20"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			)->setActive(false);
		keyAnimations.push(anim20);

		//Cinematica 19
		auto anim19 = entity_->getMngr()->addEntity();
		anim19->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim19->addComponent<Animator>(
			&sdlutils().images().at("cine19"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			);
		keyAnimations.push(anim19);


		keyAnimations.top()->getComponent<Animator>()->play(sdlutils().anims().at("cinematic_anim"));
	}
	else if (newScene_ == "hasMuerto") {
		//Cinematica 19
		auto anim19 = entity_->getMngr()->addEntity();
		anim19->addComponent<Transform>(pos, Vector2D(0, 0), 1920, 1080, 0, 1, 1);
		anim19->addComponent<Animator>(
			&sdlutils().images().at("cineMuerte"),
			1920,
			1080,
			3,
			3,
			220,
			Vector2D(0, 0),
			3
			);
		keyAnimations.push(anim19);


		keyAnimations.top()->getComponent<Animator>()->play(sdlutils().anims().at("cinematic_anim"));
	}
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
			if (!keyAnimations.empty()) {
				keyAnimations.top()->getComponent<Animator>()->setActive(true);
				keyAnimations.top()->getComponent<Animator>()->play(sdlutils().anims().at("cinematic_anim"));
			}
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