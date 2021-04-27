#include "SoundManager.h"

void SoundManager::init() {
	hit0 = &sdlutils().soundEffects().at("hit0");
	dep0 = &sdlutils().soundEffects().at("dep0");
	dep1 = &sdlutils().soundEffects().at("dep1");

}

void SoundManager::play(std::string soundName) {
	if (soundName == "hit") {
		hit();
	}
	else if (soundName == "dep") {
		dep();
	}
}

void SoundManager::hit() {
	randomNum = pickRandom(1);

	switch (randomNum)
	{
	case 0:
		hit0->play(0, hits);
	default:
		break;
	}
}

void SoundManager::attack() {

}

void SoundManager::jump() {

}

void SoundManager::dep() {
	randomNum = pickRandom(1);

	switch (randomNum)
	{
	case 0:
		dep0->play(0, deps);
		break;
	case 1:
		dep1->play(0, deps);
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