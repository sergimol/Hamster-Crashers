#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class SoundManager : public Component {
public:
	SoundManager() {}
	virtual ~SoundManager() {}

	void init() override;
	void play(std::string soundName);
	void lowVolume(bool channel);
	void upVolume(bool channel);
	void resetVolumes() { fxVol_ = 0.5; musicVol_ = 0.5; sdlutils().setMusicVol(musicVol_); sdlutils().setFxVol(fxVol_); };
	bool emptyChannel();
	void StopTutorial();
	void StopBossSounds();

	void refreshMusicVol();
	//FADEPRUEBA
	//entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->fadeOut(3000);
	//void fadeIn(int time);

	//volumes
	//general
	float fxVol_ = 0.5f;
	float musicVol_ = 0.5f;
	//local
	int initMusicVol = 35;

	int initLightVol = 80;
	int initStrongVol = 128;
	int initAttackVol = 90;

	int initDepVol = 40;
	int initHeartAttackVol = 50;

	int initCatVol = 80;

	int initHandVol = 128;

	int initMonkeVol = 128;

	int inittrainBackgroundVol = 40;

	int carVol = 60;

	int initsoldierDepVol = 65;

	int notesReanimVol = 120;
	int possesionVol = 120;

	int sardinillaSpecialVol = 120;
	int ketaSpecialVol = 80;
	int monchiSpecialVol = 120;
	int canelonSpecialVol = 120;

	int buttonVol = 128;

	int initEatVol = 60;

	int pageSkipVol = 128;
	int initTutorialVol = 60;
	int initTransitionVol = 60;

	int inittrapKitchenVol = 80;

	int initBirdsVol = 128;

	int initMicrowaveVol = 128;
	int initMicrowaveExplosionVol = 60;

	int initAngelVol = 100;

	void resetNumInts();
private:
	int randomNum;

	void playLighthit();

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

	void  playAngelHit();
	void  playAngelAttack();

	void playTrap();

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
	SoundEffect* trapKitchen0;
	SoundEffect* trapKitchen1;
	SoundEffect* trapKitchen2;

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
	SoundEffect* transition11;
	SoundEffect* transition12;
	SoundEffect* transition13;
	SoundEffect* transition14;
	SoundEffect* transition15;
	SoundEffect* transition16;
	SoundEffect* transition17;
	SoundEffect* transition18;
	SoundEffect* transition19;
	SoundEffect* transition20;
	SoundEffect* transition21;
	SoundEffect* transition22;
	SoundEffect* transition23;

	//Page transitions
	SoundEffect* page0;
	SoundEffect* page1;
	SoundEffect* page2;
	SoundEffect* page3;
	SoundEffect* page4;


	//Musica y sonidos ambiente
	Music* HamstersMainThemev2;
	Music* Nivel1GameVersion;
	Music* Nivel1Boss1_0;
	Music* HamstersNivel2GameVersion;
	Music* HamstersNivel2_Boss160bpm;
	Music* HamstersNivel4_Boss2;
	Music* HamstersNivel4GameVersion;

	SoundEffect* birds;

	SoundEffect* microBep;
	SoundEffect* microExplosion;
	SoundEffect* microStatic;
	SoundEffect* microTiktak;

	//Angel
	SoundEffect* AngelAttack0;
	SoundEffect* AngelAttack1;
	SoundEffect* AngelAttack2;
	SoundEffect* AngelAttack3;
	SoundEffect* AngelAttack4;
	SoundEffect* AngelAttack5;

	SoundEffect* AngelHit0;
	SoundEffect* AngelHit1;
	SoundEffect* AngelHit2;
	SoundEffect* AngelHit3;

	SoundEffect* AngelDep;


};

