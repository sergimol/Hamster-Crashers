#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"


class GameStates : public Component {
public:
	enum States
	{
		MAINMENU,
		HAMSTERSELECTION,
		PAUSE,
		RUNNING,
		CREDITS,
		CONTROLS,
		PLAYERSELECTION
	};

	GameStates(): state_() {};
	virtual ~GameStates() {};

	void init() override;
	void setState(States state);
	States getState();

private:
	States state_;
};
