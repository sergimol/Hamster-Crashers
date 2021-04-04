#include "HeartUI.h"
#include "Animator.h"

HeartUI::HeartUI(std::string n, int pos) :
	heart_(&sdlutils().images().at("heart1")),
	scale(2),
	name(n),
	position(pos),
	latency(1000),
	asciende(false),
	desciende(false),
	alive(true)
{
	//Posiciones de los elementos de la UI
	renderPosHeart = Vector2D((sdlutils().width() / 4) * position + 50, 50) - Vector2D(10, -20);

	//DestRects
	dest = build_sdlrect(renderPosHeart, heart_->width() * scale, heart_->height() * scale);
	destAux = dest;
}

void HeartUI::update() {
	if (alive) {
		if (sdlutils().currRealTime() > timeAux + latency) {
			timeAux = sdlutils().currRealTime();

			asciende = true;
			//Lo vamos haciendo más grande
		}

		if (asciende) {
			destAux.h += 1;
			destAux.w += 1;

			if (destAux.h > dest.h * 1.3) {
				desciende = true;
				asciende = false;
			}
		}

		if (desciende) {
			destAux.h -= 1;
			destAux.w -= 1;

			if (destAux.h == dest.h) {
				destAux.h = dest.h;
				destAux.w = dest.w;
				desciende = false;
			}
		}
	}
}

void HeartUI::render() {
	//Renderizamos su corazon
	heart_->render(destAux);
}

//Si el hamster muere cambiar textura a muerto
void HeartUI::dep() {
	heart_ = &sdlutils().images().at("heart3");
	alive = false;
}

//Incrementa o disminuye la latencia en un 'aux'%
void HeartUI::increaseLatency(float aux) {
	latency *= aux;
}
