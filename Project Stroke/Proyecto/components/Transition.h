#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"



class Transition : public Component {
public:
	Transition(Texture* tx) : tx_(tx), alpha(0), alphaCalc(0), fadingIn(false), fadingOut(false){
	}

		virtual ~Transition() {}

	void init() override;

	void update() override;

	void render() override;

	inline void startFadeIn() { fadingIn = true; fadingOut = false; };

	inline void startFadeOut() { fadingOut = true; fadingIn = false;};

private:
	void fadeIn();

	void fadeOut();

	int alpha;
	Texture* tx_;
	float alphaCalc;

	const float FADE_SPEED = 0.5;

	bool fadingIn;
	bool fadingOut;

	SDL_Rect blackRect;
};


