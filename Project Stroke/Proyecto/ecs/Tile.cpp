// This file is part of the course TPV2@UCM - Samir Genaim

#include "Entity.h"
#include "Tile.h"
#include "../components/Transform.h"
#include "../components/TileRender.h"


Tile::Tile(Manager* mn, SDL_Rect src, SDL_Rect dst, Texture* text, bool colide) {
	auto tile = mn->addTile();
	if (colide) {

		//Añado un componente o lo que coño sea para que colisione
		tile->addComponent<Transform>(Vector2D(dst.x, dst.y), Vector2D(0, 0), dst.w, dst.h, 0);

		tile->addComponent<TileRender>(src, dst, text);

	}
	else
		tile->addComponent<TileRender>(src, dst, text);
}
