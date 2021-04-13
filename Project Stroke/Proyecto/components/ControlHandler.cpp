#include "ControlHandler.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

using namespace std;

void ControlHandler::init() {

	mov_ = entity_->getComponent<Movement>();
	assert(mov_ != nullptr);
	
	string id = entity_->getComponent<EntityAttribs>()->getId();
	
	if (id == "sardinilla") {
		ab_ = entity_->getComponent<Roll>();
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

	

	lt_ = entity_->getComponent<LightAttack>();
	assert(lt_ != nullptr);

	st_ = entity_->getComponent<StrongAttack>();
	assert(st_ != nullptr);
	//En vez de construirlo solamente deberia de tner que irse a donde estuviesen guardado los controles y coger el mapeado segun lo que le pida

	if (player_ == 0) {
		keymap.insert({ UP, SDL_SCANCODE_W });
		keymap.insert({ DOWN, SDL_SCANCODE_S });
		keymap.insert({ LEFT, SDL_SCANCODE_A });
		keymap.insert({ RIGHT, SDL_SCANCODE_D });
		keymap.insert({ SPACE, SDL_SCANCODE_SPACE });
	}

	else if (player_ == 1) {
		keymap.insert({ UP, SDL_SCANCODE_UP });
		keymap.insert({ DOWN, SDL_SCANCODE_DOWN });
		keymap.insert({ LEFT, SDL_SCANCODE_LEFT });
		keymap.insert({ RIGHT, SDL_SCANCODE_RIGHT });
		keymap.insert({ SPACE, SDL_SCANCODE_K });
	}
}


//el update recibe todos los input de SDL los filtra y envia la respuesta a la clase
void ControlHandler::update() {
	// Si el jugador tiene asignado un mando llama al método que controla el input de mando
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
}

void ControlHandler::setController(bool hasController) {
	hasController_ = hasController;
}


// Métododos que manejan el input según sea con mando o con teclado
void ControlHandler::handleController() {
	if (ih().isAxisMotionEvent()) {
		// MOVIMIENTO (Igual en un futuro se puede modificar para que vaya con el valor de los ejes)
		// Por alguna razón el eje Y va del revés
		// UP
		if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTY) < 0 || ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
			mov_->updateKeymap(Movement::UP, true);
			mov_->updateKeymap(Movement::DOWN, false);
			if (roll_ != nullptr) {
				roll_->updateKeymap(Roll::UP, true);
				roll_->updateKeymap(Roll::DOWN, false);
			}
		}
		//DOWN
		else if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTY) > 0 || ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
		{
			mov_->updateKeymap(Movement::UP, false);
			mov_->updateKeymap(Movement::DOWN, true);
			if (roll_ != nullptr) {
				roll_->updateKeymap(Roll::UP, false);
				roll_->updateKeymap(Roll::DOWN, true);
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
		}

		//RIGHT
		if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTX) > 0 || ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			mov_->updateKeymap(Movement::RIGHT, true);
			mov_->updateKeymap(Movement::LEFT, false);
			if (roll_ != nullptr) {
				roll_->updateKeymap(Roll::RIGHT, true);
				roll_->updateKeymap(Roll::LEFT, false);
			}
		}
		//	LEFT
		else if (ih().getAxisValue(player_, SDL_CONTROLLER_AXIS_LEFTX) < 0 || ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		{
			mov_->updateKeymap(Movement::RIGHT, false);
			mov_->updateKeymap(Movement::LEFT, true);
			if (roll_ != nullptr) {
				roll_->updateKeymap(Roll::RIGHT, false);
				roll_->updateKeymap(Roll::LEFT, true);
			}
		}
		else {
			mov_->updateKeymap(Movement::RIGHT, false);
			mov_->updateKeymap(Movement::LEFT, false);
			if (roll_ != nullptr) {
				roll_->updateKeymap(Roll::RIGHT, false);
				roll_->updateKeymap(Roll::LEFT, false);
			}
		}
	}

	if (ih().isButtonDownEvent()) {
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

	/*if (ih().isButtonUpEvent()) {
		if (ih().isButtonUp(player_, SDL_CONTROLLER_BUTTON_A))
		{
			mov_->updateKeymap(Movement::SPACE, false);
		}
	}*/
}

void ControlHandler::handleKeyboard() {
	//la parte para MOVEMENT
	//UP
	if (ih().isKeyDown(keymap.at(UP))) //aqui es donde hacemos nuestro keymap
	{
		mov_->updateKeymap(Movement::UP, true);
		if (roll_ != nullptr) roll_->updateKeymap(Roll::UP, true);
	}
	else if (ih().isKeyUp(keymap.at(UP)))
	{
		mov_->updateKeymap(Movement::UP, false);
		if (roll_ != nullptr) roll_->updateKeymap(Roll::UP, false);
	}
	//DOWN
	if (ih().isKeyDown(keymap.at(DOWN)))
	{
		mov_->updateKeymap(Movement::DOWN, true);
		if (roll_ != nullptr) roll_->updateKeymap(Roll::DOWN, true);

	}
	else if (ih().isKeyUp(keymap.at(DOWN)))
	{
		mov_->updateKeymap(Movement::DOWN, false);
		if (roll_ != nullptr) roll_->updateKeymap(Roll::DOWN, false);

	}
	//RIGHT
	if (ih().isKeyDown(keymap.at(RIGHT)))
	{
		mov_->updateKeymap(Movement::RIGHT, true);
		if (roll_ != nullptr) roll_->updateKeymap(Roll::RIGHT, true);

	}
	else if (ih().isKeyUp(keymap.at(RIGHT)))
	{
		mov_->updateKeymap(Movement::RIGHT, false);
		if (roll_ != nullptr) roll_->updateKeymap(Roll::RIGHT, false);

	}
	//	LEFT
	if (ih().isKeyDown(keymap.at(LEFT)))
	{
		mov_->updateKeymap(Movement::LEFT, true);
		if (roll_ != nullptr) roll_->updateKeymap(Roll::LEFT, true);

	}
	else if (ih().isKeyUp(keymap.at(LEFT)))
	{
		mov_->updateKeymap(Movement::LEFT, false);
		if (roll_ != nullptr) roll_->updateKeymap(Roll::LEFT, false);

	}
	//el jump no necesita que se le pase el false
	if (ih().isKeyDown(keymap.at(SPACE)))
	{
		mov_->updateKeymap(Movement::SPACE, true);
		/*if (roll_ != nullptr) roll_->updateKeymap(Roll::SPACE, true);*/

	}
	//el jump no necesita la parte para false

	//ATAQUE LIGERO
	if (ih().mouseButtonEvent()) {
		if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {
			lt_->attack();
		}
		//ATAQUE FUERTE
		else if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT) == 1) {
			st_->attack();
		}
		//HABILIDAD
		else if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::MIDDLE) == 1) {
			ab_->use();
		}
	}
}