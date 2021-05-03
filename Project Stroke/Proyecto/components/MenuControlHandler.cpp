#include "MenuControlHandler.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

using namespace std;

void MenuControlHandler::init() {

	menu_ = entity_->getComponent<MenuButtonManager>();

	states_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(states_ != nullptr);

	keymap.insert({ UP, SDL_SCANCODE_UP });
	keymap.insert({ DOWN, SDL_SCANCODE_DOWN });
	keymap.insert({ LEFT, SDL_SCANCODE_LEFT });
	keymap.insert({ RIGHT, SDL_SCANCODE_RIGHT });
	keymap.insert({ SPACE, SDL_SCANCODE_RETURN });
}


//el update recibe todos los input de SDL los filtra y envia la respuesta a la clase
void MenuControlHandler::update() {
	auto gameState = states_->getState();

	if (gameState == stateNumber_) {
		// Si hay algún mando conectado los tiene en cuenta
		for (int i = 0; i < MAXPLAYERS; ++i) {
			if (ih().playerHasController(i)) {
				handleController(i);
			}
			else
				break;
		}
		handleKeyboard();
	}
}

// M�tododos que manejan el input seg�n sea con mando o con teclado
void MenuControlHandler::handleController(int controller) {

	if (ih().getAxisValue(controller, SDL_CONTROLLER_AXIS_LEFTY) < 0 || ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
		menu_->updateKeymap(MenuButtonManager::UP, true);
		menu_->updateKeymap(MenuButtonManager::DOWN, false);
	}
	//DOWN
	else if (ih().getAxisValue(controller, SDL_CONTROLLER_AXIS_LEFTY) > 0 || ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		menu_->updateKeymap(MenuButtonManager::UP, false);
		menu_->updateKeymap(MenuButtonManager::DOWN, true);
	}
	else
	{
		menu_->updateKeymap(MenuButtonManager::UP, false);
		menu_->updateKeymap(MenuButtonManager::DOWN, false);
	}

	//RIGHT
	if (ih().getAxisValue(controller, SDL_CONTROLLER_AXIS_LEFTX) > 0 || ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		menu_->updateKeymap(MenuButtonManager::RIGHT, true);
		menu_->updateKeymap(MenuButtonManager::LEFT, false);
	}
	//	LEFT
	else if (ih().getAxisValue(controller, SDL_CONTROLLER_AXIS_LEFTX) < 0 || ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
	{
		menu_->updateKeymap(MenuButtonManager::RIGHT, false);
		menu_->updateKeymap(MenuButtonManager::LEFT, true);
	}
	else {
		menu_->updateKeymap(MenuButtonManager::RIGHT, false);
		menu_->updateKeymap(MenuButtonManager::LEFT, false);
	}

	if (ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_A)) 
		menu_->updateKeymap(MenuButtonManager::SPACE, true);
	
	/*auto gameState = states_->getState();
	if (ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_START) && gameState == GameStates::PAUSE) {
		states_->setState(GameStates::RUNNING);
	}*/
}

void MenuControlHandler::handleKeyboard() {
	//UP
	if (ih().isKeyDown(keymap.at(UP))) //aqui es donde hacemos nuestro keymap
		menu_->updateKeymap(MenuButtonManager::UP, true);
	else if (ih().isKeyUp(keymap.at(UP)))
		menu_->updateKeymap(MenuButtonManager::UP, false);
		
	//DOWN
	if (ih().isKeyDown(keymap.at(DOWN)))
		menu_->updateKeymap(MenuButtonManager::DOWN, true);
	else if (ih().isKeyUp(keymap.at(DOWN)))
		menu_->updateKeymap(MenuButtonManager::DOWN, false);

	//RIGHT
	if (ih().isKeyDown(keymap.at(RIGHT)))
		menu_->updateKeymap(MenuButtonManager::RIGHT, true);
	else if (ih().isKeyUp(keymap.at(RIGHT)))
		menu_->updateKeymap(MenuButtonManager::RIGHT, false);

	//	LEFT
	if (ih().isKeyDown(keymap.at(LEFT)))
		menu_->updateKeymap(MenuButtonManager::LEFT, true);
	else if (ih().isKeyUp(keymap.at(LEFT)))
		menu_->updateKeymap(MenuButtonManager::LEFT, false);

	if (ih().isKeyDown(keymap.at(SPACE)))
		menu_->updateKeymap(MenuButtonManager::SPACE, true);

	/*auto gameState = states_->getState();
	if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) && gameState == GameStates::PAUSE) {
		states_->setState(GameStates::RUNNING);
	}*/
}