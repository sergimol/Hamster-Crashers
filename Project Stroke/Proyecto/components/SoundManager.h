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
	void resetVolumes() { fxVol_ = 0.5; musicVol_ = 0.5; setVolumeChannels(); sdlutils().setMusicVol(musicVol_); sdlutils().setFxVol(fxVol_); };
	bool emptyChannel();
	void StopTutorial();
	void fadeout(int time) {}
	//FADEPRUEBA
	//entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->fadeOut(3000);
	//void fadeIn(int time);

	//volumes
	//general
	float fxVol_ = 0.5f;
	float musicVol_ = 0.5f;
	//local
	int initMusicVol = 20;


	int initLightVol = 100;
	int initStrongVol = 128;
	int initAttackVol = 100;

	int initDepVol = 40;
	int initHeartAttackVol = 40;

	int initCatVol = 40;

	int initHandVol = 40;

	int initMonkeVol = 40;

	int inittrainBackgroundVol = 40;

	int carVol = 40;

	int initsoldierDepVol = 3;

	int notesReanimVol = 40;
	int possesionVol = 40;

	int sardinillaSpecialVol = 60;
	int ketaSpecialVol = 40;
	int monchiSpecialVol = 20;
	int canelonSpecialVol = 40;

	int buttonVol = 128;

	int initEatVol = 40;

	int pageSkipVol = 100;
	int initTutorialVol = 128;
	int initTransitionVol = 128;

	int inittrapKitchenVol = 40;

	int initBirdsVol = 40;


private:
	int randomNum;

	void playLighthit();
	void playHamsterLighthit();

	void playStronghit();

	void playAttack();

	void playDep();

	void playHeartattack();

	void playTutorial();
	void playTransition();

	void playKetaSpecial();

	void playMonchiSpecial();

	void playCanelonSpecial();

	void playCar();

	void  playEat();

	void  playsoldierDep();

	void  playPageSkip();

	void  playHandInit();
	void  playHandPunch();
	void  playHandHit();

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

	//Golpe Hamster 
	SoundEffect* hamLight0;
	SoundEffect* hamLight1;
	SoundEffect* hamLight2;
	SoundEffect* hamLight3;
	SoundEffect* hamLight4;

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
	SoundEffect* catMeowSleeping;

	//Boss Mano
	SoundEffect* handInit0;
	SoundEffect* handInit1;

	SoundEffect* heavyPunch0;
	SoundEffect* heavyPunch1;

	SoundEffect* handHit0;
	SoundEffect* handHit1;
	SoundEffect* handHit2;

	SoundEffect* handDep;
	

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


	//Recoger items
	SoundEffect* eat0;
	SoundEffect* eat1;
	SoundEffect* eat2;
	SoundEffect* eat3;

	//PageNext
	SoundEffect* pageSkip0;
	SoundEffect* pageSkip1;


	//Trampa cocina
	SoundEffect* trapKitchen;

	//Dialogos Angel (tutorial y transiciones, falta diferenciarlos)
	int tutorialNum = 0;
	SoundEffect* tutorial0;
	SoundEffect* tutorial1;
	SoundEffect* tutorial2;
	SoundEffect* tutorial3;
	SoundEffect* tutorial4;
	SoundEffect* tutorial5;
	SoundEffect* tutorial6;
	SoundEffect* tutorial7;
	SoundEffect* tutorial8;
	SoundEffect* tutorial9;
	SoundEffect* tutorial10;
	SoundEffect* tutorialsingle;

	int transitionNum = 0;
	SoundEffect* transition0;
	SoundEffect* transition1;
	SoundEffect* transition2;
	SoundEffect* transition3;
	SoundEffect* transition4;
	SoundEffect* transition5;
	SoundEffect* transition6;
	SoundEffect* transition7;
	SoundEffect* transition8;
	SoundEffect* transition9;
	SoundEffect* transition10;

	//Musica y sonidos ambiente
	Music* HamstersMainThemev2;
	Music* Nivel1GameVersion;
	Music* Nivel1Boss1_0;
	Music* HamstersNivel2GameVersion;
	Music* HamstersNivel2_Boss160bpm;
	Music* HamstersNivel4_Boss2;
	Music* HamstersNivel4GameVersion;

	SoundEffect* birds;

};

