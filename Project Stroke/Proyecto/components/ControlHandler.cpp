#include "ControlHandler.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

using namespace std;

void ControlHandler::init() {

	mov_ = entity_->getComponent<Movement>();
	assert(mov_ != nullptr);

	mic_ = entity_->getComponent<MovementInChase>();

	string id = entity_->getComponent<EntityAttribs>()->getId();

	if (id == "sardinilla") {
		ab_ = entity_->getComponent<Roll>();
		//ab_ = entity_->getComponent<Turret>();
		roll_ = entity_->getComponent<Roll>();
	}
	else if (id == "canelon")
		ab_ = entity_->getComponent<Pray>();
	else if (id == "keta")
		ab_ = entity_->getComponent<Poison>();
	else
		ab_ = entity_->getComponent<Turret>();

	assert(ab_ != nullptr);
	//assert(roll_ != nullptr); PUEDE SER NULLPTR

	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);

	lt_ = entity_->getComponent<LightAttack>();
	assert(lt_ != nullptr);

	st_ = entity_->getComponent<StrongAttack>();
	assert(st_ != nullptr);

	/*pause_ = entity_->getMngr()->getHandler<PauseMenu>()->getComponent<MenuButtonManager>();
	main_ = entity_->getMngr()->getHandler<MainMenu>()->getComponent<MenuButtonManager>();*/
	


	states_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(states_ != nullptr);

	keymap.insert({ UP, SDL_SCANCODE_W });
	keymap.insert({ DOWN, SDL_SCANCODE_S });
	keymap.insert({ LEFT, SDL_SCANCODE_A });
	keymap.insert({ RIGHT, SDL_SCANCODE_D });
	keymap.insert({ SPACE, SDL_SCANCODE_SPACE });
}


//el update recibe todos los input de SDL los filtra y envia la respuesta a la clase
void ControlHandler::update() {
	// Si el jugador tiene asignado un mando llama al m�todo que controla el input de mando
	if (ih().playerHasController(player_)) {
		handleController();
	}
	else
		handleKeyboard();
}

void ControlHandler::onDisable() {
	mov_->updateKeymap(Movement::RIGHT, false);
	mov_->updateKeymap(Movement::LEFT, false);
	mov_->updateKeymap(Movement::DOWN, false);
	mov_->updateKeymap(Movement::UP, false);

	if (mic_ != nullptr) {
		mic_->updateKeymap(MovementInChase::RIGHT, false);
		mic_->updateKeymap(MovementInChase::LEFT, false);
		mic_->updateKeymap(MovementInChase::DOWN, false);
		mic_->updateKeymap(MovementInChase::UP, false);
	}
}

void ControlHandler::setController(bool hasController) {
	hasController_ = hasController;
}


// M�tododos que manejan el input seg�n sea con mando o con teclado
void ControlHandler::handleController() {

	auto gameState = states_->getState();
	if (gameState == GameStates::RUNNING) {

		if (ih().isAxisMotionEvent()) {
			// MOVIMIENTO (Igual en un futuro se puede modificar para que vaya con el valor de los ejes)
			// Por alguna raz�n el eje Y va del rev�s
			// UP
			if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTY) < 0) {
				mov_->updateKeymap(Movement::UP, true);
				mov_->updateKeymap(Movement::DOWN, false);
				if (roll_ != nullptr) {
					roll_->updateKeymap(Roll::UP, true);
					roll_->updateKeymap(Roll::DOWN, false);
				}
				if (mic_ != nullptr) {
					mic_->updateKeymap(MovementInChase::DOWN, false);
					mic_->updateKeymap(MovementInChase::UP, true);
				}
			}
			//DOWN
			else if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTY) > 0)
			{
				mov_->updateKeymap(Movement::UP, false);
				mov_->updateKeymap(Movement::DOWN, true);
				if (roll_ != nullptr) {
					roll_->updateKeymap(Roll::UP, false);
					roll_->updateKeymap(Roll::DOWN, true);
				}
				if (mic_ != nullptr) {
					mic_->updateKeymap(MovementInChase::DOWN, true);
					mic_->updateKeymap(MovementInChase::UP, false);
				}
			}
			else
			{				
				mov_->updateKeymap(Movement::UP, false);
				mov_->updateKeymap(Movement::DOWN, false);
				if (roll_ != nullptr) {
					roll_->updateKeymap(Roll::UP, false);
					roll_->updateKeymap(Roll::DOWN, false);
				}
				if (mic_ != nullptr) {
					mic_->updateKeymap(MovementInChase::DOWN, false);
					mic_->updateKeymap(MovementInChase::UP, false);
				}
			}

			//RIGHT
			if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTX) > 0)
			{
				mov_->updateKeymap(Movement::RIGHT, true);
				mov_->updateKeymap(Movement::LEFT, false);
				if (roll_ != nullptr) {
					roll_->updateKeymap(Roll::RIGHT, true);
					roll_->updateKeymap(Roll::LEFT, false);
				}
				if (mic_ != nullptr) {
					mic_->updateKeymap(MovementInChase::RIGHT, true);
					mic_->updateKeymap(MovementInChase::LEFT, false);
				}
			}
			//	LEFT
			else if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTX) < 0)
			{
				mov_->updateKeymap(Movement::RIGHT, false);
				mov_->updateKeymap(Movement::LEFT, true);
				if (roll_ != nullptr) {
					roll_->updateKeymap(Roll::RIGHT, false);
					roll_->updateKeymap(Roll::LEFT, true);
				}
				if (mic_ != nullptr) {
					mic_->updateKeymap(MovementInChase::RIGHT, false);
					mic_->updateKeymap(MovementInChase::LEFT, true);
				}
			}
			else {
				mov_->updateKeymap(Movement::RIGHT, false);
				mov_->updateKeymap(Movement::LEFT, false);
				if (roll_ != nullptr) {
					roll_->updateKeymap(Roll::RIGHT, false);
					roll_->updateKeymap(Roll::LEFT, false);
				}
				if (mic_ != nullptr) {
					mic_->updateKeymap(MovementInChase::RIGHT, false);
					mic_->updateKeymap(MovementInChase::LEFT, false);
				}
			}
		}

		auto& hamState = hms_->getState();
		
		if (ih().isButtonDownEvent()) {
			if (hamState == HamStates::DEFAULT) {
				//JUMP
				if (ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_A))
				{
					mov_->updateKeymap(Movement::SPACE, true);
					/*if (roll_ != nullptr) roll_->updateKeymap(Roll::SPACE, true);*/
				}

				//ATAQUE LIGERO
				else if (ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_X)) {
					lt_->attack();
				}
				//ATAQUE FUERTE
				else if (ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_Y)) {
					st_->attack();
				}
				//HABILIDAD
				else if (ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
					ab_->use();
				}
			}
			if (ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_START)) {
				states_->setState(GameStates::PAUSE);
			}
		}
	}

	//else {
	//	if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTY) < 0 || ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
	//		if (gameState == GameStates::PAUSE) {
	//			pause_->updateKeymap(MenuButtonManager::UP, true);
	//			pause_->updateKeymap(MenuButtonManager::DOWN, false);
	//		}
	//		else if (gameState == GameStates::MAINMENU) {
	//			main_->updateKeymap(MenuButtonManager::UP, true);
	//			main_->updateKeymap(MenuButtonManager::DOWN, false);
	//		}
	//	}
	//	//DOWN
	//	else if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTY) > 0 || ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	//	{
	//		if (gameState == GameStates::PAUSE) {
	//			pause_->updateKeymap(MenuButtonManager::UP, false);
	//			pause_->updateKeymap(MenuButtonManager::DOWN, true);
	//		}
	//		else if (gameState == GameStates::MAINMENU) {
	//			main_->updateKeymap(MenuButtonManager::UP, false);
	//			main_->updateKeymap(MenuButtonManager::DOWN, true);
	//		}
	//	}
	//	else
	//	{
	//		if (gameState == GameStates::PAUSE) {
	//			pause_->updateKeymap(MenuButtonManager::UP, false);
	//			pause_->updateKeymap(MenuButtonManager::DOWN, false);
	//		}
	//		else if (gameState == GameStates::MAINMENU) {
	//			main_->updateKeymap(MenuButtonManager::UP, false);
	//			main_->updateKeymap(MenuButtonManager::DOWN, false);
	//		}
	//	}

	//	//RIGHT
	//	if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTX) > 0 || ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
	//	{
	//		if (gameState == GameStates::PAUSE) {
	//			pause_->updateKeymap(MenuButtonManager::RIGHT, true);
	//			pause_->updateKeymap(MenuButtonManager::LEFT, false);
	//		}
	//		else if (gameState == GameStates::MAINMENU) {
	//			main_->updateKeymap(MenuButtonManager::RIGHT, true);
	//			main_->updateKeymap(MenuButtonManager::LEFT, false);
	//		}
	//	}
	//	//	LEFT
	//	else if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTX) < 0 || ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
	//	{
	//		if (gameState == GameStates::PAUSE) {
	//			pause_->updateKeymap(MenuButtonManager::RIGHT, false);
	//			pause_->updateKeymap(MenuButtonManager::LEFT, true);
	//		}
	//		else if (gameState == GameStates::MAINMENU) {
	//			main_->updateKeymap(MenuButtonManager::RIGHT, false);
	//			main_->updateKeymap(MenuButtonManager::LEFT, true);
	//		}
	//	}
	//	else {
	//		if (gameState == GameStates::PAUSE) {
	//			pause_->updateKeymap(MenuButtonManager::RIGHT, false);
	//			pause_->updateKeymap(MenuButtonManager::LEFT, false);
	//		}
	//		else if (gameState == GameStates::MAINMENU) {
	//			main_->updateKeymap(MenuButtonManager::RIGHT, false);
	//			main_->updateKeymap(MenuButtonManager::LEFT, false);
	//		}
	//	}

	//	if (ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_A)) {
	//		if(gameState == GameStates::PAUSE)
	//			pause_->updateKeymap(MenuButtonManager::SPACE, true);
	//		else if(gameState == GameStates::MAINMENU)
	//			main_->updateKeymap(MenuButtonManager::SPACE, true);
	//	}
	//		
	//	if (ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_START) && gameState == GameStates::PAUSE) {
	//		states_->setState(GameStates::RUNNING);
	//	}
	//}
}

void ControlHandler::handleKeyboard() {
	auto gameState = states_->getState();
	//UP
	if (ih().isKeyDown(keymap.at(UP))) //aqui es donde hacemos nuestro keymap
	{
		if (gameState == GameStates::RUNNING) {
			mov_->updateKeymap(Movement::UP, true);
			if (roll_ != nullptr) roll_->updateKeymap(Roll::UP, true);
			if (mic_ != nullptr) mic_->updateKeymap(MovementInChase::UP, true);
		}
		/*else if (gameState == GameStates::PAUSE )
			pause_->updateKeymap(MenuButtonManager::UP, true);
		else if (gameState == GameStates::MAINMENU )
			main_->updateKeymap(MenuButtonManager::UP, true);*/
	}
	else if (ih().isKeyUp(keymap.at(UP)))
	{
		if (gameState == GameStates::RUNNING) {
			mov_->updateKeymap(Movement::UP, false);
			if (roll_ != nullptr) roll_->updateKeymap(Roll::UP, false);
			if (mic_ != nullptr) mic_->updateKeymap(MovementInChase::UP, false);
		}
		/*else if (gameState == GameStates::PAUSE)
			pause_->updateKeymap(MenuButtonManager::UP, false);
		else if (gameState == GameStates::MAINMENU)
			main_->updateKeymap(MenuButtonManager::UP, false);*/
	}
	//DOWN
	if (ih().isKeyDown(keymap.at(DOWN)))
	{
		if (gameState == GameStates::RUNNING) {
			mov_->updateKeymap(Movement::DOWN, true);
			if (roll_ != nullptr) roll_->updateKeymap(Roll::DOWN, true);
			if (mic_ != nullptr) mic_->updateKeymap(MovementInChase::DOWN, true);
		}
		/*else if (gameState == GameStates::PAUSE)
			pause_->updateKeymap(MenuButtonManager::DOWN, true);
		else if (gameState == GameStates::MAINMENU)
			main_->updateKeymap(MenuButtonManager::DOWN, true);*/

	}
	else if (ih().isKeyUp(keymap.at(DOWN)))
	{
		if (gameState == GameStates::RUNNING) {
			mov_->updateKeymap(Movement::DOWN, false);
			if (roll_ != nullptr) roll_->updateKeymap(Roll::DOWN, false);
			if (mic_ != nullptr) mic_->updateKeymap(MovementInChase::DOWN, false);
		}
		/*else if (gameState == GameStates::PAUSE)
			pause_->updateKeymap(MenuButtonManager::DOWN, false);
		else if (gameState == GameStates::MAINMENU)
			main_->updateKeymap(MenuButtonManager::DOWN, false);*/

	}
	//RIGHT
	if (ih().isKeyDown(keymap.at(RIGHT)))
	{
		if (gameState == GameStates::RUNNING) {
			mov_->updateKeymap(Movement::RIGHT, true);
			if (roll_ != nullptr) roll_->updateKeymap(Roll::RIGHT, true);
			if (mic_ != nullptr) mic_->updateKeymap(MovementInChase::RIGHT, true);
		}
		/*else if (gameState == GameStates::PAUSE)
			pause_->updateKeymap(MenuButtonManager::RIGHT, true);
		else if (gameState == GameStates::MAINMENU)
			main_->updateKeymap(MenuButtonManager::RIGHT, true);*/

	}
	else if (ih().isKeyUp(keymap.at(RIGHT)))
	{
		if (gameState == GameStates::RUNNING) {
			mov_->updateKeymap(Movement::RIGHT, false);
			if (roll_ != nullptr) roll_->updateKeymap(Roll::RIGHT, false);
			if (mic_ != nullptr) mic_->updateKeymap(MovementInChase::RIGHT, false);
		}
		/*else if (gameState == GameStates::PAUSE)
			pause_->updateKeymap(MenuButtonManager::RIGHT, false);
		else if (gameState == GameStates::MAINMENU)
			main_->updateKeymap(MenuButtonManager::RIGHT, false);*/
	}
	//	LEFT
	if (ih().isKeyDown(keymap.at(LEFT)))
	{
		if (gameState == GameStates::RUNNING) {
			mov_->updateKeymap(Movement::LEFT, true);
			if (roll_ != nullptr) roll_->updateKeymap(Roll::LEFT, true);
			if (mic_ != nullptr) mic_->updateKeymap(MovementInChase::LEFT, true);
		}
		/*else if (gameState == GameStates::PAUSE)
			pause_->updateKeymap(MenuButtonManager::LEFT, true);
		else if (gameState == GameStates::MAINMENU)
			main_->updateKeymap(MenuButtonManager::LEFT, true);*/

	}
	else if (ih().isKeyUp(keymap.at(LEFT)))
	{
		if (gameState == GameStates::RUNNING) {
			mov_->updateKeymap(Movement::LEFT, false);
			if (roll_ != nullptr) roll_->updateKeymap(Roll::LEFT, false);
			if (mic_ != nullptr) mic_->updateKeymap(MovementInChase::LEFT, false);
		}
		/*else if (gameState == GameStates::PAUSE)
			pause_->updateKeymap(MenuButtonManager::LEFT, false);
		else if (gameState == GameStates::MAINMENU)
			main_->updateKeymap(MenuButtonManager::LEFT, false);*/
	}
	auto& hamState = hms_->getState();
	//el jump no necesita que se le pase el false
	if (ih().isKeyDown(keymap.at(SPACE)))
	{
		if (gameState == GameStates::RUNNING && hamState != HamStates::DEAD && hamState != HamStates::INFARCTED) {
			mov_->updateKeymap(Movement::SPACE, true);
			if (mic_ != nullptr) mic_->updateKeymap(MovementInChase::SPACE, true);
		}
		/*else if (gameState == GameStates::PAUSE)
			pause_->updateKeymap(MenuButtonManager::SPACE, true);
		else if (gameState == GameStates::MAINMENU)
			main_->updateKeymap(MenuButtonManager::SPACE, true);*/

	}
	if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		if (gameState == GameStates::RUNNING) {
			states_->setState(GameStates::PAUSE);
		}
		else if (gameState == GameStates::PAUSE)
			states_->setState(GameStates::RUNNING);
	}
	//el jump no necesita la parte para false


	//ATAQUE LIGERO
	if (gameState == GameStates::RUNNING && hamState != HamStates::DEAD && hamState != HamStates::INFARCTED && ih().mouseButtonEvent()) {
		if (hamState != HamStates::ABILITY && ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {
			lt_->attack();
		}
		//ATAQUE FUERTE
		else if (hamState != HamStates::ABILITY && ih().getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT) == 1) {
			st_->attack();
		}
		//HABILIDAD
		else if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::MIDDLE) == 1) {
			ab_->use();
		}
	}
}