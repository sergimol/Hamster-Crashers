// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <memory>
#include <SDL.h>
#include <vector>
#include "../ecs/Entity.h"

//TILED BIEN
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>


// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files




class Manager;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
	void updateCamera();
	void sortEntities();
	static SDL_Rect camera_;
private:
	std::unique_ptr<Manager> mngr_;
	//std::vector<Entity*> players_; // vector de jugadores
};

