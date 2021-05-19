#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "EntityAttribs.h"
const float MAXLATENCY = 700;

class HeartUI : public Component {
public:
	HeartUI(std::string n, int pos);
	virtual ~HeartUI() {};

	void init() override;
	void update() override;
	void render() override;
	void dep();
	void resurrection();
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

	bool alive;
	float scale;
	int position;
	float latency;
	float latencyAux;

	GameStates* state_;
};
