#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "EntityAttribs.h"


class UI : public Component {
public:
	UI(std::string n, int pos);
	virtual ~UI() {};

	void init() override;
	void render() override;
	void dep(std::string s);
	void bar(float objetivo);
	void resurrection();

	Vector2D getBarPos() { return renderPosBar; };

	//Getters auxiliares
	inline int getPosUI() { return position; };

private:
	//Texturas de la UI
	Texture* face_;
	Texture* hexagon_;
	Texture* bar_;
	Texture* background_;

	//DestRects
	SDL_Rect dest;	//Face
	SDL_Rect dest2;	//Background
	SDL_Rect dest3;	//Bar
	SDL_Rect dest4;	//Hexagono

	//Posiciones de los destRects
	Vector2D renderPosHead;
	Vector2D renderPosBack;
	Vector2D renderPosBar;
	Vector2D renderPosHexagon;

	//Nombre del personaje que contiene la UI, todo en minusculas
	std::string name;	

	int scale;
	int barLenght;
	int barLenghtInit;
	int position;

	GameStates* state_;
};
