#pragma once

#include "InfarctedBody.h"
#include "GameStates.h"


class ReanimationGame : public Component
{
public:
	ReanimationGame(): txUp_(nullptr), txDown_(nullptr), state_(nullptr) {};
	~ReanimationGame();

	void init() override;

	void update() override;

	void render() override;

	void onDisable() override;

	void onResume() override;

	void setRevPlayer(Entity* e);
private:
	void endGame();

	void handleKey();
	void handleButton();

	void deleteTextures();

	Entity* txUp_, * txDown_;
	InfarctedBody* infarct_ = nullptr;

	SoundEffect* fx_;

	Transform* revTrans_ = nullptr;

	bool down = false;
	// Referencia al numero del jugador que le está reviviendo
	int revPlNumber_;
	bool useController_;

	int progress = 0;
	//Referente al minijuego
	const int MAX_PROGRESS = 250,
			  BEAT = 25,
			  DROP = 2,
			  TIME_BETWEEN_DROPS = 30; //ms
	//Visuales del botón
	const int OFFSET_Y = 20,
			  OFFSET_X = 0,
			  WIDTH = 100,
			  HEIGHT = 100;

	unsigned int timer = 0;


	SDL_Rect buttonPos;
	const SDL_Keycode key = SDLK_a;
	const SDL_GameControllerButton button = SDL_CONTROLLER_BUTTON_A;

	GameStates* state_;

};

