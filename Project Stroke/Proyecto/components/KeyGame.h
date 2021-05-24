#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "PossesionGame.h"
#include "GameStates.h"

using namespace std;

class KeyGame : public Component {
public:
	KeyGame(SDL_Rect path, SDL_Rect hit, PossesionGame* p): trail(path), hitmarker(hit), poss_(p), state_(nullptr) {};
	~KeyGame() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

	bool hitSkillCheck();

	inline void setTexture(Texture* txt) { tx_ = txt; };

	inline void setTextureDown(Texture* txt) { txDown_ = txt; };

	void updateGamePos(const SDL_Rect& hit, const SDL_Rect& trai);
private:
	void goBack();

	Transform* tr_;
	PossesionGame* poss_;
	Texture* tx_, * txDown_;
	GameStates* state_;

	SDL_Rect trail;
	SDL_Rect hitmarker;
	
	bool pressed = false, down = false;

	int timer, progress = 0;

	const int pressedTime = 150, speed = 5;
};