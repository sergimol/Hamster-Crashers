#include "HeartUI.h"
#include "Animator.h"

HeartUI::HeartUI(std::string n, int pos) :
	heart_(&sdlutils().images().at("heart1")),
	scale(2),
	name(n),
	position(pos),
	latency(10000)
{
	//Posiciones de los elementos de la UI
	renderPosHeart = Vector2D((sdlutils().width() / 4) * position + 50, 50) - Vector2D(10, -20);

	//DestRects
	dest2 = build_sdlrect(renderPosHeart, heart_->width() * scale, heart_->height() * scale);
}

void HeartUI::init() {
	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);
}

void HeartUI::update() {
	if (sdlutils().currRealTime() > timeAux + latency) {
		timeAux = sdlutils().currRealTime();
		//anim_->play(sdlutils().anims().at("miCoraçaoPalpita"));
		anim_->play(sdlutils().anims().at("sardinilla_idle_ghost"));

	}
}

void HeartUI::render() {
	//Renderizamos su corazon
	heart_->render(dest2);
}

//Si el hamster muere cambiar textura a muerto
void HeartUI::dep() {
	heart_ = &sdlutils().images().at("heart3");
}

//Incrementa o disminuye la latencia en un 'aux'%
void HeartUI::increaseLatency(float aux) {
	latency *= aux;
}
