#pragma once

#include "GameStates.h"


class ReanimationAlone : public Component
{
public:
	ReanimationAlone() : lineH_(nullptr), lineV_(nullptr) {};
	~ReanimationAlone() { deleteTextures(); };


	virtual void init() override;

	virtual void update() override;

	virtual void onEnable() override;

	virtual void onDisable() override;

	void reachedEnd();

	void endPossesion();
private:
	void start();
	void succesfulHit();
	void failedHit();
	void randomiseKey();
	void updateGamePos();
	void deleteTextures();
	void reanimate();

	Entity * keyGame_;
	HamsterStateMachine* hamState_;
	GameStates* gameState_;

	Ability* ab_;

	SDL_Rect lineHPos_, lineVPos_;

	Entity* lineH_, * lineV_;

	//CONSTANTES DE TECLAS, TEXTURAS Y RELACIONADOS
	const int numKeys_ = 4;

	const array<Texture*, 4> keyTextures_{ &sdlutils().images().at("w") ,
										  &sdlutils().images().at("a2"),
										  &sdlutils().images().at("s"),
										  &sdlutils().images().at("d") };

	const array<Texture*, 4> keyDownTextures_{ &sdlutils().images().at("wPressed") ,
										  &sdlutils().images().at("a2Pressed"),
										  &sdlutils().images().at("sPressed"),
										  &sdlutils().images().at("dPressed") };



	const array<SDL_Keycode, 4> keyCodes_{ SDLK_w,
										  SDLK_a,
										  SDLK_s,
										  SDLK_d };

	const array<Texture*, 4> buttonTextures_{ &sdlutils().images().at("a"),
											 &sdlutils().images().at("b"),
											 &sdlutils().images().at("x"),
											 &sdlutils().images().at("y") };

	const array<Texture*, 4> buttonDownTextures_{ &sdlutils().images().at("aPressed"),
											 &sdlutils().images().at("bPressed"),
											 &sdlutils().images().at("xPressed"),
											 &sdlutils().images().at("yPressed") };

	const array<SDL_GameControllerButton, 4> buttonCodes_{ SDL_CONTROLLER_BUTTON_A,
														  SDL_CONTROLLER_BUTTON_B,
														  SDL_CONTROLLER_BUTTON_X,
														  SDL_CONTROLLER_BUTTON_Y };

	SDL_Keycode actualKey_;
	SDL_GameControllerButton actualButton_;
	//CONTROL DEL MINIJUEGO

	bool roundPassed_ = false, failed_ = false;

	const short int hitsToWin_ = 5;

	short int hits_ = 0;

	//CONSTANTES VISUALES 
	float H_LINE_SIZE_X = 400, H_LINE_SIZE_Y = 20, H_LINE_OFFSET_X = -200, H_LINE_OFFSET_Y = -50,
		V_LINE_SIZE_X = 5, V_LINE_SIZE_Y = 70, V_LINE_OFFSET_X = 150, V_LINE_OFFSET_Y = -75,
		BOX_SIZE_X = 50, BOX_SIZE_Y = 50; //BOX_INI_VEL_X = 3;
};
