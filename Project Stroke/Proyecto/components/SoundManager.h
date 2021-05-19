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
	bool emptyChannel(int channel);

	void fadeOut(int time) { Mix_FadeOutChannel(musicsChannel, time); };
	//FADEPRUEBA
	//entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->fadeOut(3000);
	//void fadeIn(int time);
	//channels
	int lighthitsChannel = 0;
	int stronghitsChannel = 0;
	int attacksChannel = 0;

	int depsChannel = 1;
	int heartattacksChannel = 1;
	int soldierDepChannel = 1;

	int musicsChannel = 2;
	int subtitlesChannel = 2;
	int birdsChannel = 2;

	int catChannel = 3;
	int carChannel = 3;

	int ketaSpecialChannel = 4;
	int monchiSpecialChannel = 4;
	int canelonSpecialChannel = 4;

	int buttonChannel = 5;
	int EatChannel = 5;

	int trainBackgroundChannel = 6;
	int transitionChannel = 6;
	int trapKitchenChannel = 6;




	//volumes
	//general
	float fxVol_ = 1;
	float musicVol_ = 1;
	//local
	int generalFXvol = 20;

	int initStrongVol = 60;
	int initSubtitleVol = 20;

	int ketaSpecialVol = 20;
	int monchiSpecialVol = 20;
	int canelonSpecialVol = 20;

	int initCatVol = 20;
	int carVol = 20;

	int buttonVol = 20;

	int initMusicVol = 8;
	int initBirdsVol = 20;

	int initEatVol = 20;

	int initsoldierDepVol = 20;
	
	int inittrainBackgroundVol = 20;

	int inittransitionVol = 20;

	int inittrapKitchenVol = 20;
private:
	int randomNum;
	int dialogueNum = 0;

	void playLighthit();

	void playStronghit();

	void playAttack();

	void playDep();

	void playHeartattack();

	void playSubtitle();

	void playKetaSpecial();

	void playMonchiSpecial();

	void playCanelonSpecial();

	void playCar();

	void  playEat();

	void  playsoldierDep();

	void  playtransition();

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
	SoundEffect* heartattack3;
	SoundEffect* heartattack4;
	SoundEffect* heartattack5;

	SoundEffect* catMeowStatic;
	SoundEffect* catMeowAttack;
	SoundEffect* catMeowInit;
	SoundEffect* catMeowWalking;

	SoundEffect* ketaSpecial0;
	SoundEffect* ketaSpecial1;
	SoundEffect* ketaSpecial2;
	SoundEffect* ketaSpecial3;
	SoundEffect* ketaSpecial4;

	SoundEffect* monchiSpecial0;
	SoundEffect* monchiSpecial1;
	SoundEffect* monchiSpecial2;
	SoundEffect* monchiSpecial3;
	SoundEffect* monchiSpecial4;

	int canelonState = 0;
	SoundEffect* canelonSpecial0;
	SoundEffect* canelonSpecial1;

	//Enemigos
	SoundEffect* car0;
	SoundEffect* car1;
	SoundEffect* car2;

	int buttonState = 0;
	SoundEffect* button0;
	SoundEffect* button1;

	SoundEffect* mainTheme;
	SoundEffect* birds;

	SoundEffect* eat0;
	SoundEffect* eat1;

	SoundEffect* soldierDep0;
	SoundEffect* soldierDep1;
	SoundEffect* soldierDep2;
	SoundEffect* soldierDep3;

	SoundEffect* trainBackground;
	SoundEffect* trainPipi;
	SoundEffect* trainAlto;

	SoundEffect* transition0;
	SoundEffect* transition1;

	SoundEffect* trapKitchen;


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

