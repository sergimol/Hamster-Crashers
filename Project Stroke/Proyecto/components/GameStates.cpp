#include "GameStates.h"

void GameStates::init() {
	state_ = MAINMENU;
	//state_ = CONTROLS;
	//state_ = SELECTION;	

}

void GameStates::setState(States state) {
	state_ = state;
}

GameStates::States GameStates::getState() {
	return state_;
}