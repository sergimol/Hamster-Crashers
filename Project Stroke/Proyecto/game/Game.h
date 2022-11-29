// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <memory>
#include <SDL.h>
#include <vector>
#include "../ecs/Entity.h"

//TILED BIEN
#include "tmxlite/Map.hpp"
#include "tmxlite/Layer.hpp"
#include "tmxlite/TileLayer.hpp"
#include "tmxlite/ObjectGroup.hpp"

// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files

using namespace std;
static bool debug = false;
class Manager;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void update();
	void start();
	//void updateCamera();
	void sortEntities();

private:
	std::unique_ptr<Manager> mngr_;
	SDL_Rect camera_;

	//std::vector<Entity*> players_; // vector de jugadores

	void mergeSort(std::vector<Entity*>& vec, int l, int r);
	void merge(std::vector<Entity*>& vec, int l, int m, int r);
	void changeScene(string newScene);
};

