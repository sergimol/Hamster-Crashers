#include "MenuButton.h"
#include "MenuButtonManager.h"
#include "Transition.h"


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
}

void MenuButton::render() {
	if ((int)state_->getState() == stateNumber_) {

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

void MenuButton::pressed() {
	// Botones con la misma funcionalidad están separados porque en el futuro funcionarán diferente
	if (buttonName_ == "local") {
		entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>()->changeScene("controls", false);
		//state_->setState(GameStates::RUNNING);
		state_->setState(GameStates::CONTROLS);
		entity_->getMngr()->getHandler<MainMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "online") {
		std::cout << "online\n";
	}
	else if (buttonName_ == "resume") {
		state_->setState(GameStates::RUNNING);
		entity_->getMngr()->getHandler<PauseMenu>()->getComponent<MenuButtonManager>()->updateKeymap(MenuButtonManager::SPACE, false);
	}
	else if (buttonName_ == "options") {
		std::cout << "options\n";
	}
	else if (buttonName_ == "quit") {
		ih().startQuitEvent();
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
	}
	else if (buttonName_ == "1920x1080") {
		std::cout << "changeResolution\n";
		//Cambiamos la resolucion
		sdlutils().setWidth(1920);
		sdlutils().setHeight(1080);

		//Y cambiamos la ventana
		SDL_SetWindowSize(sdlutils().window(), sdlutils().width(), sdlutils().height());
		SDL_RenderSetScale(sdlutils().renderer(), sdlutils().width() / 1920.0f, sdlutils().height() / 1080.0f);
	}
	else if (buttonName_ == "1280x720") {
		std::cout << "changeResolution\n";
		//Cambiamos la resolucion
		sdlutils().setWidth(1280);
		sdlutils().setHeight(720);

		//Y cambiamos la ventana
		SDL_SetWindowSize(sdlutils().window(), sdlutils().width(), sdlutils().height());
		SDL_RenderSetScale(sdlutils().renderer(), sdlutils().width() / 1920.0f, sdlutils().height() / 1080.0f);
	}
	else if (buttonName_ == "640x480") {
		std::cout << "changeResolution\n";
		//Cambiamos la resolucion
		sdlutils().setWidth(640);
		sdlutils().setHeight(480);

		//Y cambiamos la ventana
		SDL_SetWindowSize(sdlutils().window(), sdlutils().width(), sdlutils().height());
		SDL_RenderSetScale(sdlutils().renderer(), sdlutils().width() / 1920.0f, sdlutils().height() / 1080.0f);
	}
}
