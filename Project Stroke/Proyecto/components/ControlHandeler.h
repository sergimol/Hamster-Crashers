#pragma once

#include "../ecs/Component.h"
#include <map>
#include "../sdlutils/SDLUtils.h"
#include "EntityAttribs.h"

//las cosas que controla
#include "Movement.h"
#include "Roll.h"


/*Esta clase es la encargada de filtar los inputs
para cada una de las entidades y mandarles la orden
¡de lo que sea que signifiquen,
de esta forma tmb se permitira mas adelante el mapeado de estas acciones*/
class ControlHandeler : public Component {
public:
	ControlHandeler(int player) :
		player_(player) // player es solo para decir que teclas le corresponde
	{
	}

		virtual ~ControlHandeler() {}

	void init() override;
	void update() override;

private:
	//const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	//const enum KEYS2 { UP, DOWN, LEFT, RIGHT, SPACE };
	int player_;
	Movement* mov_;
	Roll* roll_;

	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	std::map<KEYS ,SDL_Scancode> keymap;
	//std::map<KEYS, bool> keymap; //lo voy a necesitar de verdad?
};


