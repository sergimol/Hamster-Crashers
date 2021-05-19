#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/HamsterStateMachine.h"
#include <array>

using namespace std;

class PossesionGame :public Component {
public:
	PossesionGame() : possesed(nullptr), lineH(&sdlutils().images().at("linea")), lineV(&sdlutils().images().at("lineaV")) {};
	~PossesionGame() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

	inline void setPossesed(Entity* e) { possesed = e; };

	virtual void onEnable() override;

	virtual void onDisable() override;

	void reachedEnd();

	void endPossesion();

private:
	void start();
	void succesfulHit();
	void failedHit();
	void randomiseKey();

	Entity* possesed, * keyGame;
	HamsterStateMachine* possesedState;
	GameStates* state_;

	SDL_Rect lineHPos, lineVPos;

	Texture* lineH, * lineV;

	//CONSTANTES DE TECLAS, TEXTURAS Y RELACIONADOS
	const int numKeys = 4;

	const array<Texture*, 4> keyTextures{ &sdlutils().images().at("w") , &sdlutils().images().at("a2"), &sdlutils().images().at("s"),  &sdlutils().images().at("d")};
	const array<SDL_Keycode, 4> keyCodes{ SDLK_w, SDLK_a, SDLK_s, SDLK_d };
	const array<Texture*, 4> buttonTextures{ &sdlutils().images().at("a"), &sdlutils().images().at("b"), &sdlutils().images().at("x"), &sdlutils().images().at("y") };
	const array<SDL_GameControllerButton, 4> buttonCodes{ SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B, SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y };

	SDL_Keycode actualKey;
	SDL_GameControllerButton actualButton;

	// Para obtener el estado de los botones del mando que corresponde
	int playerNumber_;
	
	//CONTROL DEL MINIJUEGO

	bool roundPassed = false, failed = false;
	
	const short int maxMistakes = 3;

	short int mistakes = 0;

	//CONSTANTES VISUALES 
	const float H_LINE_SIZE_X = 400, H_LINE_SIZE_Y = 20, H_LINE_OFFSET_X = 0, H_LINE_OFFSET_Y = 50,
				V_LINE_SIZE_X = 5, V_LINE_SIZE_Y = 70, V_LINE_OFFSET_X = 200, V_LINE_OFFSET_Y = 25,
				BOX_SIZE_X = 50, BOX_SIZE_Y = 50, BOX_INI_VEL_X = 3;
};