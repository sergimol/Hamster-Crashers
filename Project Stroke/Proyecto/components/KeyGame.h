#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"

using namespace std;

class KeyGame :public Component {
	KeyGame(float vel, SDL_Keycode key, SDL_Rect rect, int& misstakes): vel_(vel), key_(key), rect_(rect), misstakes_(misstakes) {};
	~KeyGame() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

private:
	Transform* tr_;
	Texture* tx_;

	float vel_;

	SDL_Keycode key_;
	SDL_Rect rect_;
	SDL_Rect rect_end;
	int misstakes_;

	void missedSkillCheck();
	void hitSkillCheck();
};