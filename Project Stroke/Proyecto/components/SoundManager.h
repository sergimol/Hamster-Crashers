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

	void fadeOut(int time) { Mix_FadeOutChannel(musics, time); };
	//FADEPRUEBA
	//entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->fadeOut(3000);
	//void fadeIn(int time);
	//channels
	int lighthits = 0;
	int stronghits = 1;
	int attacks = 2;
	int deps = 3;
	int heartattacks = 4;
	int musics = 5;
	int subtitles = 6;

	//volumes
	//general
	float fxVol_ = 1;
	float musicVol_ = 1;
	//local
	int generalFXvol = 20;
	int initStrongVol = 60;
	int initMusicVol = 8;
	int initSubtitleVol = 20;

private:
	int randomNum;
	int dialogueNum = 0;

	void lighthit();

	void stronghit();

	void attack();

	void dep();

	void heartattack();

	void subtitle();

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

	SoundEffect* dialogue0;
	SoundEffect* dialogue1;
	SoundEffect* dialogue2;
	SoundEffect* dialogue3;
	SoundEffect* dialogue4;
	SoundEffect* dialogue5;
	SoundEffect* dialogue6;
	SoundEffect* dialogue7;
	SoundEffect* dialogue8;
	SoundEffect* dialogue9;
	SoundEffect* dialogue10;
	SoundEffect* dialogue11;
	SoundEffect* dialogue12;
	SoundEffect* dialogue13;
	SoundEffect* dialogue14;
	SoundEffect* dialogue15;
	SoundEffect* dialogue16;
	SoundEffect* dialogue17;
	SoundEffect* dialogue18;
	SoundEffect* dialogue19;
	SoundEffect* dialogue20;
	SoundEffect* dialogue21;
	SoundEffect* dialogue22;
	SoundEffect* dialogue23;
	SoundEffect* dialogue24;
	SoundEffect* dialogue25;
	SoundEffect* dialogue26;
	SoundEffect* dialogue27;
	SoundEffect* dialogue28;
	SoundEffect* dialogue29;
	SoundEffect* dialogue30;

};

