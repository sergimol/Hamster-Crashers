#include "MenuButton.h"

#include "MenuButtonManager.h"
#include "Transition.h"
#include "MenuControlHandler.h"
#include "SoundManager.h"
#include "MapMngr.h"


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

void MenuButton::setSelectable(bool s)
{
	selectable_ = s;
	
	if(selectable_)
		button_ = &sdlutils().images().at(buttonName_ + "Button");
	else
		button_ = &sdlutils().images().at(buttonName_ + "ButtonUnselectable");

}

void MenuButton::pressed() {
	//Sonido
	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("button");

	// Botones con la misma funcionalidad est�n separados porque en el futuro funcionar�n diferente
	if (buttonName_ == "local") {
		sdlutils().setHamstersToChoose(1);
		state_->setState(GameStates::HAMSTERSELECTION);

		Vector2D pos = entity_->getMngr()->getHandler<MainMenu>()->getComponent<MenuControlHandler>()->getMousePos();
		entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuControlHandler>()->setMousePos(pos);

		entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuButtonManager>()->onResume();
		//entity_->getMngr()->getHandler<MainMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "online") {
		state_->setState(GameStates::PLAYERSELECTION);
		
		Vector2D pos = entity_->getMngr()->getHandler<MainMenu>()->getComponent<MenuControlHandler>()->getMousePos();
		entity_->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuControlHandler>()->setMousePos(pos);
		
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

		Vector2D pos = entity_->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuControlHandler>()->getMousePos();
		entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuControlHandler>()->setMousePos(pos);

		//entity_->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "threePlayers") {
		sdlutils().setHamstersToChoose(3);
		state_->setState(GameStates::HAMSTERSELECTION);

		Vector2D pos = entity_->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuControlHandler>()->getMousePos();
		entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuControlHandler>()->setMousePos(pos);

		//->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "fourPlayers") {
		sdlutils().setHamstersToChoose(4);
		state_->setState(GameStates::HAMSTERSELECTION);

		Vector2D pos = entity_->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuControlHandler>()->getMousePos();
		entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuControlHandler>()->setMousePos(pos);

		//entity_->getMngr()->getHandler<PlayerQuantityMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "options") {
		state_->setState(GameStates::OPTIONS);

		Vector2D pos = entity_->getMngr()->getHandler<MainMenu>()->getComponent<MenuControlHandler>()->getMousePos();
		entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuControlHandler>()->setMousePos(pos);

		entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->onResume();

		////Vuelve a renderizar el menu
		//state_->setState(GameStates::MAINMENU);

		////Y eliminamos TODO
		//for (Entity* e : entity_->getMngr()->getEntities()) {

		//	if (e->getMngr()->getHandler<Camera__>() != e
		//		&& e->getMngr()->getHandler<StateMachine>() != e && e->getMngr()->getHandler<Mother>() != e &&
		//		e->getMngr()->getHandler<Map>() != e && e->getMngr()->getHandler<SoundManager>() != e)
		//		//La elimino
		//		e->setActive(false);
		//}

		//for (Entity* e : entity_->getMngr()->getTiles())
		//	e->setActive(false);

		//for (Entity* e : entity_->getMngr()->getMapH())
		//	e->setActive(false);

		//for (Entity* e : entity_->getMngr()->getBgs())
		//	e->setActive(false);

		//for (Entity* e : entity_->getMngr()->getFgs())
		//	e->setActive(false);

		//entity_->getMngr()->refreshFrontGround();
		//entity_->getMngr()->refreshTiles();
		//entity_->getMngr()->refreshMapHeight();
		//entity_->getMngr()->refreshBackground();
		//entity_->getMngr()->refreshForeground();


		//entity_->getMngr()->refreshDeadBodies();
		//entity_->getMngr()->refreshEnemies();
		//entity_->getMngr()->refreshItems();
		//entity_->getMngr()->refreshObstacles();
		//entity_->getMngr()->refreshPlayers();

		//entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>()->clearColliders();

		////Eliminamos a todos los hamsters
		//entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>()->clearHamstersVector();

		//sdlutils().setHamstersChosen(0);
		//sdlutils().setHamstersToChoose(0);

		//auto& i = entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuButtonManager>()->getIndicators();

		//for (int h = 1; h < i.size(); h++) {
		//	i[h]->setActive(false);
		//}

		//i[0]->getComponent<MenuIndicator>()->reset();

	}
	else if (buttonName_ == "quit") {
		ih().startQuitEvent();
	}
	else if (buttonName_ == "sardinilla" || buttonName_ == "keta" || buttonName_ == "monchi" || buttonName_ == "canelon") {
		auto* mapa = entity_->getMngr()->getHandler<Map>();
		mapa->getComponent<MapMngr>()->addHamster(buttonName_);

		sdlutils().setHamstersToChoose(sdlutils().hamstersToChoose() - 1);
		sdlutils().setHamstersChosen(sdlutils().hamstersChosen() + 1);

		setSelectable(false);

		auto* mngr = entity_->getMngr();
		auto menuMngr = mngr->getHandler<HamsterSelectionMenu>()->getComponent<MenuButtonManager>();
		auto& indctrs = menuMngr->getIndicators();
		indctrs[0]->getComponent<MenuIndicator>()->updateTexture(true);

		menuMngr->moveToFirstSelectable();

		auto selectedIndicator = mngr->addMenu();
		selectedIndicator->addComponent<MenuIndicator>("p" + to_string(sdlutils().hamstersChosen()), Vector2D(dest_.x + 90, dest_.y), stateNumber_);
		indctrs.push_back(selectedIndicator);

		if (sdlutils().hamstersToChoose() <= 0) {
			mapa->getComponent<MapMngr>()->loadNewMap("resources/images/tiled/Level1.tmx");
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

	else if (buttonName_ == "fxUp") {
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
