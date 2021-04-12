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

	void render() override;
	void dep();
	void bar(float objetivo);

	Vector2D getBarPos() { return renderPosBar; };

	//Getters auxiliares
	inline int getPosUI() { return position; };

private:
	//Texturas de la UI
	Texture* face_;
	Texture* bar_;

	//DestRects
	SDL_Rect dest;	//Face
	SDL_Rect dest3;	//Bar

	//Posiciones de los destRects
	Vector2D renderPosHead;
	Vector2D renderPosBar;

	//Nombre del personaje que contiene la UI, todo en minusculas
	std::string name;	

	int scale;
	int barLenght;
	int barLenghtInit;
	int position;
};
