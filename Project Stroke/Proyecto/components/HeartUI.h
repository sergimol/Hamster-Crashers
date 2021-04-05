#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "EntityAttribs.h"


class HeartUI : public Component {
public:
	HeartUI(std::string n, int pos);
	virtual ~HeartUI() {};
	
	void update() override;
	void render() override;
	void dep();
	void increaseLatency(float aux);

private:
	//Textura del corazon
	Texture* heart_;

	//DestRects
	SDL_Rect dest;	//Heart
	SDL_Rect destAux;	//Para la latencia

	//Posiciones de los destRects
	Vector2D renderPosHeart;
	//Nombre del personaje que contiene la UI, todo en minusculas
	std::string name;	

	bool asciende;
	bool desciende;
	bool alive;
	int scale;
	int position;
	float latency;
	float timeAux;
};
