#include "MenuButton.h"


MenuButton::MenuButton(std::string n, Vector2D position, int stateNum) :
	buttonName_(n),
	renderCoords_(position),
	stateNumber_(stateNum)
{
	button_ = &sdlutils().images().at(buttonName_ + "Button");
	buttonEnter_ = &sdlutils().images().at(buttonName_ + "ButtonEnter");

	mainText = button_;

	dest_.x = renderCoords_.getX();
	dest_.y = renderCoords_.getY();
	dest_.w = mainText->width();
	dest_.h = mainText->height();
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
	mainText = buttonEnter_;
	buttonSelected_ = true;
}

void MenuButton::exited() {
	mainText = button_;
	buttonSelected_ = false;
}

void MenuButton::pressed() {
	mainText = buttonPressed_;
	std::cout << "Mamawebaaaaso";
}
