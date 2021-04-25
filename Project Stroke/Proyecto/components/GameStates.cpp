#include "GameStates.h"

void GameStates::init() {
	// TEMPORAL HASTA QUE HAYA MENÚ DE INICIO
	state_ = RUNNING;
	// state_ = MAINMENU;	
}

void GameStates::setState(States state) {
	state_ = state;
}

GameStates::States GameStates::getState() {
	return state_;
}