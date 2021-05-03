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

	MenuButtonManager(string menu, int state);

	virtual ~MenuButtonManager() {};

	void init() override;
	void update() override;
	void updateKeymap(KEYS x, bool is);

private:
	string menuMode_;
	//Numero del estado en el que se muestra el menú
	int stateNumber_;

	//Controla el boton activo dentro de la rejilla
	Vector2D buttonsPosition_;
	Vector2D buttonsMagnitude_;
	vector<vector<Entity*>> buttons_;

	GameStates* state_;
	long unsigned int timer_, cooldown_; //Contador para movimiento entre botones

	//Input
	std::map<KEYS, bool> keymap;
	Entity* background_;
};
