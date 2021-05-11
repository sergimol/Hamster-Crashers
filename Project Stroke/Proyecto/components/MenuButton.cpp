#include "MenuButton.h"
#include "MenuButtonManager.h"
#include "Transition.h"
#include "MenuControlHandler.h"


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

		//buttonSelected_ = false;	//Despues de renderizar, devolvemos el estado normal
	}
}

void MenuButton::selected() {
	buttonSelected_ = true;
	/*if (buttonName_ == "local") {
		std::cout << "local\n";
	}
	else if (buttonName_ == "online") {
		std::cout << "online\n";
	}
	else if (buttonName_ == "options") {
		std::cout << "options\n";
	}
	else if (buttonName_ == "quit") {
		std::cout << "quit\n";
	}
	else if (buttonName_ == "sardinilla") {
		std::cout << "sardinilla\n";
	}
	else if (buttonName_ == "keta") {
		std::cout << "keta\n";
	}
	else if (buttonName_ == "monchi") {
		std::cout << "monchi\n";
	}
	else if (buttonName_ == "canelon") {
		std::cout << "canelon\n";
	}*/
}

void MenuButton::exited() {
	buttonSelected_ = false;
}

void MenuButton::pressed() {
	// Botones con la misma funcionalidad est�n separados porque en el futuro funcionar�n diferente
	if (buttonName_ == "local") {
		sdlutils().setHamstersToChoose(1);
		state_->setState(GameStates::HAMSTERSELECTION);
		entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuButtonManager>()->onResume();
		//entity_->getMngr()->getHandler<MainMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "online") {
		state_->setState(GameStates::PLAYERSELECTION);
		entity_->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuButtonManager>()->onResume();
		//entity_->getMngr()->getHandler<MainMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "resume") {
		state_->setState(GameStates::RUNNING);
		//entity_->getMngr()->getHandler<PauseMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "twoPlayers") {
		sdlutils().setHamstersToChoose(2);
		state_->setState(GameStates::HAMSTERSELECTION);
		//entity_->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "threePlayers") {
		sdlutils().setHamstersToChoose(3);
		state_->setState(GameStates::HAMSTERSELECTION);
		//->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "fourPlayers") {
		sdlutils().setHamstersToChoose(4);
		state_->setState(GameStates::HAMSTERSELECTION);
		//entity_->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "options") {
		std::cout << "options\n";
	}
	else if (buttonName_ == "quit") {
		ih().startQuitEvent();
	}
	else if (buttonName_ == "sardinilla" || buttonName_ == "keta" || buttonName_ == "monchi" || buttonName_ == "canelon") {
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
	else if (buttonName_ == "1920x1080") {
		//Cambiamos la resolucion
		sdlutils().setWidth(1920);
		sdlutils().setHeight(1080);

		//Y cambiamos la ventana
		SDL_SetWindowSize(sdlutils().window(), sdlutils().width(), sdlutils().height());
		SDL_RenderSetScale(sdlutils().renderer(), sdlutils().width() / 1920.0f, sdlutils().height() / 1080.0f);
	}
	else if (buttonName_ == "1280x720") {
		//Cambiamos la resolucion
		sdlutils().setWidth(1280);
		sdlutils().setHeight(720);

		//Y cambiamos la ventana
		SDL_SetWindowSize(sdlutils().window(), sdlutils().width(), sdlutils().height());
		SDL_RenderSetScale(sdlutils().renderer(), sdlutils().width() / 1920.0f, sdlutils().height() / 1080.0f);
	}
	else if (buttonName_ == "640x480") {
		//Cambiamos la resolucion
		sdlutils().setWidth(640);
		sdlutils().setHeight(480);

		//Y cambiamos la ventana
		SDL_SetWindowSize(sdlutils().window(), sdlutils().width(), sdlutils().height());
		SDL_RenderSetScale(sdlutils().renderer(), sdlutils().width() / 1920.0f, sdlutils().height() / 1080.0f);
	}
}
