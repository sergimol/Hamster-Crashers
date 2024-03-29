#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "GameStates.h"

using namespace std;

class KeyGame : public Component {
public:
	KeyGame(SDL_Rect path, SDL_Rect hit, PossesionGame* p, int spd): trail_(path), hitmarker_(hit), poss_(p), reanim_(nullptr),state_(nullptr), speed_(spd) {};
	KeyGame(SDL_Rect path, SDL_Rect hit, ReanimationAlone* p, int spd) : trail_(path), hitmarker_(hit), reanim_(p), poss_(nullptr),state_(nullptr), speed_(spd) {};
	~KeyGame() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

	bool hitSkillCheck();

	inline void setTexture(Texture* txt) { tx_ = txt; };

	inline void setTextureDown(Texture* txt) { txDown_ = txt; };

	void updateGamePos(const SDL_Rect& hit, const SDL_Rect& trai, int dir);

	void goBack();
private:

	Transform* tr_;
	PossesionGame* poss_ = nullptr;
	ReanimationAlone* reanim_ = nullptr;
	Texture* tx_, * txDown_;
	GameStates* state_;

	SDL_Rect trail_;
	SDL_Rect hitmarker_;
	
	bool pressed_ = false, down_ = false;

	int timer_, progress_ = 0, dirX_ = 0;

	int pressedTime_ = 30, speed_;
};