#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "GameStates.h"
#include "subtitulos.h"

using namespace std;

class Transition : public Component {
public:
	Transition(Texture* tx) : tx_(tx), alpha(0), alphaCalc(0), fadingOut(false), fadingIn(false), change(false), state_(nullptr){
	}

		virtual ~Transition() {}

	void init() override;

	void update() override;

	void render() override;

	inline void startFadeIn() { fadingOut = true; fadingIn = false; };

	inline void startFadeOut() { fadingIn = true; fadingOut = false;};

	void changeScene(string nameScene, bool changeMap, int numTransitions);

	void sceneTransition();

	void createMap();

	bool isFadingOut();

	bool isFading();

private:
	void fadeOut();

	void fadeIn();

	int alpha;
	int numT;
	int numTReference;
	Texture* tx_;
	float alphaCalc;

	const float FADE_SPEED = 0.5;

	bool fadingOut;
	bool fadingIn;

	bool change;

	bool changeMap_;

	SDL_Rect blackRect;

	string nameScene_;
	string subs;
	
	GameStates* state_;
	Subtitulos* subs_;
};


