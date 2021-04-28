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

	void lighthit();

	void stronghit();

	void attack();

	void dep();

	void heartattack();

	int pickRandom(int max);


	//SOUND LIST AND CHANNELS
	int hits = 0;
	SoundEffect* light0;
	SoundEffect* light1;
	SoundEffect* light2;
	SoundEffect* light3;
	SoundEffect* light4;
	SoundEffect* light5;
	SoundEffect* light6;
	SoundEffect* light7;
	SoundEffect* light8;
	SoundEffect* light9;
	SoundEffect* light10;

	SoundEffect* strong0;
	SoundEffect* strong1;
	SoundEffect* strong2;

	int attacks = 1;
	SoundEffect* attack0;
	SoundEffect* attack1;
	SoundEffect* attack2;
	SoundEffect* attack3;
	SoundEffect* attack4;


	int deps = 2;
	SoundEffect* dep0;
	SoundEffect* dep1;
	SoundEffect* dep2;

	int heartattacks = 3;
	SoundEffect* heartattack0;
	SoundEffect* heartattack1;
	SoundEffect* heartattack2;


};

