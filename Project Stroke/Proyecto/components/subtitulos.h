#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "EntityAttribs.h"

#include <string>

//ESTA CLASE ES LA DE LAS TRANSICIONES QUE SALE ANGEL HABLANDO

class Subtitulos : public Component {
public:
	Subtitulos(std::string actualSub, int transitionNum);
	virtual ~Subtitulos() {};

	void render() override;
	void update() override;
	void show();
	void unshow();

	void changeShow() { showDialogue = !showDialogue; };
	void changeDialogue();
	void dialogoStateChange();
private:
	//Texturas de dialogos
	Texture* barText_;
	Texture* dialogoText_;

	//Posiciones de los destRects
	Vector2D barRenderPos;
	Vector2D dialogueRenderPos;

	//DestRects Inits
	SDL_Rect barDestI;			//Bar
	SDL_Rect dialogoDestI;		//Dialogo
	//DestRects relativas
	SDL_Rect barDest;			//Bar
	SDL_Rect dialogoDest;		//Dialogo

	int dialogueNum = 0;
	bool showDialogue = false;
	bool renderDialogues = false;
	bool firstDialogue = true;
	float position = 3.0f;			//Desplaza verticalmente los destrects

	std::string actualSub_;
	int transitionNum_;

};
