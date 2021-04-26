#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "MenuButton.h"

class MenuButtonManager: public Component{
public:
	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	MenuButtonManager(string menu);
	virtual ~MenuButtonManager() {};

	void init() override;
	void update() override;

	void updateKeymap(KEYS x, bool is);

private:
	string MenuMode;
	//Numero del boton en el menu
	int buttonNumber;

	//Controla el boton activo dentro de la rejilla
	Vector2D buttonsPosition;
	Vector2D buttonsMagnitude;
	vector<Entity*> buttons;


	//Input
	std::map<KEYS, bool> keymap;
};
