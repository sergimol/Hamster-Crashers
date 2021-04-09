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

class MapMngr : public Component
{
private:
	tmx::Vector2u mapDimensions_;	//Guarda las dimensiones del mapa
	tmx::Vector2u tilesDimensions_;	//Guarda las dimensiones de las tiles
	Texture* tilesetsArr[2];
	tmx::Map map_;

	bool** collider;

	Vector2D mapCoorsToSDLPoint(Vector2D coords);
	Vector2D SDLPointToMapCoords(Vector2D p);
public: 
	MapMngr();
	~MapMngr();

	virtual void init() override;
	virtual void update() override;
	void loadNewMap(string map);

	void intersectWall();

	int scale = 6;
	int filas, columnas;

};

