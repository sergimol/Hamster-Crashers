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

#include "../utils/Collisions.h"

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
	tmx::ObjectGroup* objectLayer;	//Guardamos la capa de entidades para poder leer los enemigos
	int Room;					//Guarda la habitación en la que se encuentran los jugadores
	std::vector<Entity*> roomTrigger;//Guarda todos los triggers de cambio de sala del mapa
public: 
	MapMngr() : Room(0) {};
	~MapMngr();

	void loadNewMap(string map);
	void update()override;
	SDL_Rect cam;
	bool intersectWall(SDL_Rect hamster);
	int scale = 6;
	int filas, columnas;
	int getScale() { return scale; };

	void LoadEnemyRoom();
};

