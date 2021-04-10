#pragma once

#include "../ecs/Component.h"
#include <string>
#include <tmxlite\Types.hpp>
#include "../sdlutils/Texture.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "../game/Game.h"
#include "../ecs/Manager.h"
#include "../ecs/tile.h"



using namespace std;
class Game;

const int TAM_CELDA = 16;

class MapMngr : public Component
{
private:
	tmx::Vector2u mapDimensions_;	//Guarda las dimensiones del mapa
	tmx::Vector2u tilesDimensions_;	//Guarda las dimensiones de las tiles
	Texture* tilesetsArr[1];
	tmx::Map map_;

	//Matriz de colisiones
	bool** collider;

	Vector2D mapCoorsToSDLPoint(Vector2D coords);
	Vector2D SDLPointToMapCoords(Vector2D p);
public: 
	MapMngr() {};
	~MapMngr();

	void loadNewMap(string map);

	SDL_Rect cam;
	bool intersectWall(SDL_Rect hamster,int z);
	int scale = 6;
	int filas, columnas;

};

