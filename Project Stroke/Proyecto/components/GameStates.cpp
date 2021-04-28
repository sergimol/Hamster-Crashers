#include "GameStates.h"

void GameStates::init() {
	//state_ = RUNNING;
	state_ = MAINMENU;	
}

void GameStates::setState(States state) {
	state_ = state;
}

GameStates::States GameStates::getState() {
	return state_;
}