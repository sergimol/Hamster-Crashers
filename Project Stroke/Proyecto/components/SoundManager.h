// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class SoundManager : public Component {
public:
	SoundManager() {}
	virtual ~SoundManager() {}

	void init() override;
	void play(std::string soundName);

private:
	int randomNum;

	void hit();

	void attack();

	void jump();

	void dep();

	int pickRandom(int max);


	//SOUND LIST AND CHANNELS
	int hits = 0;
	SoundEffect* hit0;

	int deps = 1;
	SoundEffect* dep0;
	SoundEffect* dep1;

};

