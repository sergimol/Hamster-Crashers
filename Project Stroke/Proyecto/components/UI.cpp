#include "UI.h"

UI::UI(std::string n, int pos) :
	face_(&sdlutils().images().at(n + "Head1")), //
	scale(2),
	name(n),
	position(pos)
{
	//Si se trata de un hamster
	if (position < 4) {
		//Variables
		barLenghtInit = barLenght = 300;
		bar_ = &sdlutils().images().at("bar");

		//Posiciones de los elementos de la UI
		renderPosHead = Vector2D((sdlutils().width() / 4) * position + 50, 50);
		renderPosBar = renderPosHead + Vector2D(25, 10);

		//DestRects
		dest = build_sdlrect(renderPosHead, face_->width() * 1.5 * scale, face_->height() * 1.5 * scale);

	}//Si se trata de un boss
	else {
		//Variables
		barLenghtInit = barLenght = 500;
		bar_ = &sdlutils().images().at("barEnemy");

		//Posiciones de los elementos de la UI
		renderPosHead = Vector2D((sdlutils().width() / 4) * 1.5 + 25, sdlutils().height() - 100);
		renderPosBar = renderPosHead + Vector2D(25, 10);

		//DestRects
		dest = build_sdlrect(renderPosHead, face_->width() * 1.5 * scale, face_->height() * 1.5 * scale);
	}
	dest3 = build_sdlrect(renderPosBar, barLenght, bar_->height() * scale);
}

void UI::init() {
	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void UI::render() {
	//Renderizamos la barra, la cara del hamster y su corazon
	if (state_->getState() != GameStates::MAINMENU && state_->getState() != GameStates::CONTROLS) {
		bar_->render(dest3);
		face_->render(dest);
	}
}

//Si el hamster muere cambiar textura a muerto
void UI::dep() {
	face_ = &sdlutils().images().at(name + "Head2");
	dest3 = build_sdlrect(renderPosBar, 0, bar_->height() * scale);
}

void UI::bar(float objetivo) {
	int maxLife = entity_->getComponent<EntityAttribs>()->getMaxLife();	//Obtenemos la vida maxima de la entidad
	int damageRecieved = (objetivo / maxLife) * barLenghtInit;					//Calculamos el daño relativo a lo que es nuestra 'bar'
	barLenght += damageRecieved;
	dest3 = build_sdlrect(renderPosBar, barLenght, bar_->height() * scale);
}