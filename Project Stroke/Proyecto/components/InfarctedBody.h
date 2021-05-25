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
	InfarctedBody(Entity* h): hamster_(h) {};
	~InfarctedBody() { deleteTexture(); };

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

	void reanimate();
private:
	void disableOtherHamster(Entity* e);
	void enableOtherHamster();
	void deleteTexture();
	//Guarda la entidad del muerto (que ahora es un fantasma) y el que te revive (si hay)
	Entity* hamster_, *otherHamster;
	Ability* ab_;
	Transform* tr_;
	Entity* tx_ = nullptr;
	GameStates* state_;

	//Mantiene el estado del hamster QUE TE ESTÁ REVIVIENDO
	HamStates otherState;
	bool reviving_ = false;

	SDL_Rect cam;

	bool show_;
	bool isCtrl;

	const int KEY_WIDTH = 75;
	const int KEY_HEIGHT = 75;
	//Para poseer
	const SDL_Keycode key = SDLK_p;
	const SDL_GameControllerButton button = SDL_CONTROLLER_BUTTON_B;
};

