#include "GameStates.h"

void GameStates::init() {
	state_ = MAINMENU;
	//state_ = CONTROLS;
	//state_ = SELECTION;	

}

void GameStates::setState(States state) {
	lastState_ = state_;
	state_ = state;
}

GameStates::States GameStates::getState() {
	return state_;
}

void GameStates::goBack() {
	state_ = lastState_;
}