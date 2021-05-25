#include "SoundManager.h"

void SoundManager::init() {
	light0 = &sdlutils().soundEffects().at("light0");
	light1 = &sdlutils().soundEffects().at("light1");
	light2 = &sdlutils().soundEffects().at("light2");
	light3 = &sdlutils().soundEffects().at("light3");
	light4 = &sdlutils().soundEffects().at("light4");
	light5 = &sdlutils().soundEffects().at("light5");
	light6 = &sdlutils().soundEffects().at("light6");
	light7 = &sdlutils().soundEffects().at("light7");
	light8 = &sdlutils().soundEffects().at("light8");
	light9 = &sdlutils().soundEffects().at("light9");
	light10 = &sdlutils().soundEffects().at("light10");

	strong0 = &sdlutils().soundEffects().at("strong0");
	strong1 = &sdlutils().soundEffects().at("strong1");
	strong2 = &sdlutils().soundEffects().at("strong2");

	attack0 = &sdlutils().soundEffects().at("attack0");
	attack1 = &sdlutils().soundEffects().at("attack1");
	attack2 = &sdlutils().soundEffects().at("attack2");
	attack3 = &sdlutils().soundEffects().at("attack3");
	attack4 = &sdlutils().soundEffects().at("attack4");



	dep0 = &sdlutils().soundEffects().at("dep0");
	dep1 = &sdlutils().soundEffects().at("dep1");
	dep2 = &sdlutils().soundEffects().at("dep2");

	heartattack0 = &sdlutils().soundEffects().at("heartattack0");
	heartattack1 = &sdlutils().soundEffects().at("heartattack1");
	heartattack2 = &sdlutils().soundEffects().at("heartattack2");

	//Cat Boss
	catMeowStatic = &sdlutils().soundEffects().at("catMeow");
	catMeowAttack = &sdlutils().soundEffects().at("catMeowAttack");
	catMeowInit = &sdlutils().soundEffects().at("catMeowInit");
	catMeowWalking = &sdlutils().soundEffects().at("catWalking");
	catMeowSleeping = &sdlutils().soundEffects().at("catSleeping");
	//HandBoss
	heavyPunch0 = &sdlutils().soundEffects().at("heavyPunch0");
	heavyPunch1 = &sdlutils().soundEffects().at("heavyPunch1");

	//Mono andando adonde ira
	platillos = &sdlutils().soundEffects().at("platillos");

	//KeyGame
	rightNote = &sdlutils().soundEffects().at("rightNote");
	wrongNote = &sdlutils().soundEffects().at("wrongNote");

	sardinillaSpecial0 = &sdlutils().soundEffects().at("sardinillaSpecial0");

	ketaSpecial0 = &sdlutils().soundEffects().at("ketaSpecial0");
	ketaSpecial1 = &sdlutils().soundEffects().at("ketaSpecial1");
	ketaSpecial2 = &sdlutils().soundEffects().at("ketaSpecial2");
	ketaSpecial3 = &sdlutils().soundEffects().at("ketaSpecial3");
	ketaSpecial4 = &sdlutils().soundEffects().at("ketaSpecial4");

	monchiSpecial0 = &sdlutils().soundEffects().at("monchiSpecial0");
	monchiSpecial1 = &sdlutils().soundEffects().at("monchiSpecial1");
	monchiSpecial2 = &sdlutils().soundEffects().at("monchiSpecial2");
	monchiSpecial3 = &sdlutils().soundEffects().at("monchiSpecial3");
	monchiSpecial4 = &sdlutils().soundEffects().at("monchiSpecial4");

	canelonSpecial0 = &sdlutils().soundEffects().at("canelonSpecialGod");
	canelonSpecial1 = &sdlutils().soundEffects().at("canelonSpecialDevil");

	button0 = &sdlutils().soundEffects().at("button0");	//No lo uso
	button1 = &sdlutils().soundEffects().at("button1");

	car0 = &sdlutils().soundEffects().at("car0");
	car1 = &sdlutils().soundEffects().at("car1");
	car2 = &sdlutils().soundEffects().at("car2");

	HamstersMainThemev2 = &sdlutils().musics().at("HamstersMainThemev2");
	Nivel1GameVersion = &sdlutils().musics().at("Nivel1GameVersion");
	Nivel1Boss1_0 = &sdlutils().musics().at("Nivel1Boss1_0");
	HamstersNivel2GameVersion = &sdlutils().musics().at("HamstersNivel2GameVersion");
	HamstersNivel2_Boss160bpm = &sdlutils().musics().at("HamstersNivel2_Boss160bpm");
	HamstersNivel4_Boss2 = &sdlutils().musics().at("HamstersNivel4_Boss2");
	HamstersNivel4GameVersion = &sdlutils().musics().at("HamstersNivel4GameVersion");

	birds = &sdlutils().soundEffects().at("birds");

	eat0 = &sdlutils().soundEffects().at("eat0");
	eat1 = &sdlutils().soundEffects().at("eat1");
	eat2 = &sdlutils().soundEffects().at("eat2");
	eat3 = &sdlutils().soundEffects().at("eat3");

	soldierDep0 = &sdlutils().soundEffects().at("soldierDep0");
	soldierDep1 = &sdlutils().soundEffects().at("soldierDep1");
	soldierDep2 = &sdlutils().soundEffects().at("soldierDep2");
	soldierDep3 = &sdlutils().soundEffects().at("soldierDep3");

	trainBackground = &sdlutils().soundEffects().at("trainBackground");;
	trainPipi = &sdlutils().soundEffects().at("trainPipi");
	trainAlto = &sdlutils().soundEffects().at("trainAlto");

	pageSkip0 = &sdlutils().soundEffects().at("transition0");
	pageSkip1 = &sdlutils().soundEffects().at("transition1");

	trapKitchen = &sdlutils().soundEffects().at("trapKitchen");

	tutorial0 = &sdlutils().soundEffects().at("tutorial0");
	tutorial1 = &sdlutils().soundEffects().at("tutorial1");
	tutorial2 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial3 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial4 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial5 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial6 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial7 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial8 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial9 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial10 = &sdlutils().soundEffects().at("catMeowInit");


	transition0 = &sdlutils().soundEffects().at("tutorial0");
	transition1 = &sdlutils().soundEffects().at("tutorial0");
	transition2 = &sdlutils().soundEffects().at("tutorial0");
	transition3 = &sdlutils().soundEffects().at("tutorial0");
	transition4 = &sdlutils().soundEffects().at("tutorial0");
	transition5 = &sdlutils().soundEffects().at("tutorial0");
	transition6 = &sdlutils().soundEffects().at("tutorial0");
	transition7 = &sdlutils().soundEffects().at("tutorial0");
	transition8 = &sdlutils().soundEffects().at("tutorial0");
	transition9 = &sdlutils().soundEffects().at("tutorial0");
	transition10 = &sdlutils().soundEffects().at("tutorial0");



	Vector2D vol = sdlutils().volumes();
	musicVol_ = vol.getX();
	fxVol_ = vol.getY();

	setVolumeChannels();
	Mix_AllocateChannels(16);
}

void SoundManager::StopTutorial() {
	Mix_HaltChannel(7);
}

void SoundManager::setVolumeChannels() {
	//Golpe
	light0->setChannelVolume(fxVol_ * initLightVol);
	light1->setChannelVolume(fxVol_ * initLightVol);
	light2->setChannelVolume(fxVol_ * initLightVol);
	light3->setChannelVolume(fxVol_ * initLightVol);
	light4->setChannelVolume(fxVol_ * initLightVol);
	light5->setChannelVolume(fxVol_ * initLightVol);
	light6->setChannelVolume(fxVol_ * initLightVol);
	light7->setChannelVolume(fxVol_ * initLightVol);
	light8->setChannelVolume(fxVol_ * initLightVol);

	//Golpe Fuerte
	strong0->setChannelVolume(fxVol_ * initStrongVol);
	strong1->setChannelVolume(fxVol_ * initStrongVol);
	strong2->setChannelVolume(fxVol_ * initStrongVol);

	//Ataque (whoosh)
	attack0->setChannelVolume(fxVol_ * initAttackVol);
	attack1->setChannelVolume(fxVol_ * initAttackVol);
	attack2->setChannelVolume(fxVol_ * initAttackVol);
	attack3->setChannelVolume(fxVol_ * initAttackVol);
	attack4->setChannelVolume(fxVol_ * initAttackVol);

	//Muerte
	dep0->setChannelVolume(fxVol_ * initDepVol);
	dep1->setChannelVolume(fxVol_ * initDepVol);
	dep2->setChannelVolume(fxVol_ * initDepVol);

	//Ataque corazon
	heartattack0->setChannelVolume(fxVol_ * initHeartAttackVol);
	heartattack1->setChannelVolume(fxVol_ * initHeartAttackVol);
	heartattack2->setChannelVolume(fxVol_ * initHeartAttackVol);
	heartattack3->setChannelVolume(fxVol_ * initHeartAttackVol);
	heartattack4->setChannelVolume(fxVol_ * initHeartAttackVol);
	heartattack5->setChannelVolume(fxVol_ * initHeartAttackVol);

	//Boss Gato
	catMeowStatic->setChannelVolume(fxVol_ * initCatVol);
	catMeowAttack->setChannelVolume(fxVol_ * initCatVol);
	catMeowInit->setChannelVolume(fxVol_ * initCatVol);
	catMeowWalking->setChannelVolume(fxVol_ * initCatVol);

	//Boss Mano
	heavyPunch0->setChannelVolume(fxVol_ * initHandVol);
	heavyPunch1->setChannelVolume(fxVol_ * initHandVol);

	//Boss Mono
	platillos->setChannelVolume(fxVol_ * initMonkeVol);

	//Sonidos tren
	trainBackground->setChannelVolume(fxVol_ * inittrainBackgroundVol);
	trainPipi->setChannelVolume(fxVol_ * inittrainBackgroundVol);
	trainAlto->setChannelVolume(fxVol_ * inittrainBackgroundVol);

	//Coche
	car0->setChannelVolume(fxVol_ * carVol);
	car1->setChannelVolume(fxVol_ * carVol);
	car2->setChannelVolume(fxVol_ * carVol);

	//Muerte soldados
	soldierDep0->setChannelVolume(fxVol_ * initsoldierDepVol);
	soldierDep1->setChannelVolume(fxVol_ * initsoldierDepVol);
	soldierDep2->setChannelVolume(fxVol_ * initsoldierDepVol);
	soldierDep3->setChannelVolume(fxVol_ * initsoldierDepVol);

	//Juego reanimar, tecla correcta o fallida
	rightNote->setChannelVolume(fxVol_ * notesReanimVol);
	wrongNote->setChannelVolume(fxVol_ * notesReanimVol);

	//Posesion hamster
	possesion->setChannelVolume(fxVol_ * possesionVol);

	//Especial Sardinilla
	sardinillaSpecial0->setChannelVolume(fxVol_ * sardinillaSpecialVol);

	//Especial Keta
	ketaSpecial0->setChannelVolume(fxVol_ * ketaSpecialVol);
	ketaSpecial1->setChannelVolume(fxVol_ * ketaSpecialVol);
	ketaSpecial2->setChannelVolume(fxVol_ * ketaSpecialVol);
	ketaSpecial3->setChannelVolume(fxVol_ * ketaSpecialVol);
	ketaSpecial4->setChannelVolume(fxVol_ * ketaSpecialVol);

	//Especial monchi
	monchiSpecial0->setChannelVolume(fxVol_ * monchiSpecialVol);
	monchiSpecial1->setChannelVolume(fxVol_ * monchiSpecialVol);
	monchiSpecial2->setChannelVolume(fxVol_ * monchiSpecialVol);
	monchiSpecial3->setChannelVolume(fxVol_ * monchiSpecialVol);
	monchiSpecial4->setChannelVolume(fxVol_ * monchiSpecialVol);

	//Especial canelon
	canelonSpecial0->setChannelVolume(fxVol_ * canelonSpecialVol);
	canelonSpecial1->setChannelVolume(fxVol_ * canelonSpecialVol);

	//Botones UI
	button0->setChannelVolume(fxVol_ * buttonVol);
	button1->setChannelVolume(fxVol_ * buttonVol);

	//Recoger items
	eat0->setChannelVolume(fxVol_ * initEatVol);
	eat1->setChannelVolume(fxVol_ * initEatVol);
	eat2->setChannelVolume(fxVol_ * initEatVol);
	eat3->setChannelVolume(fxVol_ * initEatVol);

	//Trampa cocina
	trapKitchen->setChannelVolume(fxVol_ * inittrapKitchenVol);

	//PageNext
	pageSkip0->setChannelVolume(fxVol_ * pageSkipVol);
	pageSkip1->setChannelVolume(fxVol_ * pageSkipVol);

	//Dialogos Angel (tutorial y transiciones, falta diferenciarlos)
	tutorial0->setChannelVolume(fxVol_ * initTutorialVol);
	tutorial1->setChannelVolume(fxVol_ * initTutorialVol);
	tutorial2->setChannelVolume(fxVol_ * initTutorialVol);
	tutorial3->setChannelVolume(fxVol_ * initTutorialVol);
	tutorial4->setChannelVolume(fxVol_ * initTutorialVol);
	tutorial5->setChannelVolume(fxVol_ * initTutorialVol);
	tutorial6->setChannelVolume(fxVol_ * initTutorialVol);
	tutorial7->setChannelVolume(fxVol_ * initTutorialVol);
	tutorial8->setChannelVolume(fxVol_ * initTutorialVol);
	tutorial9->setChannelVolume(fxVol_ * initTutorialVol);
	tutorial10->setChannelVolume(fxVol_ * initTutorialVol);

	transition0->setChannelVolume(fxVol_ * initTransitionVol);
	transition1->setChannelVolume(fxVol_ * initTransitionVol);
	transition2->setChannelVolume(fxVol_ * initTransitionVol);
	transition3->setChannelVolume(fxVol_ * initTransitionVol);
	transition4->setChannelVolume(fxVol_ * initTransitionVol);
	transition5->setChannelVolume(fxVol_ * initTransitionVol);
	transition6->setChannelVolume(fxVol_ * initTransitionVol);
	transition7->setChannelVolume(fxVol_ * initTransitionVol);
	transition8->setChannelVolume(fxVol_ * initTransitionVol);
	transition9->setChannelVolume(fxVol_ * initTransitionVol);
	transition10->setChannelVolume(fxVol_ * initTransitionVol);

	// sonidos ambiente
	birds->setChannelVolume(fxVol_ * initBirdsVol);

	//Canciones
	HamstersMainThemev2->setMusicVolume(musicVol_ * initMusicVol);
	Nivel1GameVersion->setMusicVolume(musicVol_ * initMusicVol);
	Nivel1Boss1_0->setMusicVolume(musicVol_ * initMusicVol);
	HamstersNivel2GameVersion->setMusicVolume(musicVol_ * initMusicVol);
	HamstersNivel2_Boss160bpm->setMusicVolume(musicVol_ * initMusicVol);
	HamstersNivel4_Boss2->setMusicVolume(musicVol_ * initMusicVol);
	HamstersNivel4GameVersion->setMusicVolume(musicVol_ * initMusicVol);
}

void SoundManager::lowVolume(bool musicChannel) {
	//if (musicVol_ > 0 && fxVol_ > 0) {
	if (musicChannel) {
		musicVol_ = musicVol_ - 0.1f;
		if (musicVol_ < 0)
			musicVol_ = 0;
		sdlutils().setMusicVol(musicVol_);
	}

	else {
		fxVol_ = fxVol_ - 0.1f;
		if (fxVol_ < 0)
			fxVol_ = 0;
		sdlutils().setFxVol(fxVol_);
	}
	//}

	setVolumeChannels();
}

void SoundManager::upVolume(bool musicChannel) {
	if (musicChannel) {
		musicVol_ = musicVol_ + 0.1f;
		sdlutils().setMusicVol(musicVol_);
	}

	else {
		fxVol_ = fxVol_ + 0.1f;
		sdlutils().setFxVol(fxVol_);
	}

	setVolumeChannels();
}

bool SoundManager::emptyChannel() {
	if (!Mix_Playing(7)) {
		return true;
	}
	else
		return false;
}


void SoundManager::play(std::string soundName) {
	//Golpe
	if (soundName == "lighthit") {
		playLighthit();
	}
	//Golpe Fuerte
	else if (soundName == "stronghit") {
		playStronghit();
	}
	//Ataque (whoosh)
	else if (soundName == "attack") {
		playAttack();
	}
	//Muerte
	else if (soundName == "dep") {
		playDep();
	}
	//Ataque corazon
	else if (soundName == "heartattack") {
		playHeartattack();
	}

	//Especiales Hamsters
	else if (soundName == "sardinillaSpecial") {
		sardinillaSpecial0->play();
	}
	else if (soundName == "ketaSpecial") {
		playKetaSpecial();
	}
	else if (soundName == "monchiSpecial") {
		playMonchiSpecial();
	}
	else if (soundName == "canelonSpecial") {
		playCanelonSpecial();
	}
	//Boss Gato
	else if (soundName == "catMeowInit") {
		catMeowInit->play();
	}
	else if (soundName == "catMeowStatic") {
		catMeowStatic->play();
	}
	else if (soundName == "catMeowAttack") {
		catMeowAttack->play();
	}
	else if (soundName == "catMeowWalking") {
		catMeowWalking->play();
	}
	else if (soundName == "catMeowSleeping") {
		catMeowWalking->play();
	}

	//Boss Mano
	else if (soundName == "handPunch") {
		playHandPunch();
	}

	//Boss Mono
	else if (soundName == "platillos") {
		platillos->play();
	}

	//Sonidos tren
	else if (soundName == "trainBackground") {

		trainBackground->play(200);
	}
	else if (soundName == "trainPipi") {

		trainPipi->play();
	}
	else if (soundName == "trainPasoalto") {

		trainAlto->play();
	}

	//Enemigo coche
	else if (soundName == "coche") {
		playCar();
	}

	//Muerte soldados
	else if (soundName == "soldierDep") {
		playsoldierDep();
	}

	//Juego reanimar, tecla correcta o fallida
	else if (soundName == "rightNote") {
		rightNote->play(0);
	}
	else if (soundName == "wrongNote") {
		wrongNote->play(0);
	}
	//Posesion hamster
	else if (soundName == "possesion") {
		possesion->play(0);
	}

	//Botones UI
	else if (soundName == "button") {
		button1->play(0);
	}


	else if (soundName == "birds") {
		birds->play(200);
	}

	//Recoger items
	else if (soundName == "eatItem") {
		playEat();
	}

	//Transiciones
	else if (soundName == "transition") {
		playTransition();
	}
	else if (soundName == "nextPage") {
		playPageSkip();
	}
	else if (soundName == "tutorial") {
		playTutorial();
	}
	else if (soundName == "stopTutorial") {
		StopTutorial();
	}

	//Trampa cocina
	else if (soundName == "trapKitchen") {
		trapKitchen->play(0);
	}


	//CANCIONES
	else if (soundName == "HamstersMainThemev2") {
		Mix_HaltMusic();
		HamstersMainThemev2->play(200);
	}
	else if (soundName == "Nivel1GameVersion") {
		Mix_HaltMusic();
		Nivel1GameVersion->play(200);
	}
	else if (soundName == "Nivel1Boss1_0") {
		Mix_HaltMusic();
		Nivel1Boss1_0->play(200);
	}
	else if (soundName == "HamstersNivel2GameVersion") {
		Mix_HaltMusic();
		HamstersNivel2GameVersion->play(200);
	}
	else if (soundName == "HamstersNivel2_Boss160bpm") {
		Mix_HaltMusic();
		HamstersNivel2_Boss160bpm->play(200);
	}
	else if (soundName == "HamstersNivel4_Boss2") {
		Mix_HaltMusic();
		HamstersNivel4_Boss2->play(200);
	}
	else if (soundName == "HamstersNivel4GameVersion") {
		Mix_HaltMusic();
		HamstersNivel4GameVersion->play(200);
	}
}

int SoundManager::pickRandom(int max) {
	int randomNum;
	randomNum = sdlutils().rand().nextInt(0, max);
	return randomNum;
}

void SoundManager::playLighthit() {
	randomNum = pickRandom(11);
	switch (randomNum)
	{
	case 0:
		light0->play();
		break;
	case 1:
		light1->play();
		break;
	case 2:
		light2->play();
		break;
	case 3:
		light3->play();
		break;
	case 4:
		light4->play();
		break;
	case 5:
		light5->play();
		break;
	case 6:
		light6->play();
		break;
	case 7:
		light7->play();
		break;
	case 8:
		light8->play();
		break;
	case 9:
		light9->play();
		break;
	case 10:
		light10->play();
		break;
	default:
		break;
	}
}

void SoundManager::playStronghit() {
	randomNum = pickRandom(3);

	switch (randomNum)
	{
	case 0:
		strong0->play();
		break;
	case 1:
		strong1->play();
		break;
	case 2:
		strong2->play();
		break;
	default:
		break;
	}
}

void SoundManager::playAttack() {
	randomNum = pickRandom(5);

	switch (randomNum)
	{
	case 0:
		attack0->play();
		break;
	case 1:
		attack1->play();
		break;
	case 2:
		attack2->play();
		break;
	case 3:
		attack3->play();
		break;
	case 4:
		attack4->play();
		break;
	default:
		break;
	}
}


void SoundManager::playDep() {
	randomNum = pickRandom(3);

	switch (randomNum)
	{
	case 0:
		dep0->play();
		break;
	case 1:
		dep1->play();
		break;
	case 2:
		dep2->play();
		break;
	default:
		break;
	}
}

void SoundManager::playHeartattack() {
	randomNum = pickRandom(3);

	switch (randomNum)
	{
	case 0:
		heartattack0->play();
		break;
	case 1:
		heartattack1->play();
		break;
	case 2:
		heartattack2->play();
		break;
	case 3:
		heartattack4->play();
		break;
	case 4:
		heartattack5->play();
		break;
	case 5:
		heartattack5->play();
		break;
	default:
		break;
	}
}


void SoundManager::playTutorial() {

	switch (tutorialNum)
	{
	case 0:
		tutorial0->play(0, 7);
		break;
	case 1:
		tutorial0->play(0, 7);
		break;
	case 2:
		tutorial1->play(0, 7);
		break;
	case 3:
		tutorial2->play(0, 7);
		break;
	case 4:
		tutorial3->play(0, 7);
		break;
	case 5:
		tutorial4->play(0, 7);
		break;
	case 6:
		tutorial5->play(0, 7);
		break;
	case 7:
		tutorial6->play(0, 7);
		break;
	case 8:
		tutorial7->play(0, 7);
		break;
	case 9:
		tutorial8->play(0, 7);
		break;
	case 10:
		tutorial9->play(0, 7);
		break;
	case 11:
		tutorial10->play(0, 7);
		break;
	default:
		break;
	}

	tutorialNum++;	//La proxima vez se reproducira el siguiente dialogo
}


void SoundManager::playPageSkip() {

	randomNum = pickRandom(2);

	switch (randomNum)
	{
	case 0:
		pageSkip0->play();
		break;
	case 1:
		pageSkip0->play();
		break;
	default:
		break;
	}
}

void SoundManager::playTransition() {

	switch (transitionNum)
	{
	case 0:
		transition0->play(0, 7);
		break;
	case 1:
		transition1->play(0, 7);
		break;
	case 2:
		transition2->play(0, 7);
		break;
	case 3:
		transition3->play(0, 7);
		break;
	case 4:
		transition4->play(0, 7);
		break;
	case 5:
		transition5->play(0, 7);
		break;
	case 6:
		transition6->play(0, 7);
		break;
	case 7:
		transition7->play(0, 7);
		break;
	case 8:
		transition8->play(0, 7);
		break;
	case 9:
		transition9->play(0, 7);
		break;
	case 10:
		transition10->play(0, 7);
		break;
	default:
		break;
	}

	transitionNum++;	//La proxima vez se reproducira el siguiente dialogo
}

void SoundManager::playKetaSpecial() {
	randomNum = pickRandom(5);

	switch (randomNum)
	{
	case 0:
		ketaSpecial0->play();
		break;
	case 1:
		ketaSpecial1->play();
		break;
	case 2:
		ketaSpecial2->play();
		break;
	case 3:
		ketaSpecial3->play();
		break;
	case 4:
		ketaSpecial4->play();
		break;
	default:
		break;
	}
}

void SoundManager::playMonchiSpecial() {
	randomNum = pickRandom(5);

	switch (randomNum)
	{
	case 0:
		monchiSpecial0->play();
		break;
	case 1:
		monchiSpecial1->play();
		break;
	case 2:
		monchiSpecial2->play();
		break;
	case 3:
		monchiSpecial3->play();
		break;
	case 4:
		monchiSpecial4->play();
		break;
	default:
		break;
	}
}

void SoundManager::playCanelonSpecial() {

	switch (canelonState)
	{
	case 0:
		canelonSpecial0->play();
		break;
	case 1:
		canelonSpecial1->play();
		break;
	default:
		break;
	}
	canelonState++;
	if (canelonState > 1)
		canelonState = 0;
}

void SoundManager::playCar() {
	randomNum = pickRandom(3);

	switch (randomNum)
	{
	case 0:
		car0->play();
		break;
	case 1:
		car1->play();
		break;
	case 2:
		car2->play();
		break;
	default:
		break;
	}
}


void SoundManager::playEat() {

	randomNum = pickRandom(4);

	switch (randomNum)
	{
	case 0:
		eat0->play();
		break;
	case 1:
		eat1->play();
		break;
	case 2:
		eat2->play();
		break;
	case 3:
		eat3->play();
		break;
	default:
		break;
	}
}

void SoundManager::playsoldierDep() {

	randomNum = pickRandom(4);

	switch (randomNum)
	{
	case 0:
		soldierDep0->play();
		break;
	case 1:
		soldierDep1->play();
		break;
	case 2:
		soldierDep2->play();
		break;
	case 3:
		soldierDep3->play();
		break;
	default:
		break;
	}
}


void SoundManager::playHandPunch() {
	randomNum = pickRandom(2);
	switch (randomNum)
	{
	case 0:
		heavyPunch0->play();
		break;
	case 1:
		heavyPunch1->play();
		break;
	default:
		break;
	}
}