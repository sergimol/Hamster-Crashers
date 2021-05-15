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

	dialogue0 = &sdlutils().soundEffects().at("heartattack2");;
	dialogue1 = &sdlutils().soundEffects().at("heartattack2");
	dialogue2 = &sdlutils().soundEffects().at("heartattack2");
	dialogue3 = &sdlutils().soundEffects().at("heartattack2");
	dialogue4 = &sdlutils().soundEffects().at("heartattack2");
	dialogue5 = &sdlutils().soundEffects().at("heartattack2");
	dialogue6 = &sdlutils().soundEffects().at("heartattack2");
	dialogue7 = &sdlutils().soundEffects().at("heartattack2");
	dialogue8 = &sdlutils().soundEffects().at("heartattack2");
	dialogue9 = &sdlutils().soundEffects().at("heartattack2");
	dialogue10 = &sdlutils().soundEffects().at("heartattack2");
	dialogue11 = &sdlutils().soundEffects().at("heartattack2");
	dialogue12 = &sdlutils().soundEffects().at("heartattack2");
	dialogue13 = &sdlutils().soundEffects().at("heartattack2");
	dialogue14 = &sdlutils().soundEffects().at("heartattack2");
	dialogue15 = &sdlutils().soundEffects().at("heartattack2");
	dialogue16 = &sdlutils().soundEffects().at("heartattack2");
	dialogue17 = &sdlutils().soundEffects().at("heartattack2");
	dialogue18 = &sdlutils().soundEffects().at("heartattack2");
	dialogue19 = &sdlutils().soundEffects().at("heartattack2");
	dialogue20 = &sdlutils().soundEffects().at("heartattack2");
	dialogue21 = &sdlutils().soundEffects().at("heartattack2");
	dialogue22 = &sdlutils().soundEffects().at("heartattack2");
	dialogue23 = &sdlutils().soundEffects().at("heartattack2");
	dialogue24 = &sdlutils().soundEffects().at("heartattack2");
	dialogue25 = &sdlutils().soundEffects().at("heartattack2");
	dialogue26 = &sdlutils().soundEffects().at("heartattack2");
	dialogue27 = &sdlutils().soundEffects().at("heartattack2");
	dialogue28 = &sdlutils().soundEffects().at("heartattack2");
	dialogue29 = &sdlutils().soundEffects().at("heartattack2");
	dialogue30 = &sdlutils().soundEffects().at("heartattack2");

	mainTheme = &sdlutils().soundEffects().at("mainTheme");

	setVolumeChannels();
	//mainTheme->play(200, musics);
}

void SoundManager::setVolumeChannels() {
	Mix_Volume(lighthits, generalFXvol * fxVol_);
	Mix_Volume(stronghits, initStrongVol * fxVol_);
	Mix_Volume(attacks, generalFXvol * fxVol_);
	Mix_Volume(deps, generalFXvol * fxVol_);
	Mix_Volume(heartattacks, generalFXvol * fxVol_);
	Mix_Volume(musics, initMusicVol * musicVol_);

	Mix_Volume(subtitles, initSubtitleVol * musicVol_);
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
		lighthit();
	}
	else if (soundName == "stronghit") {
		stronghit();
	}
	else if (soundName == "attack") {
		attack();
	}
	else if (soundName == "dep") {
		dep();
	}
	else if (soundName == "heartattack") {
		heartattack();
	}
	else if (soundName == "subtitle") {
		subtitle();
	}
}

void SoundManager::lighthit() {
	randomNum = pickRandom(11);
	switch (randomNum)
	{
	case 0:
		light0->play(0, lighthits);
		break;
	case 1:
		light1->play(0, lighthits);
		break;
	case 2:
		light2->play(0, lighthits);
		break;
	case 3:
		light3->play(0, lighthits);
		break;
	case 4:
		light4->play(0, lighthits);
		break;
	case 5:
		light5->play(0, lighthits);
		break;
	case 6:
		light6->play(0, lighthits);
		break;
	case 7:
		light7->play(0, lighthits);
		break;
	case 8:
		light8->play(0, lighthits);
		break;
	case 9:
		light9->play(0, lighthits);
		break;
	case 10:
		light10->play(0, lighthits);
		break;
	default:
		break;
	}
}

void SoundManager::stronghit() {
	randomNum = pickRandom(3);

	switch (randomNum)
	{
	case 0:
		strong0->play(0, stronghits);
		break;
	case 1:
		strong1->play(0, stronghits);
		break;
	case 2:
		strong2->play(0, stronghits);
		break;
	default:
		break;
	}
}

void SoundManager::attack() {
	randomNum = pickRandom(5);

	switch (randomNum)
	{
	case 0:
		attack0->play(0, attacks);
		break;
	case 1:
		attack1->play(0, attacks);
		break;
	case 2:
		attack2->play(0, attacks);
		break;
	case 3:
		attack3->play(0, attacks);
		break;
	case 4:
		attack4->play(0, attacks);
		break;
	default:
		break;
	}
}


void SoundManager::dep() {
	randomNum = pickRandom(3);

	switch (randomNum)
	{
	case 0:
		dep0->play(0, deps);
		break;
	case 1:
		dep1->play(0, deps);
		break;
	case 2:
		dep2->play(0, deps);
		break;
	default:
		break;
	}
}

void SoundManager::heartattack() {
	randomNum = pickRandom(3);

	switch (randomNum)
	{
	case 0:
		heartattack0->play(0, heartattacks);
		break;
	case 1:
		heartattack1->play(0, heartattacks);
		break;
	case 2:
		heartattack2->play(0, heartattacks);
		break;
	default:
		break;
	}
}




int SoundManager::pickRandom(int max) {
	int randomNum;
	randomNum = sdlutils().rand().nextInt(0, max);
	return randomNum;
}

void SoundManager::subtitle() {

	switch (dialogueNum)
	{
	case 0:
		dialogue0->play(0, subtitles);
		break;
	case 1:
		dialogue1->play(0, subtitles);
		break;
	case 2:
		dialogue2->play(0, subtitles);
		break;
	case 3:
		dialogue3->play(0, subtitles);
		break;
	case 4:
		dialogue4->play(0, subtitles);
		break;
	case 5:
		dialogue5->play(0, subtitles);
		break;
	case 6:
		dialogue6->play(0, subtitles);
		break;
	case 7:
		dialogue7->play(0, subtitles);
		break;
	case 8:
		dialogue8->play(0, subtitles);
		break;
	case 9:
		dialogue9->play(0, subtitles);
		break;
	case 10:
		dialogue10->play(0, subtitles);
		break;
	default:
		break;
	}

	dialogueNum++;	//La proxima vez se reproducira el siguiente dialogo
}