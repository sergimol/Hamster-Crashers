// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Bounce.h"
#include "../components/KeyBoardCtrl.h"
#include "../components/Rectangle.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/DeAcceleration.h"
#include "../components/FighterCtrl.h"
#include "../components/Movement.h"
#include "../components/LightAttack.h"
#include "../components/StrongAttack.h"
#include "../components/Stroke.h"
#include "../components/UI.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Squeak Ship", 800, 600,
		"../../../Proyecto/resources/config/hamsters.resources.json");

	auto* hamster1 = mngr_->addEntity();
	hamster1->addComponent<Transform>(
		Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 128.0f, 128.0f, 0.0f);
	hamster1->addComponent<Image>(&sdlutils().images().at("sardinilla"));
	hamster1->addComponent<Movement>();
	hamster1->addComponent<LightAttack>(20);
	hamster1->addComponent<StrongAttack>(30);
	hamster1->addComponent<Life>(100);
	hamster1->addComponent<Stroke>();
	//hamster1->addComponent<UI>("sardinilla");


	//Enemigo de prueba
	auto* enemy = mngr_->addEntity();
	enemy->addComponent<Life>(200);
	enemy->addComponent<Transform>(
		Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 300.0f, 300.0f, 0.0f);
	enemy->addComponent<Image>(&sdlutils().images().at("canelon"));
	enemy->setGroup<Enemy>(true);
	enemy->addComponent<UI>("sardinilla");
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->update();
		mngr_->refresh();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

