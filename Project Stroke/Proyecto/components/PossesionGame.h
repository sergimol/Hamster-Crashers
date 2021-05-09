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

	const array<Texture*, 4> keyTextures{ &sdlutils().images().at("q") , &sdlutils().images().at("bullet"), &sdlutils().images().at("heart1"),  &sdlutils().images().at("heart2")};
	const array<SDL_Keycode, 4> keyCodes{ SDLK_a, SDLK_a, SDLK_a, SDLK_a };

	SDL_Keycode actualKey;
	
	//CONTROL DEL MINIJUEGO

	bool roundPassed = false, failed = false;
	
	const short int maxMistakes = 3;

	short int mistakes = 0;

	//CONSTANTES VISUALES 
	const float LINE_SIZE_X = 400, LINE_SIZE_Y = 20, LINE_OFFSET_X = 0, LINE_OFFSET_Y = 50,
				V_LINE_SIZE_X = 5, V_LINE_SIZE_Y = 70, V_LINE_OFFSET_X = 200, V_LINE_OFFSET_Y = 25,
				BOX_SIZE_X = 50, BOX_SIZE_Y = 50, BOX_INI_VEL_X = 3;
};