#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

using namespace std;

class KeyGame : public Component {
public:
	KeyGame(SDL_Rect rect, SDL_Rect line, int& m): checkRect(rect), endLine(line), misstakes(m) {};
	~KeyGame() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

	void hitSkillCheck();

private:
	Transform* tr_;
	Texture* tx_;

	const array<Texture*, 5> keys{ &sdlutils().images().at("q") , &sdlutils().images().at("bullet"), &sdlutils().images().at("heart1"),  &sdlutils().images().at("heart2"),  &sdlutils().images().at("heart3") };
	const array<SDL_Keycode, 5> keyCodes{ SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_SPACE };

	SDL_Keycode key_;
	SDL_Rect checkRect;
	SDL_Rect endLine;
	
	bool hit;
	int misstakes;

	Vector2D iniPos;

	void setKey();
	void missedSkillCheck();
};