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

	catMeowStatic = &sdlutils().soundEffects().at("catMeow");
	catMeowAttack = &sdlutils().soundEffects().at("catMeowAttack");
	catMeowInit = &sdlutils().soundEffects().at("catMeowInit");
	catMeowWalking = &sdlutils().soundEffects().at("catWalking");

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

	mainTheme = &sdlutils().soundEffects().at("mainTheme");
	birds = &sdlutils().soundEffects().at("birds");

	eat0 = &sdlutils().soundEffects().at("eat0");
	eat1 = &sdlutils().soundEffects().at("eat1");

	soldierDep0 = &sdlutils().soundEffects().at("soldierDep0");
	soldierDep1 = &sdlutils().soundEffects().at("soldierDep1");
	soldierDep2 = &sdlutils().soundEffects().at("soldierDep2");
	soldierDep3 = &sdlutils().soundEffects().at("soldierDep3");

	trainBackground = &sdlutils().soundEffects().at("trainBackground");;
	trainPipi = &sdlutils().soundEffects().at("trainPipi");
	trainAlto = &sdlutils().soundEffects().at("trainAlto");

	transition0 = &sdlutils().soundEffects().at("transition0");
	transition1 = &sdlutils().soundEffects().at("transition1");

	trapKitchen = &sdlutils().soundEffects().at("trapKitchen");

	dialogue0 = &sdlutils().soundEffects().at("tutorial0");
	dialogue1 = &sdlutils().soundEffects().at("tutorial1");
	dialogue2 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue3 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue4 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue5 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue6 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue7 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue8 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue9 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue10 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue11 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue12 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue13 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue14 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue15 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue16 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue17 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue18 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue19 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue20 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue21 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue22 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue23 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue24 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue25 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue26 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue27 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue28 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue29 = &sdlutils().soundEffects().at("catMeowInit");
	dialogue30 = &sdlutils().soundEffects().at("catMeowInit");

	setVolumeChannels();
	//mainTheme->play(200, musics);
	Mix_AllocateChannels(6);
}

void SoundManager::setVolumeChannels() {
	//Hits
	Mix_Volume(lighthitsChannel, generalFXvol * fxVol_);
	Mix_Volume(stronghitsChannel, initStrongVol * fxVol_);

	//Attack
	Mix_Volume(attacksChannel, generalFXvol * fxVol_);

	//Dep
	Mix_Volume(depsChannel, generalFXvol * fxVol_);

	//HeartAttack
	Mix_Volume(heartattacksChannel, generalFXvol * fxVol_);

	//Specials attack
	Mix_Volume(ketaSpecialChannel, ketaSpecialVol * generalFXvol);
	Mix_Volume(monchiSpecialChannel, monchiSpecialVol * generalFXvol);
	Mix_Volume(canelonSpecialChannel, canelonSpecialVol * generalFXvol);

	//Car
	Mix_Volume(carChannel, carVol * generalFXvol);

	//Boss
	Mix_Volume(catChannel, initCatVol * generalFXvol);

	//Button
	Mix_Volume(buttonChannel, buttonVol * generalFXvol);

	//Music
	Mix_Volume(musicsChannel, initMusicVol * musicVol_);
	//Birds
	Mix_Volume(birdsChannel, initBirdsVol * musicVol_);

	//Eat Item
	Mix_Volume(EatChannel, initEatVol * generalFXvol);

	//Soldier dep
	Mix_Volume(soldierDepChannel, generalFXvol * generalFXvol);

	//Train 
	Mix_Volume(trainBackgroundChannel, inittrainBackgroundVol * generalFXvol);
	
	//Transition
	Mix_Volume(transitionChannel, inittransitionVol * generalFXvol);

	//Traps
	Mix_Volume(trapKitchenChannel, inittrapKitchenVol * generalFXvol);

	//Subtitles
	Mix_Volume(subtitlesChannel, initSubtitleVol * musicVol_);
}

void SoundManager::lowVolume(bool musicChannel) {
	if (musicChannel)
		musicVol_ = musicVol_ - 0.2f;

	else
		fxVol_ = fxVol_ - 0.2f;

	setVolumeChannels();
}

void SoundManager::upVolume(bool musicChannel) {
	if (musicChannel)
		musicVol_ = musicVol_ + 0.2f;

	else
		fxVol_ = fxVol_ + 0.2f;

	setVolumeChannels();
}

bool SoundManager::emptyChannel(int channel) {
	if (Mix_Playing(channel) == 0) {
		return true;
	}
	else
		return false;
}


void SoundManager::play(std::string soundName) {
	if (soundName == "lighthit") {
		playLighthit();
	}
	else if (soundName == "stronghit") {
		playStronghit();
	}
	else if (soundName == "attack") {
		playAttack();
	}
	else if (soundName == "dep") {
		playDep();
	}

	else if (soundName == "heartattack") {
		playHeartattack();
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

	else if (soundName == "catMeowInit") {
		catMeowInit->play(0, catChannel);
	}
	else if (soundName == "catMeowStatic") {
		catMeowStatic->play(0, catChannel);
	}
	else if (soundName == "catMeowAttack") {
		catMeowAttack->play(0, catChannel);
	}
	else if (soundName == "catMeowWalking") {
		catMeowWalking->play(0, catChannel);
	}

	else if (soundName == "button") {
		button1->play(0, buttonChannel);
	}

	else if (soundName == "subtitle") {
		playSubtitle();
	}
	else if (soundName == "birds") {
		birds->play(200, birdsChannel);
	}
	
	else if (soundName == "eatItem") {
		playEat();
	}

	else if (soundName == "soldierDep") {
		playsoldierDep();
	}

	else if (soundName == "trainBackground") {

		trainBackground->play(200, trainBackgroundChannel);
	}
	else if (soundName == "trainPipi") {

		trainPipi->play(0, trainBackgroundChannel);
	}
	else if (soundName == "trainPasoalto") {

		trainAlto->play(0, trainBackgroundChannel);
	}

	else if (soundName == "transition") {
		playtransition();
	}
	else if (soundName == "trapKitchen") {
		trapKitchen->play(0, trapKitchenChannel);
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
		light0->play(0, lighthitsChannel);
		break;
	case 1:
		light1->play(0, lighthitsChannel);
		break;
	case 2:
		light2->play(0, lighthitsChannel);
		break;
	case 3:
		light3->play(0, lighthitsChannel);
		break;
	case 4:
		light4->play(0, lighthitsChannel);
		break;
	case 5:
		light5->play(0, lighthitsChannel);
		break;
	case 6:
		light6->play(0, lighthitsChannel);
		break;
	case 7:
		light7->play(0, lighthitsChannel);
		break;
	case 8:
		light8->play(0, lighthitsChannel);
		break;
	case 9:
		light9->play(0, lighthitsChannel);
		break;
	case 10:
		light10->play(0, lighthitsChannel);
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
		strong0->play(0, stronghitsChannel);
		break;
	case 1:
		strong1->play(0, stronghitsChannel);
		break;
	case 2:
		strong2->play(0, stronghitsChannel);
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
		attack0->play(0, attacksChannel);
		break;
	case 1:
		attack1->play(0, attacksChannel);
		break;
	case 2:
		attack2->play(0, attacksChannel);
		break;
	case 3:
		attack3->play(0, attacksChannel);
		break;
	case 4:
		attack4->play(0, attacksChannel);
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
		dep0->play(0, depsChannel);
		break;
	case 1:
		dep1->play(0, depsChannel);
		break;
	case 2:
		dep2->play(0, depsChannel);
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
		heartattack0->play(0, heartattacksChannel);
		break;
	case 1:
		heartattack1->play(0, heartattacksChannel);
		break;
	case 2:
		heartattack2->play(0, heartattacksChannel);
		break;
	case 3:
		heartattack4->play(0, heartattacksChannel);
		break;
	case 4:
		heartattack5->play(0, heartattacksChannel);
		break;
	case 5:
		heartattack5->play(0, heartattacksChannel);
		break;
	default:
		break;
	}
}


void SoundManager::playSubtitle() {

	switch (dialogueNum)
	{
	case 0:
		dialogue0->play(0, subtitlesChannel);
		break;
	case 1:
		dialogue1->play(0, subtitlesChannel);
		break;
	case 2:
		dialogue2->play(0, subtitlesChannel);
		break;
	case 3:
		dialogue3->play(0, subtitlesChannel);
		break;
	case 4:
		dialogue4->play(0, subtitlesChannel);
		break;
	case 5:
		dialogue5->play(0, subtitlesChannel);
		break;
	case 6:
		dialogue6->play(0, subtitlesChannel);
		break;
	case 7:
		dialogue7->play(0, subtitlesChannel);
		break;
	case 8:
		dialogue8->play(0, subtitlesChannel);
		break;
	case 9:
		dialogue9->play(0, subtitlesChannel);
		break;
	case 10:
		dialogue10->play(0, subtitlesChannel);
		break;
	default:
		break;
	}

	dialogueNum++;	//La proxima vez se reproducira el siguiente dialogo
}

void SoundManager::playKetaSpecial() {
	randomNum = pickRandom(5);

	switch (randomNum)
	{
	case 0:
		ketaSpecial0->play(0, ketaSpecialChannel);
		break;
	case 1:
		ketaSpecial1->play(0, ketaSpecialChannel);
		break;
	case 2:
		ketaSpecial2->play(0, ketaSpecialChannel);
		break;
	case 3:
		ketaSpecial3->play(0, ketaSpecialChannel);
		break;
	case 4:
		ketaSpecial4->play(0, ketaSpecialChannel);
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
		monchiSpecial0->play(0, monchiSpecialChannel);
		break;
	case 1:
		monchiSpecial1->play(0, monchiSpecialChannel);
		break;
	case 2:
		monchiSpecial2->play(0, monchiSpecialChannel);
		break;
	case 3:
		monchiSpecial3->play(0, monchiSpecialChannel);
		break;
	case 4:
		monchiSpecial4->play(0, monchiSpecialChannel);
		break;
	default:
		break;
	}
}

void SoundManager::playCanelonSpecial() {

	switch (canelonState)
	{
	case 0:
		canelonSpecial0->play(0, canelonSpecialChannel);
		break;
	case 1:
		canelonSpecial1->play(0, canelonSpecialChannel);
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
		car0->play(0, carChannel);
		break;
	case 1:
		car1->play(0, carChannel);
		break;
	case 2:
		car2->play(0, carChannel);
		break;
	default:
		break;
	}
}


void SoundManager::playEat() {

	randomNum = pickRandom(2);

	switch (randomNum)
	{
	case 0:
		eat0->play(0, EatChannel);
		break;
	case 1:
		eat0->play(0, EatChannel);
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
		soldierDep0->play(0, soldierDepChannel);
		break;
	case 1:
		soldierDep1->play(0, soldierDepChannel);
		break;
	case 2:
		soldierDep2->play(0, soldierDepChannel);
		break;
	case 3:
		soldierDep3->play(0, soldierDepChannel);
		break;
	default:
		break;
	}
}

void SoundManager::playtransition() {

	randomNum = pickRandom(4);

	switch (randomNum)
	{
	case 0:
		transition0->play(0, transitionChannel);
		break;
	case 1:
		transition1->play(0, transitionChannel);
		break;
	default:
		break;
	}
}