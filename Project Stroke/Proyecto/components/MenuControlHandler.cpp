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
		if (gameState != GameStates::HAMSTERSELECTION) {
			bool handled = false;
			int i = 0;
			// Si hay algún mando conectado los tiene en cuenta
			while (!handled && ih().playerHasController(i)) {
				handled = handleController(i);
				i++;
			}
			if (!handled) {
				handleKeyboard();
				handleMouse();
			}
		}
		else {
			int i = sdlutils().hamstersChosen();
			if (ih().playerHasController(i))
				handleController(i);
			else {
				handleKeyboard();
				handleMouse();
			}
		}
	}
}

// M�tododos que manejan el input seg�n sea con mando o con teclado
bool MenuControlHandler::handleController(int controller) {
	bool handled = false;
	if (ih().getAxisValue(controller, SDL_CONTROLLER_AXIS_LEFTY) < 0 || ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
		menu_->moveUp();
		handled = true;
	}
	//DOWN
	else if (ih().getAxisValue(controller, SDL_CONTROLLER_AXIS_LEFTY) > 0 || ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		menu_->moveDown();
		handled = true;
	}

	//RIGHT
	if (ih().getAxisValue(controller, SDL_CONTROLLER_AXIS_LEFTX) > 0 || ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		menu_->moveRight();
		handled = true;
	}
	//	LEFT
	else if (ih().getAxisValue(controller, SDL_CONTROLLER_AXIS_LEFTX) < 0 || ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
	{
		menu_->moveLeft();
		handled = true;
	}

	if (ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_A)) {
		menu_->pressButton();
		handled = true;
	}
	
	return handled;
	/*auto gameState = states_->getState();
	if (ih().isButtonDown(controller, SDL_CONTROLLER_BUTTON_START) && gameState == GameStates::PAUSE) {
		states_->setState(GameStates::RUNNING);
	}*/
}

bool MenuControlHandler::handleKeyboard() {
	//UP
	if (ih().isKeyDown(keymap.at(UP))) //aqui es donde hacemos nuestro keymap
	{
		menu_->moveUp();
		return true;
	}
	//DOWN
	if (ih().isKeyDown(keymap.at(DOWN))) {
		menu_->moveDown();
		return true;
	}

	//RIGHT
	if (ih().isKeyDown(keymap.at(RIGHT))) {
		menu_->moveRight();
		return true;
	}

	//	LEFT
	if (ih().isKeyDown(keymap.at(LEFT))) {
		menu_->moveLeft();
		return true;
	}

	if (ih().isKeyDown(keymap.at(SPACE))) {
		menu_->pressButton();
		return true;
	}

	return false;
	/*auto gameState = states_->getState();
	if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) && gameState == GameStates::PAUSE) {
		states_->setState(GameStates::RUNNING);
	}*/
}

bool MenuControlHandler::handleMouse() {
	auto buttons = menu_->getButtons();
	auto magnitude = menu_->getMagnitude();
	
	int xMouse, yMouse;
	SDL_GetMouseState(&xMouse, &yMouse);

	bool click = ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT);

	if (xMouse != lastMouseX_ || yMouse != lastMouseY_ || click) {
		lastMouseX_ = xMouse;
		lastMouseY_ = yMouse;
		for (int i = 0; i < magnitude.getX(); ++i) {
			for (int e = 0; e < magnitude.getY(); ++e) {
				auto button = buttons[i][e];
				if (button != nullptr) {
					auto buttRect = button->getComponent<MenuButton>();
					if (buttRect != nullptr && mouseInButton(xMouse, yMouse, buttRect->getRect())) {
						menu_->setButtonPos(i, e);
						if (click) {
							menu_->pressButton();
						}
					}
				}
			}
		}
		return true;
	}
	return false;
}

bool MenuControlHandler::mouseInButton(float x, float y, SDL_Rect const& button) {
	auto relations = sdlutils().getResolutionRelation();
	float relX = relations.getX(), relY = relations.getY();
	x /= relX;
	y /= relY;

	//Mouse is left of the button
	if (x < button.x){
		return false;
	}
	//Mouse is right of the button
	else if (x > (button.x + button.w)){
		return false;
	}
	//Mouse above the button
	else if (y < button.y){
		return false;
	}
	//Mouse below the button
	else if (y > (button.y + button.h)){
		return false;
	}
	return true;
}

