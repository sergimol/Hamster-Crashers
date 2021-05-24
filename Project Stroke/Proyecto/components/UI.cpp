#include "UI.h"
#include "../ecs/Manager.h"

UI::UI(std::string n, int pos) :
	face_(&sdlutils().images().at(n + "Head1")), //
	hexagon_(&sdlutils().images().at("Hexagon")), //
	background_(&sdlutils().images().at("hamsBackGround")),
	scale(1),
	name(n),
	position(pos)
{
	//Si se trata de un hamster
	if (position < 4) {
		//Variables
		barLenghtInit = barLenght = 300;
		bar_ = &sdlutils().images().at("bar");

		//Posiciones de los elementos de la UI
		renderPosHead = Vector2D((sdlutils().width() / 4) * position + 70, 35);
		renderPosBar = Vector2D((sdlutils().width() / 4) * position + 125, 60);
		renderPosBack = Vector2D((sdlutils().width() / 4) * position + 30, 10);
		//DestRects
		dest = build_sdlrect(renderPosHead, face_->width()  * scale, face_->height()  * scale);
		dest2 = build_sdlrect(renderPosBack, background_->width()  * scale, background_->height()  * scale);
		dest4 = build_sdlrect(renderPosHexagon, 0, 0);
	}//Si se trata de un boss
	else {
		//Variables
		barLenghtInit = barLenght = 500;
		bar_ = &sdlutils().images().at("barEnemy");

		//Posiciones de los elementos de la UId
		renderPosHead = Vector2D((sdlutils().width() / 4) -20, sdlutils().height()-130);
		renderPosHexagon = Vector2D((sdlutils().width() / 4) - 75, sdlutils().height() - 150);
		renderPosBar = renderPosHead + Vector2D(150, 50);

		//DestRects
		dest = build_sdlrect(renderPosHead, face_->width()  * scale, face_->height()  * scale);
		dest2 = build_sdlrect(renderPosHead, 0, 0);
		dest4 = build_sdlrect(renderPosHexagon, hexagon_->width() * scale, hexagon_->height() * scale);
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
		background_->render(dest2);
		bar_->render(dest3);
		hexagon_->render(dest4);
		face_->render(dest);
	}
}

//Si el hamster muere cambiar textura a muerto
void UI::dep(std::string s) {
	face_ = &sdlutils().images().at(name + "Head" + s);
	dest3 = build_sdlrect(renderPosBar, 0, bar_->height() * scale);
}

void UI::bar(float objetivo) {
	int maxLife = entity_->getComponent<EntityAttribs>()->getMaxLife();	//Obtenemos la vida maxima de la entidad
	int damageRecieved = (objetivo / maxLife) * barLenghtInit;					//Calculamos el daño relativo a lo que es nuestra 'bar'
	//std::cout << objetivo << " " << maxLife << "\n";
	barLenght += damageRecieved;
	if(face_ == &sdlutils().images().at(name + "Head1"))
	dest3 = build_sdlrect(renderPosBar, barLenght, bar_->height() * scale);
}

void UI::resurrection() {
	face_ = &sdlutils().images().at(name + "Head1");
	dest3 = build_sdlrect(renderPosBar, barLenght, bar_->height() * scale);
}