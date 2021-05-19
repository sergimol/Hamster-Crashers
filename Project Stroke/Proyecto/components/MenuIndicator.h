#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "EntityAttribs.h"
#include "GameStates.h"


class MenuIndicator : public Component {
public:
	MenuIndicator(std::string n, Vector2D position, int stateNum);
	virtual ~MenuIndicator() {};

	void render() override;
	void init() override;

	void updateTexture(bool isUp);
	void reset();
	
	// Para el indicador del jugador que está eligiendo
	void moveX(bool isRight);

	void moveToButton(int but);

private:
	//Nombre del indicador
	std::string indicatorName_;
	//Numero del boton en el menu
	int stateNumber_;

	//Texturas del indicador
	Texture* indicator_;

	int indicatorIndex_;

	vector<Texture*> possibleTextures_;
	// Para no hacer .size
	int texturesCount_ = 0;
	GameStates* state_;

	//DestRects
	SDL_Rect dest_;
	//Posiciones de los destRects
	Vector2D renderCoords_;
};
