#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "EntityAttribs.h"


class dialogos : public Component {
public:
	dialogos();
	virtual ~dialogos() {
	};

	void render() override;
	void update() override;
	void init() override;
	void show();
	void unshow();

	void changeShow() { showDialogue = !showDialogue; };
	void changeDialogue();
	void dialogoStateChange();
	void showStrokeTutorial(std::string text);
private:
	//Texturas de dialogos
	Texture* angelText_;
	Texture* barText_;
	Texture* dialogoText_;
	Texture* explicacionText_;

	//Posiciones de los destRects
	Vector2D angelRenderPos;
	Vector2D barRenderPos;
	Vector2D dialogueRenderPos;
	Vector2D explicacionRenderPos;

	//DestRects Inits
	SDL_Rect angelDestI;			//Angel
	SDL_Rect barDestI;			//Bar
	SDL_Rect dialogoDestI;		//Dialogo
	SDL_Rect explicacionDestI;	//Explicacion
	//DestRects relativas
	SDL_Rect angelDest;			//Angel
	SDL_Rect barDest;			//Bar
	SDL_Rect dialogoDest;		//Dialogo
	SDL_Rect explicacionDest;	//Explicacion

	int dialogueNum = 0;
	bool showDialogue = false;
	bool renderDialogues = false;
	bool firstDialogue = true;
	float position = 3.0f;			//Desplaza verticalmente los destrects


	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	std::map<KEYS, SDL_Scancode> keymap;

};
