#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "EntityAttribs.h"


class MenuButton : public Component {
public:
	MenuButton(std::string n, Vector2D position);
	virtual ~MenuButton() {};

	void render() override;

	void selected();
	void pressed();

	//Getters auxiliares
	//inline int getPosUI() { return position; };

private:
	//Nombre del personaje que contiene la UI, todo en minusculas
	std::string name;
	//Numero del boton en el menu
	int buttonNumber;

	//Texturas del boton
	Texture* button_;
	Texture* buttonEnter_;
	Texture* buttonPressed_;
	Texture* mainText;

	//DestRects
	SDL_Rect dest;
	//Posiciones de los destRects
	Vector2D renderCoords;

	bool buttonSelected;
};
