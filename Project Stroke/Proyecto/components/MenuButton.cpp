#include "MenuButton.h"


MenuButton::MenuButton(std::string n, Vector2D position) :
	buttonName(n),
	renderCoords(position)
{
	button_ = &sdlutils().images().at(buttonName + "Button");
	buttonEnter_ = &sdlutils().images().at(buttonName + "ButtonEnter");

	mainText = button_;

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
	//buttonSelected = false;	//Despues de renderizar, devolvemos el estado normal
}

void MenuButton::selected() {
	mainText = buttonEnter_;
	buttonSelected = true;
}

void MenuButton::pressed() {
	mainText = buttonPressed_;
	std::cout << "Mamawebaaaaso";
}
