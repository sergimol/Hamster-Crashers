#pragma once

#include "../ecs/Component.h"
#include <string>
#include <tmxlite\Types.hpp>
#include "../sdlutils/Texture.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

using namespace std;

class MapMngr : public Component
{
private:
	tmx::Vector2u mapDimensions_;	//Guarda las dimensiones del mapa
	tmx::Vector2u tilesDimensions_;	//Guarda las dimensiones de las tiles
	Texture* tilesetsArr[2];
	tmx::Map map_;
public: 
	MapMngr() {};
	~MapMngr() {};
	virtual void init() override;
	virtual void render() override;
	void loadNewMap(string map);
};

