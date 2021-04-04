// This file is part of the course TPV2@UCM - Samir Genaim

#include "Entity.h"
#include "tile.h"

#include "../components/tileRender.h"


tile::tile(Manager* mn, SDL_Rect src, SDL_Rect dst, Texture* text) {
	auto tile = mn->addTile();
	tile->addComponent<tileRender>(src, dst,text);
}
