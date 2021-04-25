#include "MenuButton.h"


MenuButton::MenuButton(std::string n, Vector2D position) :
	name(n),
	button_(&sdlutils().images().at(n + "Button")),
	//	buttonEnter_(&sdlutils().images().at(n + "ButtonEnter")),
		//buttonPressed_(&sdlutils().images().at(n + "ButtonPressed")),
	mainText(button_),
	renderCoords(position)
{
	dest.x = renderCoords.getX();
	dest.y = renderCoords.getY();
	dest.w = mainText->width();
	dest.h = mainText->height();
}

void MenuButton::render() {
	//Renderizamos el boton
	mainText->render(dest);

	if (!buttonSelected)
		mainText = button_;
	buttonSelected = false;	//Despues de renderizar, devolvemos el estado normal
}

void MenuButton::selected() {
	mainText = buttonEnter_;
	buttonSelected = true;
}

void MenuButton::pressed() {
	mainText = buttonPressed_;
}
