#pragma once

#include "../ecs/Component.h"
#include <map>
#include "../sdlutils/SDLUtils.h"
#include "EntityAttribs.h"

//las cosas que controla
#include "Movement.h"
#include "Roll.h"
#include "LightAttack.h"
#include "StrongAttack.h"


/*Esta clase es la encargada de filtar los inputs
para cada una de las entidades y mandarles la orden
¡de lo que sea que signifiquen,
de esta forma tmb se permitira mas adelante el mapeado de estas acciones*/
class ControlHandler : public Component {
public:
	ControlHandler(int player) :
		mov_(nullptr),
		roll_(nullptr),
		lt_(nullptr),
		st_(nullptr),
		player_(player), // player es solo para decir que teclas le corresponde
		hasController_(false) // true = el jugador tiene mando, false = no tiene 
	{
	}

		virtual ~ControlHandler() {}

	void init() override;
	void update() override;

	virtual void onDisable() override;

	// Actualiza el booleano del mando, por si se conecta o desconecta
	void setController(bool hasController);

private:
	//const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	//const enum KEYS2 { UP, DOWN, LEFT, RIGHT, SPACE };
	int player_;
	Movement* mov_;
	Roll* roll_;
	LightAttack* lt_;
	StrongAttack* st_;
	bool hasController_;

	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	std::map<KEYS ,SDL_Scancode> keymap;
	//std::map<KEYS, bool> keymap; //lo voy a necesitar de verdad?

	void handleKeyboard();
	void handleController();
};


