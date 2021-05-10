#include "MenuButton.h"
#include "MenuButtonManager.h"
#include "Transition.h"
#include "MenuControlHandler.h"
#include "SoundManager.h"

MenuButton::MenuButton(std::string n, Vector2D position, int stateNum) :
	buttonName_(n),
	renderCoords_(position),
	stateNumber_(stateNum)
{
	button_ = &sdlutils().images().at(buttonName_ + "Button");
	buttonEnter_ = &sdlutils().images().at(buttonName_ + "ButtonEnter");

	dest_.x = renderCoords_.getX();
	dest_.y = renderCoords_.getY();
	dest_.w = button_->width();
	dest_.h = button_->height();
}

void MenuButton::init() {
	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
}

void MenuButton::render() {
	if (state_->getState() == stateNumber_) {

		/*if (!buttonSelected_)
		mainText = button_;*/

		//Renderizamos el boton
		if (!buttonSelected_)
			button_->render(dest_);
		else
			buttonEnter_->render(dest_);

			//buttonSelected_ = false; //Despues de renderizar, devolvemos el estado normal
	}
}

void MenuButton::selected() {
	buttonSelected_ = true;
}

void MenuButton::exited() {
	buttonSelected_ = false;
}

void LocalButton::pressed() {
	sdlutils().setHamstersToChoose(1);
	state_->setState(GameStates::HAMSTERSELECTION);
	entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuButtonManager>()->onResume();
	//entity_->getMngr()->getHandler<MainMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
}

void MultiplayerButton::pressed() {
	state_->setState(GameStates::PLAYERSELECTION);
	entity_->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuButtonManager>()->onResume();
	//entity_->getMngr()->getHandler<MainMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
}

void ResumeButton::pressed() {
	state_->setState(GameStates::RUNNING);
	//entity_->getMngr()->getHandler<PauseMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
}

void QuitButton::pressed() {
	ih().startQuitEvent();
}

void OptionsButton::pressed() {
	std::cout << "options\n";
}

void PlayerNumberButton::pressed() {
	int pNumber = 0;
	if (buttonName_ == "twoPlayers")
		pNumber = 2;
	else if (buttonName_ == "threePlayers")
		pNumber = 3;
	else if (buttonName_ == "fourPlayers")
		pNumber = 4;

	sdlutils().setHamstersToChoose(pNumber);
	state_->setState(GameStates::HAMSTERSELECTION);
	//entity_->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
}

void HamsterSelectButton::pressed() {
	auto* mapa = entity_->getMngr()->getHandler<Map>();
	mapa->getComponent<MapMngr>()->addHamster(buttonName_);

	sdlutils().setHamstersToChoose(sdlutils().hamstersToChoose() - 1);
	sdlutils().setHamstersChosen(sdlutils().hamstersChosen() + 1);

	if (sdlutils().hamstersToChoose() <= 0) {
		mapa->getComponent<MapMngr>()->loadNewMap("resources/images/tiled/Lvl1Javi.tmx");
		state_->setState(GameStates::RUNNING);
	}
	//entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
}

void MusicLowButton::pressed() {
	auto musicMaster = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
	musicMaster->lowVolume(true);	//true es el volumen de la musica, false el de fx
}

void MusicUpButton::pressed() {
	auto musicMaster = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
	musicMaster->upVolume(true);	//true es el volumen de la musica, false el de fx
}

void FxLowButton::pressed() {
	auto musicMaster = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
	musicMaster->lowVolume(false);	//true es el volumen de la musica, false el de fx
}

void FxUpButton::pressed() {
	auto musicMaster = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
	musicMaster->upVolume(false);	//true es el volumen de la musica, false el de fx
}



//
//void MenuButton::pressed() {
//	// Botones con la misma funcionalidad están separados porque en el futuro funcionarán diferente
//	 if (buttonName_ == "1920x1080") {
//	//Cambiamos la resolucion
//	sdlutils().setWidth(1920);
//	sdlutils().setHeight(1080);
//
//	//Y cambiamos la ventana
//	SDL_SetWindowSize(sdlutils().window(), sdlutils().width(), sdlutils().height());
//	SDL_RenderSetScale(sdlutils().renderer(), sdlutils().width() / 1920.0f, sdlutils().height() / 1080.0f);
//	}
//	else if (buttonName_ == "1280x720") {
//	//Cambiamos la resolucion
//	sdlutils().setWidth(1280);
//	sdlutils().setHeight(720);
//
//	//Y cambiamos la ventana
//	SDL_SetWindowSize(sdlutils().window(), sdlutils().width(), sdlutils().height());
//	SDL_RenderSetScale(sdlutils().renderer(), sdlutils().width() / 1920.0f, sdlutils().height() / 1080.0f);
//	}
//	else if (buttonName_ == "640x480") {
//	//Cambiamos la resolucion
//	sdlutils().setWidth(640);
//	sdlutils().setHeight(480);
//
//	//Y cambiamos la ventana
//	SDL_SetWindowSize(sdlutils().window(), sdlutils().width(), sdlutils().height());
//	SDL_RenderSetScale(sdlutils().renderer(), sdlutils().width() / 1920.0f, sdlutils().height() / 1080.0f);
//	}
//}