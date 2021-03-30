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
#include "../components/ControlHandeler.h"

#include "../ecs/ecs.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"

SDL_Rect Game::camera_ = { 0,0,1920, 1080 };

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Squeak Ship", 1920, 1080, "resources/config/hamsters.resources.json");

	auto& players = mngr_->getPlayers();
	auto& enemies = mngr_->getEnemies();
	auto& obstacles = mngr_->getObstacles();

	// Mapa
	auto* mapa = mngr_->addEntity();
	mapa->addComponent<MapMngr>();

	//Imagen de fondo fija
	/*auto* background = mngr_->addEntity();
	background->addComponent<Transform>(
		Vector2D(0, 0),
		Vector2D(), 1920.0f, 1010.0f, 0.0f);

	background->addComponent<Image>(&sdlutils().images().at("background"));*/


	////MATERIAL PARA EL HITO1
	////Keta
	//auto* hamster2 = mngr_->addEntity();
	//hamster2->addComponent<Transform>(
	//	Vector2D(sdlutils().width() / 2.0f - 500, sdlutils().height() / 2.0f + 200),
	//	Vector2D(), 256.0f, 256.0f, 0.0f);
	//hamster2->addComponent<Image>(&sdlutils().images().at("keta"));
	//hamster2->addComponent<HamsterStateMachine>();
	//hamster2->addComponent<LightAttack>(20);
	//hamster2->addComponent<StrongAttack>(30);
	//hamster2->addComponent<Stroke>();
	//hamster2->addComponent<Life>(100);
	//hamster2->addComponent<UI>("keta", 1);

	//players_.push_back(hamster2);

	//auto* hamster3 = mngr_->addEntity();
	//hamster3->addComponent<Transform>(
	//	Vector2D(sdlutils().width() / 2.0f -800, sdlutils().height() / 2.0f + -50),
	//	Vector2D(), 256.0f, 256.0f, 0.0f);
	//hamster3->addComponent<Image>(&sdlutils().images().at("monchi"));
	//hamster3->addComponent<HamsterStateMachine>();
	//hamster3->addComponent<LightAttack>(20);
	//hamster3->addComponent<StrongAttack>(30);
	//hamster3->addComponent<Stroke>();
	//hamster3->addComponent<Life>(100);
	//hamster3->addComponent<UI>("monchi", 2);

	//players_.push_back(hamster3);

	////MATERIAL PARA EL HITO1//

	//Sardinilla
	auto* hamster1 = mngr_->addEntity();
	hamster1->addComponent<Transform>(
		Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 256.0f, 256.0f, 0.0f);
	hamster1->addComponent<EntityAttribs>(100, 0.0, "sardinilla", Vector2D(7, 4.5));
	//hamster1->addComponent<Image>(&sdlutils().images().at("sardinilla"));
	hamster1->addComponent<Animator>(
		&sdlutils().images().at("sardinillaSheet"),
		64,
		64,
		3,
		3,
		220,
		Vector2D(0, 0),
		3
		);

	hamster1->addComponent<HamsterStateMachine>();
	hamster1->addComponent<Movement>();
	hamster1->addComponent<LightAttack>();
	hamster1->addComponent<StrongAttack>();
	hamster1->addComponent<Stroke>();
	hamster1->addComponent<UI>("sardinilla", 0);
	//hamster1->addComponent<Pray>(30, 50);
	//hamster1->addComponent<Roll>();
	//hamster1->addComponent<Turret>();
	hamster1->addComponent<Poison>(5);
	hamster1->addComponent<Combos>();
	hamster1->setGroup<Ally>(true);
	hamster1->addComponent<ControlHandeler>(1);

	players.push_back(hamster1);

	//Igual luego no lo usammos pero por si aca
	mngr_->setHandler<Hamster1>(hamster1);


	//CLON Sardinilla (P2)
	auto* hamster2 = mngr_->addEntity();
	hamster2->addComponent<Transform>(
		Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 256.0f, 256.0f, 0.0f);
	hamster2->addComponent<EntityAttribs>(100, 0.0, "sardinilla2", Vector2D(7, 4.5));
	//hamster1->addComponent<Image>(&sdlutils().images().at("sardinilla"));
	hamster2->addComponent<Animator>(
		&sdlutils().images().at("sardinillaSheet"),
		64,
		64,
		3,
		3,
		220,
		Vector2D(0, 0),
		3
		);
	hamster2->addComponent<HamsterStateMachine>();
	hamster2->addComponent<Movement>();
	hamster2->addComponent<LightAttack>();
	hamster2->addComponent<StrongAttack>();
	hamster2->addComponent<Stroke>();
	hamster2->addComponent<UI>("sardinilla", 1);
	//hamster1->addComponent<Pray>(30, 50);
	hamster2->addComponent<Roll>();
	//hamster1->addComponent<Turret>();
	hamster2->addComponent<Combos>();
	hamster2->setGroup<Ally>(true);
	hamster2->addComponent<ControlHandeler>(2);
	players.push_back(hamster2);


	//Enemigo de prueba con la imagen de canelón
	/*auto* enemy = mngr_->addEntity();
	enemy->addComponent<EntityAttribs>(200, 0.0, "enemy", Vector2D(4.5, 2));
	enemy->addComponent<Transform>(
		Vector2D(sdlutils().width() / 2.0f + 400, sdlutils().height() / 2.0f - 100),
		Vector2D(), 500.0f, 500.0f, 0.0f)->getFlip() = true;
	enemy->addComponent<Image>(&sdlutils().images().at("canelon"));
	enemy->setGroup<Enemy>(true);
	enemy->addComponent<UI>("canelon", 4);


	enemy->addComponent<EnemyStateMachine>();
	enemy->addComponent<EnemyAttack>();
	enemy->addComponent<MovementSimple>();
	enemy->addComponent<FollowPlayer>();*/
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
		sortEntities();

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
	int players(0);
	auto& players_ = mngr_->getPlayers();

	//Cámara sigue a los personajes
	for (Entity* e : players_) {
		auto& playerpos = e->getComponent<Transform>()->getPos();

		// Operación para calcular el punto medio con más jugadores
		camPos = camPos + playerpos;
		players++;
	}

	camera_.x = (camPos.getX() / players) - camera_.w / 2;
	camera_.y = (camPos.getY() / players) - camera_.h / 2;

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

	//std::cout << camera_.x << " " << camera_.y << "\n";
}
//
//bool myfunction(Entity* a, Entity* b) {
//	std::cout << "MENOR QUE" << std::endl;
//	if (a->hasComponent<Transform>() && b->hasComponent<Transform>())
//		return (a->getComponent<Transform>()->getPos().getY() <= b->getComponent<Transform>()->getPos().getY());
//	return false;
//}



void Game::sortEntities() {
	
	auto& entities = mngr_->getEntities();
	
	mergeSort(entities, 1, entities.size()-1);
	
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

