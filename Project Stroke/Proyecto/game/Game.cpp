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
#include "../components/Roll.h"
#include "../components/Poison.h"
#include "../components/Pray.h"
#include "../components/Combos.h"
#include "../components/Turret.h"
#include "../components/FollowPlayer.h"
#include "../components/MovementSimple.h"
#include "../components/EnemyAttack.h"
#include "../components/EnemyStateMachine.h"
#include "../components/MapMngr.h"
#include "../components/ControlHandler.h"
#include "../components/Item.h"
#include "../components/GetItem.h"
#include "../components/EnemyStun.h"
#include "../components/Stun.h"
#include "../components/Gravity.h"
#include "../components/Knockback.h"
#include "../components/HeartUI.h"
#include "../components/GhostCtrl.h"
#include "../components/PossesionGame.h"
#include "../components/Transition.h"
#include "../components/menuButtonManager.h"
#include "../components/GameStates.h"
#include "../components/EnemyMother.h"

//PARA LAS COLISIONES CON TILE
#include "../utils/Collisions.h"

#include "../ecs/ecs.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../ecs/Camera.h"



Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Squeak Ship", 1920, 1010, "resources/config/hamsters.resources.json");


	//MENU	
	/*auto* mainMenu = mngr_->addEntity();
	/*mainMenu->addComponent<Animator>(
		&sdlutils().images().at("menuSheet"),
		1920,
		1080,
		1,
		1,
		220,
		Vector2D(0, 0),
		3
		);*/
	//mainMenu->addComponent<ControlHandler>(0);
	//mainMenu->addComponent<menuButtonManager>("mainMenu");
	

	
	//Camara
	camera_ = { 0,0,1920, 1080 };
	auto* camera = mngr_->addEntity();
	camera->addComponent<Camera>(camera_);
	mngr_->setHandler<Camera__>(camera);

	// Máquina de estados
	auto* stateMachine = mngr_->addEntity();
	stateMachine->addComponent<GameStates>();
	mngr_->setHandler<StateMachine>(stateMachine);
	
	//EnemyMother
	auto* mother = mngr_->addEntity();
	mother->addComponent<EnemyMother>();
	mngr_->setHandler<Mother>(mother);

	// Mapa
	auto* mapa = mngr_->addEntity();
	mapa->addComponent<MapMngr>();
	mapa->getComponent<MapMngr>()->loadNewMap("resources/images/tiled/Mapa.tmx");

	mngr_->setHandler<Map>(mapa);

	// Transition
	auto* levelMngr = mngr_->addEntity();
	levelMngr->addComponent<Transition>(&sdlutils().images().at("transition"));
	//Metemos al mapa en el Handler de Map

	mngr_->setHandler<Trans>(levelMngr);
	
}

void Game::update() {

}
void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	//Cargamos tiled

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


		//sortEntities();

		//updateCamera();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

//void Game::updateCamera() {
//
//	Vector2D camPos;
//	int players(0);
//	auto& players_ = mngr_->getPlayers();
//
//	//Cámara sigue a los personajes
//	for (Entity* e : players_) {
//		auto& playerpos = e->getComponent<Transform>()->getPos();
//
//		// Operación para calcular el punto medio con más jugadores
//		camPos = camPos + playerpos;
//		players++;
//	}
//
//	camera_.x = (camPos.getX() / players) - camera_.w / 2;
//	camera_.y = (camPos.getY() / players) - camera_.h / 2;
//
//	// Bordes de la cámara
//	/*
//	if (camera_.x < 0)
//		camera_.x = 0;
//	if (camera_.y < 0)
//		camera_.y = 0;
//	if (camera_.x > camera_.w)
//		camera_.x = camera_.w;
//	if (camera_.h > camera_.h)
//		camera_.y = camera_.h;
//	*/
//
//	//std::cout << camera_.x << " " << camera_.y << "\n";
//}
//
//bool myfunction(Entity* a, Entity* b) {
//	std::cout << "MENOR QUE" << std::endl;
//	if (a->hasComponent<Transform>() && b->hasComponent<Transform>())
//		return (a->getComponent<Transform>()->getPos().getY() <= b->getComponent<Transform>()->getPos().getY());
//	return false;
//}



void Game::sortEntities() {

	auto& entities = mngr_->getEntities();
	//Este 2 indica el numero de entidades a las que no afecta el mergeSort
	mergeSort(entities, 2, entities.size() - 1);	//ERES UN PUTO NAZI DANLLES COMENTA EL PUTO CODIGO MAMAWEBO

	/*
		-------------DEBUG-----------
		auto& t = sdlutils().msgs().at("sardinilla");
	auto& t2 = sdlutils().msgs().at("sardinilla2");

	if (entities[1]->hasComponent<EntityAttribs>()) {
		if (entities[1]->getComponent<EntityAttribs>()->getId() == "sardinilla") {
			t.render((sdlutils().width() - t.width()) / 2,
				(sdlutils().height() - t.height()) / 2);
		}
		else {
			t2.render((sdlutils().width() - t.width()) / 2,
				(sdlutils().height() - t.height()) / 2);
		}
	}*/
}

void Game::mergeSort(vector<Entity*>& vec, int l, int r) {
	if (l >= r) {
		return;//returns recursively
	}
	int m = l + (r - l) / 2;
	mergeSort(vec, l, m);
	mergeSort(vec, m + 1, r);
	merge(vec, l, m, r);
}

void Game::merge(vector<Entity*>& vec, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	vector<Entity*> L(n1);
	vector<Entity*> R(n2);

	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = vec[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = vec[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]

	// Initial index of first subarray
	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i]->getComponent<Transform>()->getPos().getY() <= R[j]->getComponent<Transform>()->getPos().getY()) {
			vec[k] = L[i];
			i++;
		}
		else {
			vec[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of
	// L[], if there are any
	while (i < n1) {
		vec[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		vec[k] = R[j];
		j++;
		k++;
	}
}

void Game::changeScene(string newScene) {

}

