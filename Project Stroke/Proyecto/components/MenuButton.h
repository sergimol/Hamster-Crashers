#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "EntityAttribs.h"
#include "GameStates.h"


class MenuButton : public Component {
public:
	MenuButton(std::string n, Vector2D position, int stateNum);
	virtual ~MenuButton() {};

	void render() override;
	void init() override;

	virtual void selected();
	virtual void exited();

	virtual void pressed() {} = 0;

	//Getters auxiliares
	//inline int getPosUI() { return position; };

protected:
	//Nombre del personaje que contiene la UI, todo en minusculas
	std::string buttonName_;

	//Numero del boton en el menu
	int stateNumber_;

	//Texturas del boton
	Texture* button_;
	Texture* buttonEnter_;
	Texture* buttonPressed_;

	GameStates* state_;

	//DestRects
	SDL_Rect dest_;
	//Posiciones de los destRects
	Vector2D renderCoords_;

	bool buttonSelected_;
};

class LocalButton : public MenuButton {
	LocalButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override;
};

class MultiplayerButton : public MenuButton {
	MultiplayerButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override;
};

class OptionsButton : public MenuButton {
	OptionsButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override;
};

class QuitButton : public MenuButton {
	QuitButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override;
};

class ResumeButton : public MenuButton {
	ResumeButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override ;
};


class HamsterButton : public MenuButton {
	HamsterButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override;
};

class PlayerNumberButton : public MenuButton {
	PlayerNumberButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override;
};

class HamsterSelectButton : public MenuButton {
	HamsterSelectButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override;
};

class MusicLowButton : public MenuButton {
	MusicLowButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override;
};

class MusicUpButton : public MenuButton {
	MusicUpButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override;
};

class FxLowButton : public MenuButton {
	FxLowButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override;
};

class FxUpButton : public MenuButton {
	FxUpButton(std::string n, Vector2D position, int stateNum) :MenuButton(n, position, stateNum) {};
	void pressed() override;
};