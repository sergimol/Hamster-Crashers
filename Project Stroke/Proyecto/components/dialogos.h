#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "EntityAttribs.h"
#include "Animator.h"


class dialogos : public Component {
public:
	dialogos();
	virtual ~dialogos() {
	};

	void render() override;
	void update() override;
	void show();
	void unshow();

	void changeShow() { showDialogue_ = !showDialogue_; };
	void changeDialogue();
	void dialogoStateChange();
	void showStrokeTutorial(std::string text);
private:
	//Texturas de dialogos
	Texture* angelText_;
	Texture* barText_;
	Texture* dialogoText_;
	Texture* explicacionText_;

	int altTime_;
	int altCD_;

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

	int dialogueNum_ = 0;
	bool showDialogue_ = false;
	bool isAlt_ = false;
	bool renderDialogues = false;
	bool firstDialogue_ = true;
	float position = 3.0f;			//Desplaza verticalmente los destrects

};
