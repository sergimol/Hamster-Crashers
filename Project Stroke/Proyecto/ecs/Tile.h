// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../sdlutils/Texture.h"
#include "../ecs/Manager.h"


class Tile {

public:
	Tile(Manager* mn, SDL_Rect source, SDL_Rect dest, Texture* text,bool colide);

};

