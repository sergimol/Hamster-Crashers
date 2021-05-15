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
		state_->setState(GameStates::OPTIONS);
		entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->onResume();
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
			mapa->getComponent<MapMngr>()->loadNewMap("resources/images/tiled/Lvl1javi.tmx");
			state_->setState(GameStates::RUNNING);
		}
		//entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "musicDown") {
		auto soundMngr = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
		if (soundMngr->musicVol_ > 0.1f) {
			soundMngr->lowVolume(true);
			entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->updateIndicator(0, false);
		}
	}

	else if (buttonName_ == "musicUp") {
		auto soundMngr = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
		if (soundMngr->musicVol_ < 2) {
			soundMngr->upVolume(true);
			entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->updateIndicator(0, true);
		}
	}

	else if (buttonName_ == "fxDown") {
		auto soundMngr = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
		if (soundMngr->fxVol_ > 0.1f) {
			soundMngr->lowVolume(false);
			entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->updateIndicator(1, false);
		}
	}

	else if(buttonName_ == "fxUp") {
		auto soundMngr = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
		if (soundMngr->fxVol_ < 2) {
			soundMngr->upVolume(false);
			entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->updateIndicator(1, true);
		}
	}

	else if (buttonName_ == "resolutionDown") {
		sdlutils().lowerResolution();
		entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->updateIndicator(2, false);
	}

	else if (buttonName_ == "resolutionUp") {
		sdlutils().higherResolution();
		entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->updateIndicator(2, true);
	}

	else if (buttonName_ == "reset") {
		sdlutils().setWidth(1920.0);
		sdlutils().setHeight(1080.0);

		SDL_SetWindowSize(sdlutils().window(), sdlutils().width(), sdlutils().height());
		SDL_RenderSetScale(sdlutils().renderer(), 1.0f, 1.0f);

		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->resetVolumes();
		entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->resetIndicators();
	}

	else if (buttonName_ == "back") {
		state_->goBack();
	}
}
