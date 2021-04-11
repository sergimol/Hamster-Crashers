#pragma once

#include "InfarctedBody.h"


class ReanimationGame : public Component
{
public:
	ReanimationGame(): txUp_(&sdlutils().images().at("a")), txDown_(&sdlutils().images().at("a2")) {};
	~ReanimationGame() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

	virtual void onDisable() override;
private:
	void endGame();


	Texture* txUp_, * txDown_;
	InfarctedBody* infarct_ = nullptr;

	bool down = false;

	int progress = 0;
	//Referente al minijuego
	const int MAX_PROGRESS = 500,
			  BEAT = 25,
			  DROP = 2,
			  TIME_BETWEEN_DROPS = 30; //ms
	//Visuales del botón
	const int OFFSET_Y = -50,
			  OFFSET_X = 0,
			  WIDTH = 100,
			  HEIGHT = 100;

	unsigned int timer = 0;


	SDL_Rect buttonPos;
	const SDL_Keycode key = SDLK_a;

	

};

