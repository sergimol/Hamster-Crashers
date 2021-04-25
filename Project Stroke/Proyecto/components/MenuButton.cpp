#include "MenuButton.h"

MenuButton::MenuButton(std::string n, Vector2D position) :
	name(n),
	button_(&sdlutils().images().at(n + "Button")),
//	buttonEnter_(&sdlutils().images().at(n + "ButtonEnter")),
	//buttonPressed_(&sdlutils().images().at(n + "ButtonPressed")),
	mainText(button_),
	renderCoords(position),
	scale(2)
{
	dest.x = renderCoords.getX();
	dest.y = renderCoords.getY();
	dest.w = mainText->width();
	dest.h = mainText->height();
}

void MenuButton::render() {
	//Renderizamos el boton
	mainText->render(dest);
}

void MenuButton::selected() {
	mainText = buttonEnter_;
}

void MenuButton::pressed() {
	mainText = buttonPressed_;
}

void MenuButton::deselected() {
	mainText = button_;
}