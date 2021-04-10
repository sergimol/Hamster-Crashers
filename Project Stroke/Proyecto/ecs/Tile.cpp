// This file is part of the course TPV2@UCM - Samir Genaim

#include "Entity.h"
#include "Tile.h"
#include "../components/Transform.h"
#include "../components/TileRender.h"


Tile::Tile(Manager* mn, SDL_Rect src, SDL_Rect dst, Texture* text, bool colide) {
	if (colide) {
		auto tileCd = mn->addTileCollider();

		//Añado un componente o lo que coño sea para que colisione
		tileCd->addComponent<Transform>(Vector2D(dst.x, dst.y), Vector2D(0, 0), dst.w, dst.h, 0);
	}
	else {
		auto tile = mn->addTile();
		tile->addComponent<TileRender>(src, dst, text);
	}
}
