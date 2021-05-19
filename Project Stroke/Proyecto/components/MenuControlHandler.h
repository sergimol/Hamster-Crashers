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
	MenuControlHandler(int state) :
		states_(nullptr),
		menu_(nullptr),
		stateNumber_(state)
	{
	}

	virtual ~MenuControlHandler() {}

	void init() override;
	void update() override;

	void setMousePos(const Vector2D& mousePos) { lastMouseX_ = mousePos.getX(); lastMouseY_ = mousePos.getY(); };
	Vector2D getMousePos() { return Vector2D(lastMouseX_, lastMouseY_); };

private:
	//const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	//const enum KEYS2 { UP, DOWN, LEFT, RIGHT, SPACE };
	GameStates* states_;
	MenuButtonManager* menu_;

	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	std::map<KEYS ,SDL_Scancode> keymap;

	bool handleKeyboard();
	bool handleController(int controller);
	bool handleMouse();

	bool mouseInButton(float x, float y, SDL_Rect const& button);


	int stateNumber_, lastMouseX_ = 0, lastMouseY_ = 0;
	//char lastHandled_ = ' ';
};


