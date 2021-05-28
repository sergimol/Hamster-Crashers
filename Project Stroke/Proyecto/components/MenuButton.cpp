#include "MenuButton.h"

#include "MenuButtonManager.h"
#include "Transition.h"
#include "MenuControlHandler.h"
#include "SoundManager.h"
#include "MapMngr.h"
#include "EnemyMother.h"


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
	assert(state_ != nullptr);
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

	if (selectable_)
		button_ = &sdlutils().images().at(buttonName_ + "Button");
	else if (buttonName_ == "angel" && !sdlutils().angelUnlocked())
		button_ = &sdlutils().images().at(buttonName_ + "ButtonLocked");
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
	}
	else if (buttonName_ == "quit") {
		ih().startQuitEvent();
	}
	else if (buttonName_ == "sardinilla" || buttonName_ == "keta" || buttonName_ == "monchi" || buttonName_ == "canelon" || buttonName_ == "angel") {
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
		menuMngr->setLastUnselectable(buttonName_);

		auto selectedIndicator = mngr->addMenu();
		selectedIndicator->addComponent<MenuIndicator>("p" + to_string(sdlutils().hamstersChosen()), Vector2D(dest_.x + 45, dest_.y - 70), stateNumber_);
		indctrs.push_back(selectedIndicator);

		//Cuando haya seleccionado a los hamsters...
		if (sdlutils().hamstersToChoose() <= 0) {
			//Hago una transicion para presentar el nivel inicial
			entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>()->changeScene("Level3Boss", true, 8);

			state_->setState(GameStates::RUNNING);
		}
		Mix_FadeOutMusic(500);
	}
	else if (buttonName_ == "musicDown") {
		auto soundMngr = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
		if (soundMngr->musicVol_ > 0.099f) {
			soundMngr->lowVolume(true);
			entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->updateIndicator(0, false);
			entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->refreshMusicVol();
		}
	}

	else if (buttonName_ == "musicUp") {
		auto soundMngr = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
		if (soundMngr->musicVol_ < 1.0f) {
			soundMngr->upVolume(true);
			entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->updateIndicator(0, true);
			entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->refreshMusicVol();
		}
	}

	else if (buttonName_ == "fxDown") {
		auto soundMngr = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
		if (soundMngr->fxVol_ > 0.099f) {
			soundMngr->lowVolume(false);
			entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->updateIndicator(1, false);
			entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->refreshMusicVol();

		}
	}

	else if (buttonName_ == "fxUp") {
		auto soundMngr = entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>();
		if (soundMngr->fxVol_ < 1.0f) {
			soundMngr->upVolume(false);
			entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->updateIndicator(1, true);
			entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->refreshMusicVol();

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
		sdlutils().setResolutionIndex(RESOLUTIONSCOUNT - 1);

		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->resetVolumes();
		entity_->getMngr()->getHandler<OptionsMenu>()->getComponent<MenuButtonManager>()->resetIndicators();
	}

	else if (buttonName_ == "back") {
		state_->goBack();
	}

	else if (buttonName_ == "exit") {
		entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->resetCamera();
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->resetNumInts();
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->StopBossSounds();
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->StopTutorial();
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("HamstersMainThemev2");

		//Vuelve a renderizar el menu
		state_->setState(GameStates::MAINMENU);

		//Y eliminamos TODO
		for (Entity* e : entity_->getMngr()->getEntities()) {

			if (e->getMngr()->getHandler<Camera__>() != e
				&& e->getMngr()->getHandler<StateMachine>() != e && e->getMngr()->getHandler<Mother>() != e &&
				e->getMngr()->getHandler<Map>() != e && e->getMngr()->getHandler<SoundManager>() != e)
				//La elimino
				e->setActive(false);
		}

		for (Entity* e : entity_->getMngr()->getTiles())
			e->setActive(false);

		for (Entity* e : entity_->getMngr()->getMapH())
			e->setActive(false);

		for (Entity* e : entity_->getMngr()->getBgs())
			e->setActive(false);

		for (Entity* e : entity_->getMngr()->getFgs())
			e->setActive(false);

		for (Entity* e : entity_->getMngr()->getWavesObjects())
			e->setActive(false);

		for (Entity* e : entity_->getMngr()->getTraps())
			e->setActive(false);

		entity_->getMngr()->refreshFrontGround();
		entity_->getMngr()->refreshTiles();
		entity_->getMngr()->refreshMapHeight();
		entity_->getMngr()->refreshParallax();
		entity_->getMngr()->refreshForeground();


		entity_->getMngr()->refreshDeadBodies();
		entity_->getMngr()->refreshEnemies();
		entity_->getMngr()->refreshItems();
		entity_->getMngr()->refreshObstacles();
		entity_->getMngr()->refreshPlayers();
		entity_->getMngr()->refreshWavesObjects();
		entity_->getMngr()->refreshTraps();
		entity_->getMngr()->refresh();

		auto map = entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>();
		map->clearColliders();

		//Eliminamos a todos los hamsters
		map->clearHamstersVector();

		map->resetTriggerList();

		sdlutils().setHamstersChosen(0);
		sdlutils().setHamstersToChoose(0);

		auto* hsm = entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuButtonManager>();

		auto& i = hsm->getIndicators();
		auto& but = hsm->getButtons();
		for (int h = 1; h < i.size(); h++) {
			i[h]->setActive(false);
		}

		for (int j = 0; j < but.size(); ++j) {
			auto mb = but[j][0]->getComponent<MenuButton>();
			if (mb->getName() != "angel" || sdlutils().angelUnlocked())
				mb->setSelectable(true);
		}

		i[0]->getComponent<MenuIndicator>()->reset();

		entity_->getMngr()->getHandler<Mother>()->getComponent<EnemyMother>()->resetNumPlayers();
		entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->changeCamState(State::Players);
	}
}
