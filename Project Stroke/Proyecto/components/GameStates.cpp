#include "GameStates.h"
#include "SoundManager.h"
void GameStates::init() {
	state_ = MAINMENU;
	//state_ = CONTROLS;
	//state_ = SELECTION;	

}

void GameStates::setState(States state) {
	if (state == RUNNING)
		sdlutils().hideCursor();
	else
		sdlutils().showCursor();

	lastState_ = state_;
	state_ = state;

}

GameStates::States GameStates::getState() {
	return state_;
}

void GameStates::goBack() {
	state_ = lastState_;
}