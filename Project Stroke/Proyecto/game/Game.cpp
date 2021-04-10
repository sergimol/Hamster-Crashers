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
#include "../components/Possesion.h"

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

	//Camara
	camera_ = { 0,0,1920, 1080 };
	auto* camera = mngr_->addEntity();
	camera->addComponent<Camera>(camera_);
	mngr_->setHandler<Camera__>(camera);
	// Mapa
	auto* mapa = mngr_->addEntity();
	mapa->addComponent<MapMngr>();
	mapa->getComponent<MapMngr>()->loadNewMap("resources/images/tiled/Mapa.tmx");

	//Metemos al mapa en el Handler de Map
	mngr_->setHandler<Map>(mapa);

	//Imagen de fondo fija
	/*auto* background = mngr_->addEntity();
	background->addComponent<Transform>(
		Vector2D(0, 0),
		Vector2D(), 1920.0f, 1010.0f, 0.0f);

	background->addComponent<Image>(&sdlutils().images().at("background"));*/

	/*
	* SI VAIS A TESTEAR CON MENOS HÁMSTERS, NO QUITEIS EL CÓDIGO, COMENTADLO
	*/


	//auto& players = mngr_->getPlayers();

	////Sardinilla (P1)
	//auto* hamster2 = mngr_->addEntity();
	//hamster2->addComponent<Transform>(
	//	Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
	//	Vector2D(), 256.0f, 256.0f, 0.0f);
	//hamster2->addComponent<EntityAttribs>(100, 0.0, "sardinilla2", Vector2D(7, 4.5));
	////hamster1->addComponent<Image>(&sdlutils().images().at("sardinilla"));
	//hamster2->addComponent<Animator>(
	//	&sdlutils().images().at("sardinillaSheet"),
	//	64,
	//	64,
	//	3,
	//	3,
	//	220,
	//	Vector2D(0, 0),
	//	3
	//	);
	//hamster2->addComponent<HamsterStateMachine>();

	//hamster2->addComponent<Movement>();
	//hamster2->addComponent<LightAttack>();
	//hamster2->addComponent<StrongAttack>();
	//hamster2->addComponent<UI>("sardinilla", 1);
	////hamster2->addComponent<HeartUI>("sardinilla", 1);
	////hamster1->addComponent<Pray>(30, 50);
	////hamster1->addComponent<Turret>();
	//hamster2->addComponent<Roll>();
	//hamster2->addComponent<Possesion>();
	//hamster2->addComponent<GhostCtrl>();
	//hamster2->addComponent<Stroke>();
	//hamster2->addComponent<Combos>();
	//hamster2->setGroup<Ally>(true);
	//hamster2->addComponent<ControlHandler>(2);
	//hamster2->addComponent<Stun>();
	//hamster2->addComponent<Knockback>();
	//hamster2->addComponent<GetItem>();
	//hamster2->addComponent<Gravity>();
	//players.push_back(hamster2);

	/*
	* SI VAIS A TESTEAR CON MENOS HÁMSTERS, NO QUITEIS EL CÓDIGO, COMENTADLO
	*/

	//Sardinilla (P2)
	//auto* hamster1 = mngr_->addEntity();
	//hamster1->addComponent<Transform>(
	//	Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
	//	Vector2D(), 256.0f, 256.0f, 0.0f);
	//hamster1->addComponent<EntityAttribs>(100, 0.0, "sardinilla2", Vector2D(7, 4.5));
	////hamster1->addComponent<Image>(&sdlutils().images().at("sardinilla"));
	//hamster1->addComponent<Animator>(
	//	&sdlutils().images().at("sardinillaSheet"),
	//	64,
	//	64,
	//	3,
	//	3,
	//	220,
	//	Vector2D(0, 0),
	//	3
	//	);
	//hamster1->addComponent<HamsterStateMachine>();

	//hamster1->addComponent<Movement>();
	//hamster1->addComponent<LightAttack>();
	//hamster1->addComponent<StrongAttack>();
	//hamster1->addComponent<UI>("sardinilla", 2);
	////hamster2->addComponent<HeartUI>("sardinilla", 1);
	////hamster1->addComponent<Pray>(30, 50);
	////hamster1->addComponent<Turret>();
	//hamster1->addComponent<Roll>();
	//hamster1->addComponent<Possesion>();
	//hamster1->addComponent<GhostCtrl>();
	//hamster1->addComponent<Stroke>();
	//hamster1->addComponent<Combos>();
	//hamster1->setGroup<Ally>(true);
	//hamster1->addComponent<ControlHandler>(2);
	//hamster1->addComponent<Stun>();
	//hamster1->addComponent<Knockback>();
	//hamster1->addComponent<GetItem>();
	//hamster1->addComponent<Gravity>();
	//players.push_back(hamster1);
}

void Game::update() {
	//TODO HACER ESTO SIN IMPORTAR EL NUM DE HAMSTERS QUE HAYA	
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

		//Cutreria

		//Cogemos la entidad del primer hamster
		auto hamster1 = mngr_->getHandler<Hamster1>();

		auto hamsterTr = hamster1->getComponent<Transform>();

		Vector2D playerPos = hamster1->getComponent<Transform>()->getPos();

		mngr_->update();
		mngr_->refresh();

		//Cogemos todos los tiles
		auto hamsters = mngr_->getPlayers();
		for (Entity* hamster : hamsters) {

			//Cojo el transform de la colision
			auto auxTr = hamster->getComponent<Transform>();

			//Cogemos el mapa
			auto map = mngr_->getHandler<Map>();

			SDL_Rect playerRect;
			playerRect.x = auxTr->getPos().getX();
			playerRect.y = auxTr->getPos().getY();
			playerRect.w = auxTr->getW();
			playerRect.h = auxTr->getH();;

			//Si choca con la colision más cercana
			if (map->getComponent<MapMngr>()->intersectWall(playerRect, auxTr->getZ())) {
				//Vuelves a tu posicion de inicio
				hamster1->getComponent<Transform>()->setPos(playerPos);
			}
		}

		sortEntities();

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

