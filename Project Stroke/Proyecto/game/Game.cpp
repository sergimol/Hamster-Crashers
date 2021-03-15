// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Transform.h"
#include "../components/HamsterStateMachine.h"
#include "../components/Image.h"
#include "../components/Movement.h"
#include "../components/LightAttack.h"
#include "../components/StrongAttack.h"
#include "../components/Stroke.h"
#include "../components/UI.h"
#include "../components/Animator.h"

#include "../ecs/ecs.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"

SDL_Rect Game::camera_ = { 0,0,1920, 1010 };
Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Squeak Ship", 1920, 1010,
		"../../../Proyecto/resources/config/hamsters.resources.json");

	auto* hamster1 = mngr_->addEntity();
	hamster1->addComponent<Transform>(
		Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 128.0f, 128.0f, 0.0f);
	//hamster1->addComponent<Image>(&sdlutils().images().at("sardinilla"));
	hamster1->addComponent<Animator>(
		&sdlutils().images().at("sardinillaSheet"),
		64,
		64,
		3,
		1,
		220,
		Vector2D(0, 0),
		Vector2D(2, 0)
		);
	hamster1->addComponent<HamsterStateMachine>();
	hamster1->addComponent<Movement>();
	hamster1->addComponent<LightAttack>(20);
	hamster1->addComponent<StrongAttack>(30);
	hamster1->addComponent<Stroke>();
	hamster1->addComponent<Life>(100);
	hamster1->addComponent<UI>("sardinilla", 3 );

	players_.push_back(hamster1);

	//Enemigo de prueba
	auto* enemy = mngr_->addEntity();
	enemy->addComponent<Life>(200);
	enemy->addComponent<Transform>(
		Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 300.0f, 300.0f, 0.0f);
	enemy->addComponent<Image>(&sdlutils().images().at("canelon"));
	enemy->setGroup<Enemy>(true);
	enemy->addComponent<UI>("canelon", 4);
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

		updateCamera();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

void Game::updateCamera() {

	Vector2D camPos;

	//Cámara sigue a los personajes
	for (Entity* e : players_) {
		auto& playerpos = e->getComponent<Transform>()->getPos();

		// Operación para calcular el punto medio con más jugadores
		camPos = playerpos;
	}

	camera_.x = camPos.getX() - camera_.w / 2;
	camera_.y = camPos.getY() - camera_.h / 2;

	// Bordes de la cámara
	/*
	if (camera_.x < 0)
		camera_.x = 0;
	if (camera_.y < 0)
		camera_.y = 0;
	if (camera_.x > camera_.w)
		camera_.x = camera_.w;
	if (camera_.h > camera_.h)
		camera_.y = camera_.h;
	*/

	std::cout << camera_.x << " " << camera_.y << "\n";
}

