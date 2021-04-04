#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"


class TileRender : public Component {
public:
	TileRender(SDL_Rect source, SDL_Rect dest, Texture* text);
	virtual ~TileRender() {};
	void render()override;
private:
	Texture* text;
	SDL_Rect src;
	SDL_Rect dst;
};
