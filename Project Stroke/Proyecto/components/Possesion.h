#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include <array>

using namespace std;

class Possesion :public Component {
public:
	Possesion() : possesed(nullptr), lineH(&sdlutils().images().at("linea")), lineV(&sdlutils().images().at("lineaV")) {};
	~Possesion() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

	inline void setPossesed(Entity* e) { possesed = e; };

	virtual void onEnable() override;

	virtual void onDisable() override;


private:
	Entity* possesed;
	
	SDL_Rect lineHPos, lineVPos;

	Texture* lineH, * lineV;

	Entity* key;
	
	int misstakes = 0;

	const float LINE_SIZE_X = 400, LINE_SIZE_Y = 20, LINE_OFFSET_X = 0, LINE_OFFSET_Y = 50,
		V_LINE_SIZE_X = 5, V_LINE_SIZE_Y = 70, V_LINE_OFFSET_X = 200, V_LINE_OFFSET_Y = 25,
		BOX_SIZE_X = 50, BOX_SIZE_Y = 50, BOX_INI_VEL_X = 5;

	void start();
};