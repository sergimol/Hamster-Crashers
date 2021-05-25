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
	GhostCtrl() : tr_(nullptr), mv_(nullptr), state_(nullptr), keyTx_(nullptr) {
		active_ = false;
	};
	~GhostCtrl() { deleteKey(); };

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

	virtual void onDisable() override;

private:
	void generateKey();
	void updateKey();
	void deleteKey();

	Transform* tr_;
	HamStates st_;
	Movement* mv_;

	Entity* keyTx_;

	SDL_Rect cam;

	GameStates* state_;

	const int KEY_WIDTH = 100;
	const int KEY_HEIGHT = 100;

	const SDL_Keycode key_ = SDLK_q;
	const SDL_GameControllerButton button_ = SDL_CONTROLLER_BUTTON_B;

	bool show_;
	bool isController_;

	void startPossesion(Entity* e);
};

