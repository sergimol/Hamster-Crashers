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
	int initSubtitleVol = 100;

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

	void  playHandPunch();

	int pickRandom(int max);



	//Golpe
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

	//Golpe Fuerte
	SoundEffect* strong0;
	SoundEffect* strong1;
	SoundEffect* strong2;

	//Ataque (whoosh)
	SoundEffect* attack0;
	SoundEffect* attack1;
	SoundEffect* attack2;
	SoundEffect* attack3;
	SoundEffect* attack4;

	//Muerte
	SoundEffect* dep0;
	SoundEffect* dep1;
	SoundEffect* dep2;

	//Ataque corazon
	SoundEffect* heartattack0;
	SoundEffect* heartattack1;
	SoundEffect* heartattack2;
	SoundEffect* heartattack3;
	SoundEffect* heartattack4;
	SoundEffect* heartattack5;

	//Boss Gato
	SoundEffect* catMeowStatic;
	SoundEffect* catMeowAttack;
	SoundEffect* catMeowInit;
	SoundEffect* catMeowWalking;

	//Boss Mano
	SoundEffect* heavyPunch0;
	SoundEffect* heavyPunch1;

	//Boss Mono
	SoundEffect* platillos;

	//Sonidos tren
	SoundEffect* trainBackground;
	SoundEffect* trainPipi;
	SoundEffect* trainAlto;

	//Coche
	SoundEffect* car0;
	SoundEffect* car1;
	SoundEffect* car2;

	//Muerte soldados
	SoundEffect* soldierDep0;
	SoundEffect* soldierDep1;
	SoundEffect* soldierDep2;
	SoundEffect* soldierDep3;

	//Juego reanimar, tecla correcta o fallida
	SoundEffect* rightNote;
	SoundEffect* wrongNote;

	//Posesion hamster
	SoundEffect* possesion;

	//Especial Sardinilla
	SoundEffect* sardinillaSpecial0;

	//Especial Keta
	SoundEffect* ketaSpecial0;
	SoundEffect* ketaSpecial1;
	SoundEffect* ketaSpecial2;
	SoundEffect* ketaSpecial3;
	SoundEffect* ketaSpecial4;

	//Especial monchi
	SoundEffect* monchiSpecial0;
	SoundEffect* monchiSpecial1;
	SoundEffect* monchiSpecial2;
	SoundEffect* monchiSpecial3;
	SoundEffect* monchiSpecial4;

	//Especial canelon
	int canelonState = 0;
	SoundEffect* canelonSpecial0;
	SoundEffect* canelonSpecial1;

	//Botones UI
	int buttonState = 0;
	SoundEffect* button0;
	SoundEffect* button1;

	//Musica y sonidos ambiente
	SoundEffect* mainTheme;
	SoundEffect* birds;

	//Recoger items
	SoundEffect* eat0;
	SoundEffect* eat1;
	SoundEffect* eat2;
	SoundEffect* eat3;

	//Transiciones
	SoundEffect* transition0;
	SoundEffect* transition1;

	//Trampa cocina
	SoundEffect* trapKitchen;

	//Dialogos Angel (tutorial y transiciones, falta diferenciarlos)
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

