#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Ability.h"
#include "GameStates.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/HamsterStateMachine.h"


#include <string>

using namespace std;

class InfarctedBody: public Component
{
public:
	InfarctedBody(Entity* h): hamster(h), tx_(&sdlutils().images().at("r")), ctrlTx_(&sdlutils().images().at("b")) {};
	~InfarctedBody() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

	void reanimate();
private:
	void disableOtherHamster(Entity* e);
	void enableOtherHamster();
	//Guarda la entidad del muerto (que ahora es un fantasma) y el que te revive (si hay)
	Entity* hamster, *otherHamster;
	Ability* ab_;
	Transform* tr_;
	Texture* tx_;
	Texture* ctrlTx_;
	GameStates* state_;

	//Mantiene el estado del hamster QUE TE ESTÁ REVIVIENDO
	HamStates otherState;
	bool reviving = false;

	SDL_Rect cam;

	bool show;
	bool isCtrl;

	const int KEY_WIDTH = 100;
	const int KEY_HEIGHT = 100;
	//Para poseer
	const SDL_Keycode key = SDLK_p;
	const SDL_GameControllerButton button = SDL_CONTROLLER_BUTTON_B;
};

