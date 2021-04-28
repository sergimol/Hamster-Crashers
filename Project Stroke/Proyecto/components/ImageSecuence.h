#pragma once
// This file is part of the course TPV2@UCM - Alberto Muñoz

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include <stack>
#include <string>

using namespace std;

class ImageSecuence : public Component {
public:
	ImageSecuence(string newScene);
	
	virtual ~ImageSecuence() {}

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

private:
	stack<Texture*> keyTextures;

	const string level1 = "Mapa.tmx",
		level2 = "Mapa2.tmx",
		controls = "controls",
		hasMuerto = "hasMuerto",
		hasGanado = "hasGanado";

	string newScene_;

	bool next = false;

	bool controles = false;

	bool gameOver = false;

	SDL_Rect imageRect;

	Transition* trans_;
};