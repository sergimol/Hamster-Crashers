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

	possesion = &sdlutils().soundEffects().at("possesion");

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

	handInit0 = &sdlutils().soundEffects().at("handInit0");
	handInit1 = &sdlutils().soundEffects().at("handInit1");

	handHit0 = &sdlutils().soundEffects().at("handHit0");
	handHit1 = &sdlutils().soundEffects().at("handHit1");
	handHit2 = &sdlutils().soundEffects().at("handHit2");

	handDep = &sdlutils().soundEffects().at("handDep");
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

	trapKitchen0 = &sdlutils().soundEffects().at("trapKitchen0");
	trapKitchen1 = &sdlutils().soundEffects().at("trapKitchen1");
	trapKitchen2 = &sdlutils().soundEffects().at("trapKitchen2");

	tutorial0 = &sdlutils().soundEffects().at("tutorial0");
	tutorial1 = &sdlutils().soundEffects().at("tutorial1");
	tutorial2 = &sdlutils().soundEffects().at("tutorial2");
	tutorial3 = &sdlutils().soundEffects().at("tutorial3");
	tutorialsingle = &sdlutils().soundEffects().at("tutorial3single");

	tutorial4 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial5 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial6 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial7 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial8 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial9 = &sdlutils().soundEffects().at("catMeowInit");
	tutorial10 = &sdlutils().soundEffects().at("catMeowInit");


	transition0 = &sdlutils().soundEffects().at("transition0");
	transition1 = &sdlutils().soundEffects().at("transition1");
	transition2 = &sdlutils().soundEffects().at("transition2");
	transition3 = &sdlutils().soundEffects().at("transition3");
	transition4 = &sdlutils().soundEffects().at("transition4");
	transition5 = &sdlutils().soundEffects().at("transition5");
	transition6 = &sdlutils().soundEffects().at("transition6");
	transition7 = &sdlutils().soundEffects().at("transition7");
	transition8 = &sdlutils().soundEffects().at("transition8");
	transition9 = &sdlutils().soundEffects().at("transition9");
	transition10 = &sdlutils().soundEffects().at("transition10");
	transition11 = &sdlutils().soundEffects().at("transition11");
	transition12 = &sdlutils().soundEffects().at("transition12");
	transition13 = &sdlutils().soundEffects().at("transition13");
	transition14 = &sdlutils().soundEffects().at("transition14");
	transition15 = &sdlutils().soundEffects().at("transition15");
	transition16 = &sdlutils().soundEffects().at("transition16");
	transition17 = &sdlutils().soundEffects().at("transition17");
	transition18 = &sdlutils().soundEffects().at("transition18");
	transition19 = &sdlutils().soundEffects().at("transition19");
	transition20 = &sdlutils().soundEffects().at("transition20");
	transition21 = &sdlutils().soundEffects().at("transition21");
	transition22 = &sdlutils().soundEffects().at("transition22");
	transition23 = &sdlutils().soundEffects().at("transition23");

	page0 = &sdlutils().soundEffects().at("page0");
	page1 = &sdlutils().soundEffects().at("page1");
	page2 = &sdlutils().soundEffects().at("page2");
	page3 = &sdlutils().soundEffects().at("page3");
	page4 = &sdlutils().soundEffects().at("page4");

	microBep = &sdlutils().soundEffects().at("microwaveBep");
	microExplosion = &sdlutils().soundEffects().at("microwaveExplosion");
	microStatic = &sdlutils().soundEffects().at("microwaveStatic");
	microTiktak = &sdlutils().soundEffects().at("tiktak");


	AngelAttack0 = &sdlutils().soundEffects().at("AngelAttack0");
	AngelAttack1 = &sdlutils().soundEffects().at("AngelAttack1");
	AngelAttack2 = &sdlutils().soundEffects().at("AngelAttack2");

	AngelStrongAttack3 = &sdlutils().soundEffects().at("AngelStrongAttack3");
	AngelStrongAttack4 = &sdlutils().soundEffects().at("AngelStrongAttack4");
	AngelStrongAttack5 = &sdlutils().soundEffects().at("AngelStrongAttack5");

	AngelHit0 = &sdlutils().soundEffects().at("AngelDamage0");
	AngelHit1 = &sdlutils().soundEffects().at("AngelDamage1");
	AngelHit2 = &sdlutils().soundEffects().at("AngelDamage2");
	AngelHit3 = &sdlutils().soundEffects().at("AngelDamage3");

	AngelDep = &sdlutils().soundEffects().at("Angeldep");
	AngelUlti = &sdlutils().soundEffects().at("angelUlti");

	Vector2D vol = sdlutils().volumes();
	musicVol_ = vol.getX();
	fxVol_ = vol.getY();

	Mix_AllocateChannels(16);
}

void SoundManager::resetNumInts() {
	randomNum = 0;
	canelonState = 0;
	canelonState = 0;
	buttonState = 0;
	tutorialNum = 0;
	transitionNum = 0;
}

void SoundManager::StopTutorial() {
	Mix_HaltChannel(7);
}

void SoundManager::StopBossSounds() {
	Mix_HaltChannel(6);
	Mix_HaltChannel(5);
}

void SoundManager::lowVolume(bool musicChannel) {
	if (musicVol_ > 0 && fxVol_ > 0) {
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
	}

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

}

bool SoundManager::emptyChannel() {
	if (!Mix_Playing(7)) {
		return true;
	}
	else
		return false;
}

void SoundManager::refreshMusicVol() {
	HamstersMainThemev2->setMusicVolume(musicVol_ * initMusicVol);
	Nivel1GameVersion->setMusicVolume(musicVol_ * initMusicVol);
	Nivel1Boss1_0->setMusicVolume(musicVol_ * initMusicVol);
	HamstersNivel2GameVersion->setMusicVolume(musicVol_ * initMusicVol);
	HamstersNivel2_Boss160bpm->setMusicVolume(musicVol_ * initMusicVol);
	HamstersNivel4_Boss2->setMusicVolume(musicVol_ * initMusicVol);
	HamstersNivel4GameVersion->setMusicVolume(musicVol_ * initMusicVol);
}

void SoundManager::play(std::string soundName) {
	//Golpe
	if (soundName == "lighthit") {
		//Golpe
		light0->setChannelVolume(fxVol_ * initLightVol);
		playLighthit();
	}
	//Golpe Fuerte
	else if (soundName == "stronghit") {
		//Golpe Fuerte
		strong0->setChannelVolume(fxVol_ * initStrongVol);
		playStronghit();
	}
	//Ataque (whoosh)
	else if (soundName == "attack") {
		//Ataque (whoosh)
		attack0->setChannelVolume(fxVol_ * initAttackVol);
		playAttack();
	}
	//Muerte
	else if (soundName == "dep") {
		//Muerte
		dep0->setChannelVolume(fxVol_ * initDepVol);
		playDep();
	}
	//Ataque corazon
	else if (soundName == "heartattack") {
		//Ataque corazon
		heartattack0->setChannelVolume(fxVol_ * initHeartAttackVol);
		playHeartattack();
	}

	//Especiales Hamsters
	else if (soundName == "sardinillaSpecial") {
		//Especial Sardinilla
		sardinillaSpecial0->setChannelVolume(fxVol_ * sardinillaSpecialVol);
		sardinillaSpecial0->play();
	}
	else if (soundName == "ketaSpecial") {
		//Especial Keta
		ketaSpecial0->setChannelVolume(fxVol_ * ketaSpecialVol);
		playKetaSpecial();
	}
	else if (soundName == "monchiSpecial") {
		//Especial monchi
		monchiSpecial0->setChannelVolume(fxVol_ * monchiSpecialVol);
		playMonchiSpecial();
	}
	else if (soundName == "canelonSpecial") {
		//Especial canelon
		canelonSpecial0->setChannelVolume(fxVol_ * canelonSpecialVol);
		playCanelonSpecial();
	}
	//Boss Gato
	else if (soundName == "catMeowInit") {
		catMeowInit->setChannelVolume(fxVol_ * initCatVol);
		catMeowInit->play();
	}
	else if (soundName == "catMeowStatic") {
		catMeowStatic->setChannelVolume(fxVol_ * initCatVol);
		catMeowStatic->play(11, 6);
	}
	else if (soundName == "catMeowAttack") {
		catMeowAttack->setChannelVolume(fxVol_ * initCatVol);
		catMeowAttack->play();
	}
	else if (soundName == "catMeowWalking") {
		catMeowWalking->setChannelVolume(fxVol_ * initCatVol);
		catMeowWalking->play(11, 6);
	}
	else if (soundName == "catMeowSleeping") {
		catMeowSleeping->setChannelVolume(fxVol_ * initCatVol);
		catMeowSleeping->play(0, 6);
	}

	//Boss Mano
	else if (soundName == "handInit") {
		handInit0->setChannelVolume(fxVol_ * initHandVol);
		playHandInit();
	}
	else if (soundName == "handPunch") {
		heavyPunch0->setChannelVolume(fxVol_ * initHandVol);
		playHandPunch();
	}
	else if (soundName == "handHit") {
		handHit0->setChannelVolume(fxVol_ * initHandVol);
		playHandHit();
	}
	else if (soundName == "handDep") {
		handDep->setChannelVolume(fxVol_ * initHandVol);
		handDep->play();
	}

	//Boss Mono
	else if (soundName == "platillos") {
		//Boss Mono
		platillos->setChannelVolume(fxVol_ * initMonkeVol);
		platillos->play();
	}

	//Sonidos tren
	else if (soundName == "trainBackground") {
		//Sonidos tren
		trainBackground->setChannelVolume(fxVol_ * inittrainBackgroundVol);
		trainBackground->play(200, 6);
	}
	else if (soundName == "trainPipi") {
		trainPipi->setChannelVolume(fxVol_ * inittrainBackgroundVol);
		trainPipi->play();
	}
	else if (soundName == "trainPasoalto") {
		trainAlto->setChannelVolume(fxVol_ * inittrainBackgroundVol);
		trainAlto->play();
	}

	//Enemigo coche
	else if (soundName == "coche") {
		//Coche
		car0->setChannelVolume(fxVol_ * carVol);
		playCar();
	}

	//Muerte soldados
	else if (soundName == "soldierDep") {
		//Muerte soldados
		soldierDep0->setChannelVolume(fxVol_ * initsoldierDepVol);
		playsoldierDep();
	}

	//Juego reanimar, tecla correcta o fallida
	else if (soundName == "rightNote") {
		rightNote->setChannelVolume(fxVol_ * notesReanimVol);
		rightNote->play();
	}
	else if (soundName == "wrongNote") {
		wrongNote->setChannelVolume(fxVol_ * notesReanimVol);
		wrongNote->play();
	}
	//Posesion hamster
	else if (soundName == "possesion") {
		//Posesion hamster
		possesion->setChannelVolume(fxVol_ * possesionVol);
		possesion->play();
	}

	//Botones UI
	else if (soundName == "button") {
		//Botones UI
		button0->setChannelVolume(fxVol_ * buttonVol);
		button1->play();
	}


	else if (soundName == "birds") {
		// sonidos ambiente
		birds->setChannelVolume(fxVol_ * initBirdsVol);
		birds->play(0, 5);
	}


	//Recoger items
	else if (soundName == "eatItem") {
		//Recoger items
		eat0->setChannelVolume(fxVol_ * initEatVol);
		playEat();
	}

	//Transiciones
	else if (soundName == "transition") {
		transition0->setChannelVolume(fxVol_ * initTransitionVol);
		playTransition();
	}
	else if (soundName == "nextPage") {
		//PageNext
		pageSkip0->setChannelVolume(fxVol_ * pageSkipVol);
		playPageSkip();
	}
	else if (soundName == "tutorial") {
		//Dialogos Angel
		tutorial0->setChannelVolume(fxVol_ * initTutorialVol);
		playTutorial();
	}
	else if (soundName == "tutorialsingle") {
		tutorialsingle->play(0, 7);
	}
	else if (soundName == "stopTutorial") {
		StopTutorial();
	}

	//Trampa cocina
	else if (soundName == "trapKitchen") {
		//Trampa cocina
		trapKitchen0->setChannelVolume(fxVol_ * inittrapKitchenVol);
		playTrap();
	}


	//CANCIONES
	else if (soundName == "HamstersMainThemev2") {
		Mix_HaltMusic();
		HamstersMainThemev2->setMusicVolume(musicVol_ * initMusicVol);
		HamstersMainThemev2->play(200);
	}
	else if (soundName == "Nivel1GameVersion") {
		Mix_HaltMusic();
		Nivel1GameVersion->setMusicVolume(musicVol_ * initMusicVol);
		Nivel1GameVersion->play(200);
	}
	else if (soundName == "Nivel1Boss1_0") {
		Mix_HaltMusic();
		Nivel1Boss1_0->setMusicVolume(musicVol_ * initMusicVol);
		Nivel1Boss1_0->play(200);
	}
	else if (soundName == "HamstersNivel2GameVersion") {
		Mix_HaltMusic();
		HamstersNivel2GameVersion->setMusicVolume(musicVol_ * initMusicVol);
		HamstersNivel2GameVersion->play(200);
	}
	else if (soundName == "HamstersNivel2_Boss160bpm") {
		Mix_HaltMusic();
		HamstersNivel2_Boss160bpm->setMusicVolume(musicVol_ * initMusicVol);
		HamstersNivel2_Boss160bpm->play(200);
	}
	else if (soundName == "HamstersNivel4_Boss2") {
		Mix_HaltMusic();
		HamstersNivel4_Boss2->setMusicVolume(musicVol_ * initMusicVol);
		HamstersNivel4_Boss2->play(200);
	}
	else if (soundName == "HamstersNivel4GameVersion") {
		Mix_HaltMusic();
		HamstersNivel4GameVersion->setMusicVolume(musicVol_ * initMusicVol);
		HamstersNivel4GameVersion->play(200);
	}

	//MICROONDAS
	else if (soundName == "microwaveBep") {
		microBep->setChannelVolume(fxVol_ * initMicrowaveVol);
		microBep->play(0);
	}
	else if (soundName == "microwaveExplosion") {
		microExplosion->setChannelVolume(fxVol_ * initMicrowaveExplosionVol);
		microExplosion->play(0);
	}
	else if (soundName == "microwaveStatic") {
		microStatic->setChannelVolume(fxVol_ * initMicrowaveVol);
		microStatic->play(100, 5);
	}
	else if (soundName == "tiktak") {
		microTiktak->setChannelVolume(fxVol_ * initMicrowaveVol);
		microTiktak->play(100, 6);
	}

	//ANGEL
	else if (soundName == "angelHit") {
		AngelHit0->setChannelVolume(fxVol_ * initAngelVol);
		playAngelHit();
	}
	else if (soundName == "angelAttack") {
		AngelAttack0->setChannelVolume(fxVol_ * initAngelVol);
		playAngelAttack();
	}
	else if (soundName == "angelstrongHit") {
		AngelAttack0->setChannelVolume(fxVol_ * initAngelVol);
		playAngelStrongAttack();
	}
	else if (soundName == "angelDep") {
		AngelDep->setChannelVolume(fxVol_ * initAngelVol);
		AngelDep->play();
	}
	else if (soundName == "angelUlti") {
		AngelUlti->setChannelVolume(fxVol_ * angelUlti);
		AngelUlti->play();
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
		tutorial1->play(0, 7);
		break;
	case 2:
		tutorial2->play(0, 7);
		break;
	case 3:
		tutorial3->play(0, 7);
		break;
	case 4:
		tutorial4->play(0, 7);
		break;
	case 5:
		tutorial5->play(0, 7);
		break;
	case 6:
		tutorial6->play(0, 7);
		break;
	case 7:
		tutorial7->play(0, 7);
		break;
	case 8:
		tutorial8->play(0, 7);
		break;
	case 9:
		tutorial9->play(0, 7);
		break;
	case 10:
		tutorial10->play(0, 7);
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
		page0->play();
		break;
	case 1:
		page1->play();
		break;
	case 2:
		page2->play();
		break;
	case 3:
		page3->play();
		break;
	case 4:
		page4->play();
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
	case 11:
		transition11->play(0, 7);
		break;
	case 12:
		transition12->play(0, 7);
		break;
	case 13:
		transition13->play(0, 7);
		break;
	case 14:
		transition14->play(0, 7);
		break;
	case 15:
		transition15->play(0, 7);
		break;
	case 16:
		transition16->play(0, 7);
		break;
	case 17:
		transition17->play(0, 7);
		break;
	case 18:
		transition18->play(0, 7);
		break;
	case 19:
		transition19->play(0, 7);
		break;
	case 20:
		transition20->play(0, 7);
		break;
	case 21:
		transition21->play(0, 7);
		break;
	case 22:
		transition22->play(0, 7);
		break;
	case 23:
		transition23->play(0, 7);
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

void SoundManager::playHandInit() {
	randomNum = pickRandom(2);
	switch (randomNum)
	{
	case 0:
		handInit0->play();
		break;
	case 1:
		handInit1->play();
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

void SoundManager::playHandHit() {
	randomNum = pickRandom(3);
	switch (randomNum)
	{
	case 0:
		handHit0->play();
		break;
	case 1:
		handHit1->play();
		break;
	case 2:
		handHit2->play();
		break;
	default:
		break;
	}
}

void SoundManager::playTrap() {
	randomNum = pickRandom(3);

	switch (randomNum)
	{
	case 0:
		trapKitchen0->play();
		break;
	case 1:
		trapKitchen1->play();
		break;
	case 2:
		trapKitchen2->play();
		break;
	default:
		break;
	}
}

void SoundManager::playAngelAttack() {
	randomNum = pickRandom(3);

	switch (randomNum)
	{
	case 0:
		AngelAttack0->play();
		break;
	case 1:
		AngelAttack1->play();
		break;
	case 2:
		AngelAttack2->play();
		break;
	default:
		break;
	}
}

void SoundManager::playAngelStrongAttack() {
	randomNum = pickRandom(2);

	switch (randomNum)
	{
	case 0:
		AngelStrongAttack3->play();
		break;
	case 1:
		AngelStrongAttack4->play();
		break;
	case 2:
		AngelStrongAttack5->play();
		break;
	default:
		break;
	}
}

void SoundManager::playAngelHit() {
	randomNum = pickRandom(2);

	switch (randomNum)
	{
	case 0:
		AngelHit0->play();
		break;
	case 1:
		AngelHit1->play();
		break;
	case 2:
		AngelHit2->play();
		break;
	case 3:
		AngelHit3->play();
		break;
	default:
		break;
	}
}