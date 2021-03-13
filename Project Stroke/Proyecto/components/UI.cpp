#include "UI.h"

UI::UI(std::string n) :
	face_(&sdlutils().images().at(n + "Head1")), //
	heart_(&sdlutils().images().at("heart1")),
	bar_(&sdlutils().images().at("bar")),
	scale(2),
	name(n),
	barLenghtInit(200),
	barLenght(200)
{
	renderPosHead = Vector2D(50, 50);	// Vector2D(sdlutils().width() / 4, 50);
	renderPosHeart = renderPosHead - Vector2D(10, -20);
	renderPosBar = renderPosHead + Vector2D(25, 10);
	dest = build_sdlrect(renderPosHead, face_->width() * 1.5 * scale, face_->height() * 1.5 * scale);
	dest2 = build_sdlrect(renderPosHeart, heart_->width() * scale, heart_->height() * scale);
	dest3 = build_sdlrect(renderPosBar, barLenght, bar_->height() * scale);
}

void UI::render() {
	bar_->render(dest3);
	face_->render(dest);
	heart_->render(dest2);
}

//Si el hamster muere cambiar textura a muerto
void UI::dep() {
	heart_ = &sdlutils().images().at("heart3");
	face_ = &sdlutils().images().at(name + "Head2");
}

void UI::bar(float objetivo) {
	int maxLife = entity_->getComponent<Life>()->getMaxLife();	//Obtenemos la vida maxima de la entidad
	int damageRecieved = (objetivo / maxLife) * barLenghtInit;					//Calculamos el daño relativo a lo que es nuestra 'bar'
	barLenght += damageRecieved;
	dest3 = build_sdlrect(renderPosBar, barLenght, bar_->height() * scale);
}