#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "Life.h"


class UI : public Component {
public:
	UI(std::string n);
	virtual ~UI() {};

	void render() override;
	void dep();
	void bar(float objetivo);
private:
	//Texturas de la UI
	Texture* face_;
	Texture* heart_;
	Texture* bar_;

	//DestRects
	SDL_Rect dest;	//Face
	SDL_Rect dest2;	//Heart
	SDL_Rect dest3;	//Bar
	//Posiciones de los destRects
	Vector2D renderPosHead;
	Vector2D renderPosHeart;
	Vector2D renderPosBar;

	//Nombre del personaje que contiene la UI, todo en minusculas
	std::string name;	

	int scale;
	int barLenght;
	int barLenghtInit;
};
