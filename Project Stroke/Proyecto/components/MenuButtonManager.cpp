#include "MenuButtonManager.h"
#include "BackGround.h"
#include "Transition.h"
#include "MenuAnim.h"

MenuButtonManager::MenuButtonManager(string menu, int state) :menuMode_(menu), stateNumber_(state), background_(nullptr) {}

void MenuButtonManager::init() {

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);

	auto mngr = entity_->getMngr();
	if (menuMode_ == "mainMenu") {

		buttonsMagnitude_ = Vector2D(2, 2); //4 botones, 2x2

		buttons_ = vector<vector<Entity*>>(buttonsMagnitude_.getX());
		for (int i = 0; i < buttons_.size(); ++i) {
			buttons_[i] = vector<Entity*>(buttonsMagnitude_.getY());
		}

		auto* localbutton = mngr->addMenu();
		localbutton->addComponent<MenuButton>("local", Vector2D(100, 650), stateNumber_);
		buttons_[0][0] = localbutton;

		auto* onlinebutton = mngr->addMenu();
		onlinebutton->addComponent<MenuButton>("online", Vector2D(100, 850), stateNumber_);
		buttons_[0][1] = onlinebutton;

		auto* optionsbutton = mngr->addMenu();
		optionsbutton->addComponent<MenuButton>("options", Vector2D(1350, 650), stateNumber_);
		buttons_[1][0] = optionsbutton;

		auto* quitbutton = mngr->addMenu();
		quitbutton->addComponent<MenuButton>("quit", Vector2D(1520, 850), stateNumber_);
		buttons_[1][1] = quitbutton;

		auto backgrText = &sdlutils().images().at("mainMenuBlank");
		background_ = entity_->getMngr()->addMenuBackground();
		background_->addComponent<Transform>(Vector2D(0, -205), Vector2D(0, 0), backgrText->width(), backgrText->height(), 0.0, 1, 1);
		background_->addComponent<MenuAnim>();

	}
	else if (menuMode_ == "pauseMenu") {
		buttonsMagnitude_ = Vector2D(1, 3); //3 botones, 1x3
		buttons_ = vector<vector<Entity*>>(buttonsMagnitude_.getX());
		for (int i = 0; i < buttons_.size(); ++i) {
			buttons_[i] = vector<Entity*>(buttonsMagnitude_.getY());
		}

		auto* resumeButton = mngr->addMenu();
		resumeButton->addComponent<MenuButton>("resume", Vector2D(730, 150), stateNumber_);
		buttons_[0][0] = resumeButton;

		auto* optionsbutton = mngr->addMenu();
		optionsbutton->addComponent<MenuButton>("options", Vector2D(740, 450), stateNumber_);
		buttons_[0][1] = optionsbutton;

		auto* quitbutton = mngr->addMenu();
		quitbutton->addComponent<MenuButton>("exit", Vector2D(820, 750), stateNumber_);
		buttons_[0][2] = quitbutton;

		auto backgrText = &sdlutils().images().at("configBackground");
		background_ = entity_->getMngr()->addMenuBackground();

		background_->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), backgrText->width(), backgrText->height(), 0.0, 1, 1);
		background_->addComponent<BackGround>(backgrText, 0, false);
	}
	else if (menuMode_ == "hamsterMenu") {
		buttonsMagnitude_ = Vector2D(5, 1); //5 botones, 5x1
		buttons_ = vector<vector<Entity*>>(buttonsMagnitude_.getX());
		for (int i = 0; i < buttons_.size(); ++i) {
			buttons_[i] = vector<Entity*>(buttonsMagnitude_.getY());
		}

		auto* sardinillabutton = mngr->addMenu();
		sardinillabutton->addComponent<MenuButton>("sardinilla", Vector2D(129, 116), stateNumber_);
		buttons_[0][0] = sardinillabutton;

		auto* ketabutton = mngr->addMenu();
		ketabutton->addComponent<MenuButton>("keta", Vector2D(477, 116), stateNumber_);
		buttons_[1][0] = ketabutton;

		auto* monchibutton = mngr->addMenu();
		monchibutton->addComponent<MenuButton>("monchi", Vector2D(825, 117), stateNumber_);
		buttons_[2][0] = monchibutton;

		auto* canelonbutton = mngr->addMenu();
		canelonbutton->addComponent<MenuButton>("canelon", Vector2D(1172, 117), stateNumber_);
		buttons_[3][0] = canelonbutton;

		auto* angelbutton = mngr->addMenu();
		angelbutton->addComponent<MenuButton>("angel", Vector2D(1510, 118), stateNumber_);
		buttons_[4][0] = angelbutton;

		Texture* backgrText;

		if (!sdlutils().angelUnlocked()) {
			angelbutton->getComponent<MenuButton>()->setSelectable(false);
			backgrText = &sdlutils().images().at("hamsterSelectorBlankLocked");
		}
		else
			backgrText = &sdlutils().images().at("hamsterSelectorBlank");

		background_ = entity_->getMngr()->addMenuBackground();
		background_->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), backgrText->width(), backgrText->height(), 0.0, 1, 1);
		background_->addComponent<BackGround>(backgrText, 0, false);

		auto* playerSelectingIndicator = mngr->addMenu();
		playerSelectingIndicator->addComponent<MenuIndicator>("p", Vector2D(170, 25), stateNumber_);
		indicators_.push_back(playerSelectingIndicator);
	}
	else if (menuMode_ == "playerQuantityMenu") {
		buttonsMagnitude_ = Vector2D(1, 3); //3 botones, 1x3

		buttons_ = vector<vector<Entity*>>(buttonsMagnitude_.getX());
		for (int i = 0; i < buttons_.size(); ++i) {
			buttons_[i] = vector<Entity*>(buttonsMagnitude_.getY());
		}

		auto* twoPlayersButton = mngr->addMenu();
		twoPlayersButton->addComponent<MenuButton>("twoPlayers", Vector2D(750, 100), stateNumber_);
		buttons_[0][0] = twoPlayersButton;

		auto* threePlayersButton = mngr->addMenu();
		threePlayersButton->addComponent<MenuButton>("threePlayers", Vector2D(750, 400), stateNumber_);
		buttons_[0][1] = threePlayersButton;

		auto* fourPlayersButton = mngr->addMenu();
		fourPlayersButton->addComponent<MenuButton>("fourPlayers", Vector2D(750, 700), stateNumber_);
		buttons_[0][2] = fourPlayersButton;

		auto backgrText = &sdlutils().images().at("mainMenuBlank");
		background_ = entity_->getMngr()->addMenuBackground();
		background_->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), backgrText->width(), backgrText->height(), 0.0, 1, 1);
		background_->addComponent<BackGround>(backgrText, 0, false);
	}
	else if (menuMode_ == "optionsMenu") {
		buttonsMagnitude_ = Vector2D(2, 4);

		buttons_ = vector<vector<Entity*>>(buttonsMagnitude_.getX());
		for (int i = 0; i < buttons_.size(); ++i) {
			buttons_[i] = vector<Entity*>(buttonsMagnitude_.getY());
		}

		auto* musicDownButton = mngr->addMenu();
		musicDownButton->addComponent<MenuButton>("musicDown", Vector2D(650, 150), stateNumber_);
		buttons_[0][0] = musicDownButton;

		auto* musicUpButton = mngr->addMenu();
		musicUpButton->addComponent<MenuButton>("musicUp", Vector2D(1275, 150), stateNumber_);
		buttons_[1][0] = musicUpButton;

		auto* fxDownButton = mngr->addMenu();
		fxDownButton->addComponent<MenuButton>("fxDown", Vector2D(650, 350), stateNumber_);
		buttons_[0][1] = fxDownButton;

		auto* fxUpButton = mngr->addMenu();
		fxUpButton->addComponent<MenuButton>("fxUp", Vector2D(1275, 350), stateNumber_);
		buttons_[1][1] = fxUpButton;

		auto* resolutionDownButton = mngr->addMenu();
		resolutionDownButton->addComponent<MenuButton>("resolutionDown", Vector2D(650, 550), stateNumber_);
		buttons_[0][2] = resolutionDownButton;

		auto* resolutionUpButton = mngr->addMenu();
		resolutionUpButton->addComponent<MenuButton>("resolutionUp", Vector2D(1275, 550), stateNumber_);
		buttons_[1][2] = resolutionUpButton;

		auto* resetButton = mngr->addMenu();
		resetButton->addComponent<MenuButton>("reset", Vector2D(625, 750), stateNumber_);
		buttons_[0][3] = resetButton;

		auto* backButton = mngr->addMenu();
		backButton->addComponent<MenuButton>("back", Vector2D(1000, 750), stateNumber_);
		buttons_[1][3] = backButton;

		auto* musicVolumeIndicator = mngr->addMenu();
		musicVolumeIndicator->addComponent<MenuIndicator>("musicBar", Vector2D(725, 150), stateNumber_);
		indicators_.push_back(musicVolumeIndicator);

		auto* fxVolumeIndicator = mngr->addMenu();
		fxVolumeIndicator->addComponent<MenuIndicator>("fxBar", Vector2D(725, 350), stateNumber_);
		indicators_.push_back(fxVolumeIndicator);

		auto* resolutionIndicator = mngr->addMenu();
		resolutionIndicator->addComponent<MenuIndicator>("resolutionIndicator", Vector2D(725, 550), stateNumber_);
		indicators_.push_back(resolutionIndicator);

		auto* musicVolumeSign = mngr->addMenu();
		musicVolumeSign->addComponent<MenuIndicator>("musicVolume", Vector2D(212, 150), stateNumber_);
		indicators_.push_back(musicVolumeSign);

		auto* fxVolumeSign = mngr->addMenu();
		fxVolumeSign->addComponent<MenuIndicator>("sfxVolume", Vector2D(270, 350), stateNumber_);
		indicators_.push_back(fxVolumeSign);

		auto* resolutionSign = mngr->addMenu();
		resolutionSign->addComponent<MenuIndicator>("resolution", Vector2D(287, 550), stateNumber_);
		indicators_.push_back(resolutionSign);

		auto backgrText = &sdlutils().images().at("configBackground");
		background_ = entity_->getMngr()->addMenuBackground();
		
		background_->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), backgrText->width(), backgrText->height(), 0.0, 1, 1);
		background_->addComponent<BackGround>(backgrText, 0, false);
	}
	//buttonsPosition = Vector2D(0, 0);
	buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->selected();

	cooldown_ = 100;
	timer_ = sdlutils().currRealTime() + cooldown_;
}

void MenuButtonManager::update() {
	if (background_ != nullptr)
	{
		auto gameState = state_->getState();
		if (gameState == stateNumber_ && !background_->isActive()) {
			Vector2D pos = Vector2D(entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam().x, 
					entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam().y);
			background_->getComponent<Transform>()->setPos(pos);
			background_->setActive(true);
		}
		else if (gameState != stateNumber_ && background_->isActive())
			background_->setActive(false);
	}
}

void MenuButtonManager::moveUp() {
	if (sdlutils().currRealTime() > timer_ + cooldown_) {
		if (buttonsPosition_.getY() > 0) {
			buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->exited();
			buttonsPosition_.setY(buttonsPosition_.getY() - 1);
			buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->selected();
		}
		timer_ = sdlutils().currRealTime();
	}
}

void MenuButtonManager::moveDown() {
	if (sdlutils().currRealTime() > timer_ + cooldown_) {
		if (buttonsPosition_.getY() < buttonsMagnitude_.getY() - 1) {
			buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->exited();
			buttonsPosition_.setY(buttonsPosition_.getY() + 1);
			buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->selected();
		}
		timer_ = sdlutils().currRealTime();
	}
}

void MenuButtonManager::moveRight() {
	if (sdlutils().currRealTime() > timer_ + cooldown_) {
		if (buttonsPosition_.getX() < buttonsMagnitude_.getX() - 1) {
			bool moved = false;
			buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->exited();
			int i = buttonsPosition_.getX();
			while (!moved && i < buttonsMagnitude_.getX() - 1) {
				if (buttons_[i + 1][buttonsPosition_.getY()]->getComponent<MenuButton>()->selectable()) {
					buttonsPosition_.setX(i + 1);
					moved = true;
				}
				else
					i++;
			}
			buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->selected();

			if (menuMode_ == "hamsterMenu" && moved) {
				SDL_Rect r = buttons_[buttonsPosition_.getX()][0]->getComponent<MenuButton>()->getRect();
				indicators_[0]->getComponent<MenuIndicator>()->moveToButton(r.x);
			}
		}
		timer_ = sdlutils().currRealTime();
	}
}



void MenuButtonManager::moveLeft() {
	if (sdlutils().currRealTime() > timer_ + cooldown_) {
		if (buttonsPosition_.getX() > 0) {
			bool moved = false;
			buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->exited();
			int i = buttonsPosition_.getX();
			while (!moved && i > 0) {
				if (buttons_[i - 1][buttonsPosition_.getY()]->getComponent<MenuButton>()->selectable()) {
					buttonsPosition_.setX(i - 1);
					moved = true;
				}
				else
					i--;
			}
			buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->selected();

			if (menuMode_ == "hamsterMenu" && moved) {
				SDL_Rect r = buttons_[buttonsPosition_.getX()][0]->getComponent<MenuButton>()->getRect();
				indicators_[0]->getComponent<MenuIndicator>()->moveToButton(r.x);
			}
		}
		timer_ = sdlutils().currRealTime();
	}
}

void MenuButtonManager::moveToFirstSelectable() {
	bool found = false;
	buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->exited();
	int i = 0;
	while (!found && i < buttonsMagnitude_.getX() - 1) {
		if (buttons_[i][buttonsPosition_.getY()]->getComponent<MenuButton>()->selectable()) {
			buttonsPosition_.setX(i);
			found = true;
		}
		else
			i++;
	}
	buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->selected();

	if (menuMode_ == "hamsterMenu" && found) {
		SDL_Rect r = buttons_[buttonsPosition_.getX()][0]->getComponent<MenuButton>()->getRect();
		indicators_[0]->getComponent<MenuIndicator>()->moveToButton(r.x);
	}
}

void MenuButtonManager::setButtonPos(int x, int y) {
	//if (buttonsPosition_ != Vector2D(x, y)) {
	buttonsPosition_.set(x, y);
	for (int i = 0; i < buttonsMagnitude_.getX(); ++i) {
		for (int e = 0; e < buttonsMagnitude_.getY(); ++e) {
			buttons_[i][e]->getComponent<MenuButton>()->exited();
		}
	}
	buttons_[x][y]->getComponent<MenuButton>()->selected();
	//}
}

void MenuButtonManager::pressButton() {
	if (sdlutils().currRealTime() > timer_ + cooldown_)
		buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->pressed();
}

void MenuButtonManager::updateIndicator(int i, bool isUp) {
	indicators_[i]->getComponent<MenuIndicator>()->updateTexture(isUp);
}

void MenuButtonManager::resetIndicators() {
	for (int i = 0; i < indicators_.size(); ++i)
		indicators_[i]->getComponent<MenuIndicator>()->reset();
}

void MenuButtonManager::unlockAngelBackground() {
	// Hago esto porque cambiarle la textura al fondo no funciona, así que hay quitar el fondo y volverlo a crear
	background_->removeComponent<BackGround>();
	background_->addComponent<BackGround>(&sdlutils().images().at("hamsterSelectorBlank"), 0, false);
}