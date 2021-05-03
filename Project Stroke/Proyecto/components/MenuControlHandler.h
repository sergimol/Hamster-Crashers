#pragma once

#include "../ecs/Component.h"
#include <map>
#include "../sdlutils/SDLUtils.h"
#include "EntityAttribs.h"

//las cosas que controla
#include "GameStates.h"
#include "MenuButtonManager.h"


/*Esta clase es la encargada de filtar los inputs
para cada una de las entidades y mandarles la orden
¡de lo que sea que signifiquen,
de esta forma tmb se permitira mas adelante el mapeado de estas acciones*/
class MenuControlHandler : public Component {
public:
	MenuControlHandler() :
		states_(nullptr),
		menu_(nullptr)
	{
	}

	virtual ~MenuControlHandler() {}

	void init() override;
	void update() override;

private:
	//const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	//const enum KEYS2 { UP, DOWN, LEFT, RIGHT, SPACE };
	GameStates* states_;
	MenuButtonManager* menu_;

	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	std::map<KEYS ,SDL_Scancode> keymap;

	void handleKeyboard();
	void handleController(int controller);
};


