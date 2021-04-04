// This file is part of the course TPV2@UCM - Samir Genaim

#include "Entity.h"
#include "Tile.h"

#include "../components/TileRender.h"


Tile::Tile(Manager* mn, SDL_Rect src, SDL_Rect dst, Texture* text) {
	auto tile = mn->addTile();
	tile->addComponent<TileRender>(src, dst,text);
}
