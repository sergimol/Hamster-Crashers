#include "menuButtonManager.h"


menuButtonManager::menuButtonManager(string menu) :MenuMode(menu) {}

void menuButtonManager::init() {

	if (MenuMode == "mainMenu") {
		buttonsMagnitude = Vector2D(2, 2); //4 botones, 2x2
		buttons = vector<Entity*>(buttonsMagnitude.getX() * buttonsMagnitude.getY());
		auto mngr_ = entity_->getMngr();

		auto* localbutton = mngr_->addEntity();
		localbutton->addComponent<MenuButton>("local", Vector2D(100, 550));
		buttons[0] = localbutton;

		auto* onlinebutton = mngr_->addEntity();
		onlinebutton->addComponent<MenuButton>("online", Vector2D(100, 750));
		buttons[1] = onlinebutton;

		auto* optionsbutton = mngr_->addEntity();
		optionsbutton->addComponent<MenuButton>("options", Vector2D(1550, 650));
		buttons[0] = localbutton;

		auto* quitbutton = mngr_->addEntity();
		quitbutton->addComponent<MenuButton>("quit", Vector2D(1550, 820));
		buttons[1] = onlinebutton;
	}
	else if (MenuMode == "pauseMenu") {
		buttonsMagnitude = Vector2D(2, 2); //4 botones, 2x2
		buttons = vector<Entity*>(buttonsMagnitude.getX() * buttonsMagnitude.getY());
		auto mngr_ = entity_->getMngr();

		auto* localbutton = mngr_->addEntity();
		localbutton->addComponent<MenuButton>("local", Vector2D(800, 300));
		buttons[0] = localbutton;

		auto* onlinebutton = mngr_->addEntity();
		onlinebutton->addComponent<MenuButton>("online", Vector2D(800, 470));
		buttons[1] = onlinebutton;

		auto* optionsbutton = mngr_->addEntity();
		optionsbutton->addComponent<MenuButton>("options", Vector2D(870, 650));
		buttons[0] = localbutton;
	}
	else if (MenuMode == "hamsterMenu") {
		buttonsMagnitude = Vector2D(1, 4); //4 botones, 2x2
		buttons = vector<Entity*>(buttonsMagnitude.getX() * buttonsMagnitude.getY());
		auto mngr_ = entity_->getMngr();

		auto* sardinillabutton = mngr_->addEntity();
		sardinillabutton->addComponent<MenuButton>("sardinilla", Vector2D(50, 50));
		buttons[0] = sardinillabutton;

		auto* ketabutton = mngr_->addEntity();
		ketabutton->addComponent<MenuButton>("keta", Vector2D(500, 50));
		buttons[1] = ketabutton;

		auto* monchibutton = mngr_->addEntity();
		monchibutton->addComponent<MenuButton>("monchi", Vector2D(950, 50));
		buttons[2] = monchibutton;

		auto* canelonbutton = mngr_->addEntity();
		canelonbutton->addComponent<MenuButton>("canelon", Vector2D(1400, 50));
		buttons[3] = canelonbutton;
	}
	buttonsPosition = Vector2D();

	keymap.insert({ UP, false });
	keymap.insert({ DOWN, false });
	keymap.insert({ RIGHT, false });
	keymap.insert({ LEFT, false });
	keymap.insert({ SPACE, false });
}

void menuButtonManager::update() {
	if (keymap.at(UP)) {
		if (buttonsPosition.getY() > 0)
			buttonsPosition.setY(buttonsPosition.getY() - 1);
	}
	else if (keymap.at(DOWN)) {
		if (buttonsPosition.getY() < buttonsMagnitude.getY())
			buttonsPosition.setY(buttonsPosition.getY() + 1);
	}

	if (keymap.at(RIGHT)) {
		if (buttonsPosition.getX() < buttonsMagnitude.getX())
			buttonsPosition.setY(buttonsPosition.getX() + 1);
	}
	else if (keymap.at(LEFT)) {
		if (buttonsPosition.getX() > 0)
			buttonsPosition.setY(buttonsPosition.getX() - 1);
	}
	else if (keymap.at(SPACE)) {
		buttons[buttonsPosition.getX()* buttonsPosition.getY()]->getComponent<MenuButton>()->pressed();
	}
	buttons[buttonsPosition.getX() * buttonsPosition.getY()]->getComponent<MenuButton>()->selected();
}

void menuButtonManager::updateKeymap(KEYS x, bool is) {
	if (x != SPACE || !keymap.at(SPACE))
		keymap.at(x) = is;
}