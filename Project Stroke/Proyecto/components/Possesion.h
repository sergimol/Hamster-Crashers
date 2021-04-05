#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

#include <array>

using namespace std;

class Possesion :public Component {
public:
	Possesion() : possesed(nullptr), line(&sdlutils().images().at("bullet")) {};
	~Possesion() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

	inline void setPossesed(Entity* e) { possesed = e; };

	virtual void onEnable() override;

	virtual void onDisable() override;


private:
	Entity* possesed;
	
	SDL_Rect gamePos;

	const array<Texture*, 5> keys { &sdlutils().images().at("q") , &sdlutils().images().at("bullet"), &sdlutils().images().at("heart1"),  &sdlutils().images().at("heart2"),  &sdlutils().images().at("heart3") };
	const array<SDL_Keycode, 5> keyCodes{ SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_SPACE };

	Texture* line;
	
	int mistakes = 0;

	const float LINE_SIZE_X = 100, LINE_SIZE_Y = 25;

	void start();
};