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
	
	void init() override;
	void update() override;
	void render() override;
	void dep();
	void increaseLatency(float aux);

private:
	//Texturas de la UI
	Texture* heart_;

	//DestRects
	SDL_Rect dest2;	//Heart

	//Posiciones de los destRects
	Vector2D renderPosHeart;

	Animator* anim_;

	//Nombre del personaje que contiene la UI, todo en minusculas
	std::string name;	

	int scale;
	int position;
	float latency;
	float timeAux;
};
