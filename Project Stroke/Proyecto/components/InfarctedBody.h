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
	InfarctedBody(Entity* h): hamster(h), tx_(&sdlutils().images().at("r")) {};
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
	GameStates* state_;

	//Mantiene el estado del hamster QUE TE ESTÁ REVIVIENDO
	HamStates otherState;
	bool reviving = false;

	SDL_Rect cam;

	bool show;

	const int KEY_WIDHT = 100;
	const int KEY_HEIGHT = 100;
	const SDL_Keycode key = SDLK_r;
};

