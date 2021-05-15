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
	void setVolumeChannels();
	void lowVolume(bool channel);
	void upVolume(bool channel);
	void resetVolumes() { fxVol_ = 1; musicVol_ = 1; };

	void fadeOut(int time) { Mix_FadeOutChannel(musics, time);	fadeIn(8000);};
	//FADEPRUEBA
	//entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->fadeOut(3000);
	void fadeIn(int time) { Mix_FadeInChannel(musics,0,8000, time); };
	//channels
	int lighthits = 0;
	int stronghits = 1;
	int attacks = 2;
	int deps = 3;
	int heartattacks = 4;
	int musics = 5;

	//volumes
	//general
	float fxVol_ = 1;
	float musicVol_ = 1;
	//local
	int generalFXvol = 20;
	int initStrongVol = 60;
	int initMusicVol = 8;

private:
	int randomNum;

	void lighthit();

	void stronghit();

	void attack();

	void dep();

	void heartattack();

	int pickRandom(int max);


	//SOUND LIST AND CHANNELS
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

	SoundEffect* attack0;
	SoundEffect* attack1;
	SoundEffect* attack2;
	SoundEffect* attack3;
	SoundEffect* attack4;


	SoundEffect* dep0;
	SoundEffect* dep1;
	SoundEffect* dep2;

	SoundEffect* heartattack0;
	SoundEffect* heartattack1;
	SoundEffect* heartattack2;

	SoundEffect* mainTheme;

};

