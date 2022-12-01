#include "UI.h"
#include "../ecs/Manager.h"

UI::UI(std::string n, int pos) :
	face_(&sdlutils().images().at(n + "Head1")), //
	hexagon_(&sdlutils().images().at("Hexagon")), //
	background_(&sdlutils().images().at("hamsBackGround")),
	backgroundBoss_(&sdlutils().images().at("barEnemyBack")),
	scale(1),
	name(n),
	position(pos)
{

	//Si se trata de un hamster
	if (position < 4) {
		//Variables
		barLenghtInit = barLenght = 300;
		bar_ = &sdlutils().images().at("bar");
		bar_up_ = &sdlutils().images().at("bar_up");

		//Posiciones de los elementos de la UI
		renderPosHead = Vector2D((sdlutils().width() / 4) * position + 70, 35);
		renderPosBar = Vector2D((sdlutils().width() / 4) * position + 125, 40);
		renderPosBack = Vector2D((sdlutils().width() / 4) * position + 30, 10);
		//DestRects
		dest = build_sdlrect(renderPosHead, face_->width()  * scale, face_->height()  * scale);
		dest2 = build_sdlrect(renderPosBack, background_->width()  * scale, background_->height()  * scale);
		dest4 = build_sdlrect(renderPosHexagon, 0, 0);
	}//Si se trata de un boss
	else {
		//Variables
		barLenghtInit = barLenght = 1000;
		bar_ = &sdlutils().images().at("barEnemy");

		//Posiciones de los elementos de la UId
		renderPosHead = Vector2D((sdlutils().width() / 4) -300,
									sdlutils().height()-300);
		renderPosHexagon = Vector2D((sdlutils().width() / 4) - 300,
										sdlutils().height() - 300);
		renderPosBar = renderPosHead + Vector2D(150, 150);
		renderPosBack = renderPosBar + Vector2D(0, 20);

		//DestRects
		dest = build_sdlrect(renderPosHead,
							face_->width()  * scale,
							face_->height()  * scale);
		dest2 = build_sdlrect(renderPosBack,
							 barLenght+150,
							 backgroundBoss_->height() * scale);
		dest4 = build_sdlrect(renderPosHexagon,
							  hexagon_->width() * scale,
							  hexagon_->height() * scale);
	}
	dest3 = build_sdlrect(renderPosBar, barLenght, bar_->height() * scale);
}

void UI::init() {
	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void UI::update()
{
	if (state_->getState() == GameStates::RUNNING)
	{
		// Si el aumento de vida esta activado
		if (life_up && sdlutils().currRealTime() >= timer_ + lifeUp_Time_) {
			life_up = false;
			timer_ = sdlutils().currRealTime();
		}
	}

}

void UI::render() {
	//Renderizamos la barra, la cara del hamster y su corazon
	if (state_->getState() != GameStates::MAINMENU && state_->getState() != GameStates::CONTROLS) {
		
		if (position >= 4) // es un boss
		{
			backgroundBoss_->render(dest2);
			bar_->render(dest3);
		}
		else // Hamster
		{
			background_->render(dest2);
			if (!life_up)
				bar_->render(dest3);
			else
				bar_up_->render(dest3);
		}
		

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

void UI::setLifeUp(bool life)
{
	life_up = life;
	timer_ = sdlutils().currRealTime();
}