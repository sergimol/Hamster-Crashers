#include "ControlHandeler.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
void ControlHandeler::init() {

	mov_ = entity_->getComponent<Movement>();
	assert(mov_ != nullptr);

}


//el update recibe todos los input de SDL los filtra y envia la respuesta a la clase
void ControlHandeler::update() {

	//la parte para MOVEMENT
	if (ih().isKeyDown(SDL_SCANCODE_UP) || ih().isKeyDown(SDLK_w)) //aqui es donde ahcemos nuestro keymap
		mov_->updateKeymap(Movement::UP, true);
	else if (ih().isKeyUp(SDL_SCANCODE_UP) && ih().isKeyUp(SDLK_w))
		mov_->updateKeymap(Movement::UP, false);
	if (ih().isKeyDown(SDL_SCANCODE_DOWN) || ih().isKeyDown(SDLK_s))
		mov_->updateKeymap(Movement::DOWN, true);
	else if (ih().isKeyUp(SDL_SCANCODE_DOWN) && ih().isKeyUp(SDLK_s))
		mov_->updateKeymap(Movement::DOWN, false);
	if (ih().isKeyDown(SDL_SCANCODE_RIGHT) || ih().isKeyDown(SDLK_d))
		mov_->updateKeymap(Movement::RIGHT, true);
	else if (ih().isKeyUp(SDL_SCANCODE_RIGHT) && ih().isKeyUp(SDLK_d))
		mov_->updateKeymap(Movement::RIGHT, false);
	if (ih().isKeyDown(SDL_SCANCODE_LEFT) || ih().isKeyDown(SDLK_a))
		mov_->updateKeymap(Movement::LEFT, true);
	else if (ih().isKeyUp(SDL_SCANCODE_LEFT) && ih().isKeyUp(SDLK_a))
		mov_->updateKeymap(Movement::LEFT, false);



}