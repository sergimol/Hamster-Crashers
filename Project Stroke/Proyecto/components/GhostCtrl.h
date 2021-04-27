#pragma once

#include "../ecs/Component.h"
#include "Movement.h"
#include "HamsterStateMachine.h"
#include "GameStates.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"


class GhostCtrl: public Component
{
public:
	GhostCtrl() : tr_(nullptr), mv_(nullptr), tx_(&sdlutils().images().at("q")), state_(nullptr) {
		active_ = false;
	};
	~GhostCtrl() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;



private:
	Transform* tr_;
	HamStates st_;
	Movement* mv_;
	Texture* tx_;
	SDL_Rect cam;
	GameStates* state_;

	const int KEY_WIDHT = 100;
	const int KEY_HEIGHT = 100;
	const SDL_Keycode key = SDLK_q;

	bool show;

	void startPossesion(Entity* e);
};

