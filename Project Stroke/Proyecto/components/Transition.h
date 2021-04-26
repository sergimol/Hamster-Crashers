#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

using namespace std;

class Transition : public Component {
public:
	Transition(Texture* tx) : tx_(tx), alpha(0), alphaCalc(0), fadingOut(false), fadingIn(false), change(false){
	}

		virtual ~Transition() {}

	void init() override;

	void update() override;

	void render() override;

	inline void startFadeIn() { fadingOut = true; fadingIn = false; };

	inline void startFadeOut() { fadingIn = true; fadingOut = false;};

	void changeScene(string nameScene);

	void sceneTransition();

	void createMap();

	bool isFadingOut();

	bool isFading();

private:
	void fadeOut();

	void fadeIn();

	int alpha;
	Texture* tx_;
	float alphaCalc;

	const float FADE_SPEED = 7;

	bool fadingOut;
	bool fadingIn;

	bool change;

	SDL_Rect blackRect;

	string nameScene_;
};


