#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

class Creditos : public Component
{public:
	Creditos() : tex_(&sdlutils().images().at("canelonSheet")) {};
	~Creditos() {
	};
	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

	void backToMenu();

	void endCreditos();

private:
	Texture* tex_;
	SDL_Rect imRect_;

	bool scrolling = true;

	int timer = 0;
	const int UPDATE = 50;
	const int ENDWAIT = 5000;
};

