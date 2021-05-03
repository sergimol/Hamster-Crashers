#include "MenuButtonManager.h"
#include "BackGround.h"
#include "Transition.h"

MenuButtonManager::MenuButtonManager(string menu, int state) :menuMode_(menu), stateNumber_(state), background_(nullptr) {}

void MenuButtonManager::init() {

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(states_ != nullptr);

	if (menuMode_ == "mainMenu") {
		
		buttonsMagnitude_ = Vector2D(2, 2); //4 botones, 2x2

		buttons_ = vector<vector<Entity*>>(buttonsMagnitude_.getX());
		for (int i = 0; i < buttons_.size(); ++i) {
			buttons_[i] = vector<Entity*>(buttonsMagnitude_.getY());
		}

		auto mngr_ = entity_->getMngr();

		auto* localbutton = mngr_->addMenu();
		localbutton->addComponent<MenuButton>("local", Vector2D(100, 550), 0);
		buttons_[0][0] = localbutton;

		auto* onlinebutton = mngr_->addMenu();
		onlinebutton->addComponent<MenuButton>("online", Vector2D(100, 750), 0);
		buttons_[0][1] = onlinebutton;

		auto* optionsbutton = mngr_->addMenu();
		optionsbutton->addComponent<MenuButton>("options", Vector2D(1550, 550), 0);
		buttons_[1][0] = optionsbutton;

		auto* quitbutton = mngr_->addMenu();
		quitbutton->addComponent<MenuButton>("quit", Vector2D(1550, 750), 0);
		buttons_[1][1] = quitbutton;
		
		auto backgrText = &sdlutils().images().at("mainMenuBlank");
		background_ = entity_->getMngr()->addBackGround();
		background_->addComponent<Transform>(Vector2D(0, -250), Vector2D(0, 0), backgrText->width(), backgrText->height(), 0.0, 1, 1);
		background_->addComponent<BackGround>(backgrText, 0);
	}
	else if (menuMode_ == "pauseMenu") {
		//buttonsMagnitude = Vector2D(1, 3); //3 botones, 1x3
		// Para la demo
		buttonsMagnitude_ = Vector2D(1, 2); //2 botones, 1x2
		buttons_ = vector<vector<Entity*>>(buttonsMagnitude_.getX());
		for (int i = 0; i < buttons_.size(); ++i) {
			buttons_[i] = vector<Entity*>(buttonsMagnitude_.getY());
		}

		auto mngr_ = entity_->getMngr();

		auto* resumeButton = mngr_->addMenu();
		resumeButton->addComponent<MenuButton>("resume", Vector2D(800, 300), 2);
		buttons_[0][0] = resumeButton;

		/*auto* optionsbutton = mngr_->addMenu();
		optionsbutton->addComponent<MenuButton>("options", Vector2D(870, 470), 2);
		buttons[0][1] = optionsbutton;*/

		auto* quitbutton = mngr_->addMenu();
		/*quitbutton->addComponent<MenuButton>("quit", Vector2D(870, 650), 2);
		buttons[0][2] = quitbutton;*/
		// Para la demo
		quitbutton->addComponent<MenuButton>("quit", Vector2D(870, 550), 2);
		buttons_[0][1] = quitbutton;
	}
	else if (menuMode_ == "hamsterMenu") {
		buttonsMagnitude_ = Vector2D(4, 1); //4 botones, 4x1
		buttons_ = vector<vector<Entity*>>(buttonsMagnitude_.getX());
		for (int i = 0; i < buttons_.size(); ++i) {
			buttons_[i] = vector<Entity*>(buttonsMagnitude_.getY());
		}
		auto mngr_ = entity_->getMngr();

		auto* sardinillabutton = mngr_->addMenu();
		sardinillabutton->addComponent<MenuButton>("sardinilla", Vector2D(50, 50), 1);
		buttons_[0][0] = sardinillabutton;

		auto* ketabutton = mngr_->addMenu();
		ketabutton->addComponent<MenuButton>("keta", Vector2D(500, 50), 1);
		buttons_[1][0] = ketabutton;

		auto* monchibutton = mngr_->addMenu();
		monchibutton->addComponent<MenuButton>("monchi", Vector2D(950, 50), 1);
		buttons_[2][0] = monchibutton;

		auto* canelonbutton = mngr_->addMenu();
		canelonbutton->addComponent<MenuButton>("canelon", Vector2D(1400, 50), 1);
		buttons_[3][0] = canelonbutton;

		auto backgrText = &sdlutils().images().at("hamsterSelectorBlank");
		background_ = entity_->getMngr()->addBackGround(); 
		background_->addComponent<Transform>(Vector2D(0, -250), Vector2D(0, 0), backgrText->width(), backgrText->height(), 0.0, 1, 1);
		background_->addComponent<BackGround>(backgrText, 0);
	}
	//buttonsPosition = Vector2D(0, 0);
	buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->selected();

	keymap.insert({ UP, false });
	keymap.insert({ DOWN, false });
	keymap.insert({ RIGHT, false });
	keymap.insert({ LEFT, false });
	keymap.insert({ SPACE, false });

	cooldown_ = 100;	
}

void MenuButtonManager::update() {
	if (sdlutils().currRealTime() > timer_ + cooldown_) {
		if (keymap.at(UP)) {
			if (buttonsPosition_.getY() > 0) {
				buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->exited();
				buttonsPosition_.setY(buttonsPosition_.getY() - 1);
				buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->selected();
			}
		}
		else if (keymap.at(DOWN)) {
			if (buttonsPosition_.getY() < buttonsMagnitude_.getY() - 1) {
				buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->exited();
				buttonsPosition_.setY(buttonsPosition_.getY() + 1);
				buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->selected();
			}
		}

		if (keymap.at(RIGHT)) {
			if (buttonsPosition_.getX() < buttonsPosition_.getX() - 1) {
				buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->exited();
				buttonsPosition_.setX(buttonsPosition_.getX() + 1);
				buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->selected();
			}
		}
		else if (keymap.at(LEFT)) {
			if (buttonsPosition_.getX() > 0) {
				buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->exited();
				buttonsPosition_.setX(buttonsPosition_.getX() - 1);
				buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->selected();
			}
		}

		if (keymap.at(SPACE)) {
			buttons_[buttonsPosition_.getX()][buttonsPosition_.getY()]->getComponent<MenuButton>()->pressed();
		}
		timer_ = sdlutils().currRealTime();
	}

	auto gameState = state_->getState();
	if (background_ != nullptr)
	{
		if((int)gameState == stateNumber_ && !background_->isActive())
			background_->setActive(true);
		else if((int)gameState != stateNumber_ && background_->isActive())
			background_->setActive(false);
	}
}

void MenuButtonManager::updateKeymap(KEYS x, bool is) {
	//if (x != SPACE || !keymap.at(SPACE))
		keymap.at(x) = is;
}