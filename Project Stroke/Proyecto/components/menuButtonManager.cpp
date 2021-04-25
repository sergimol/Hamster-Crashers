#include "menuButtonManager.h"


menuButtonManager::menuButtonManager(string menu) {
	MenuMode = menu;

	if (menu == "MainMenu") {
		buttonsMagnitude = Vector2D(2, 2); //4 botones, 2x2
		buttons = vector<Entity*> (buttonsMagnitude.getX()* buttonsMagnitude.getY());
		buttonsPosition = Vector2D();
		auto mngr_ = entity_->getMngr();

		auto* localbutton = mngr_->addEntity();
		localbutton->addComponent<MenuButton>("local", Vector2D(300, 700));
		buttons[0] = localbutton;

		auto* onlinebutton = mngr_->addEntity();
		onlinebutton->addComponent<MenuButton>("online", Vector2D(300, 900));
		buttons[1] = onlinebutton;

		auto* optionsbutton = mngr_->addEntity();
		optionsbutton->addComponent<MenuButton>("options", Vector2D(1750, 800));
		buttons[0] = localbutton;

		auto* quitbutton = mngr_->addEntity();
		quitbutton->addComponent<MenuButton>("quit", Vector2D(1750, 970));
		buttons[1] = onlinebutton;
	}

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
		buttons[buttonsPosition.getX() * buttonsPosition.getY()]->getComponent<MenuButton>()->pressed();
	}
	buttons[buttonsPosition.getX() * buttonsPosition.getY()]->getComponent<MenuButton>()->selected();
}

void menuButtonManager::updateKeymap(KEYS x, bool is) {
	if (x != SPACE || !keymap.at(SPACE))
		keymap.at(x) = is;
}