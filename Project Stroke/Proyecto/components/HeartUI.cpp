#include "HeartUI.h"
#include "Animator.h"

float lerp(float a, float b, float f)
{
	return (a + f * (b - a));
}

HeartUI::HeartUI(std::string n, int pos) :
	heart_(&sdlutils().images().at("heart1")),
	scale(2),
	name(n),
	position(pos),
	latency(MAXLATENCY),
	latencyAux(MAXLATENCY),
	alive(true)
{
	//Posiciones de los elementos de la UI
	renderPosHeart = Vector2D((sdlutils().width() / 4) * position + 50, 50) - Vector2D(10, -20);

	//DestRects
	dest = build_sdlrect(renderPosHeart, heart_->width() * scale, heart_->height() * scale);
	destAux = dest;
}

void HeartUI::init() {
	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}


void HeartUI::update() {
	//auto posAux = entity_->getComponent<Transform>()->getPos();
	if (alive) {
		float currentState = sin((sdlutils().currRealTime() / latency));

		if (abs(currentState) < 0.2 && latencyAux > 50) {
			//latency = latencyAux;
			latency = lerp(latency, latencyAux, 0.9);
		}


		destAux.h = dest.h + abs(currentState) * 20;
		destAux.w = dest.w + abs(currentState) * 20;

		destAux.x = dest.x - (abs(currentState) * 20) / 2;
		destAux.y = dest.y - (abs(currentState) * 20) / 2;
	}
}

void HeartUI::render() {
	//Renderizamos su corazon
	if (state_->getState() != GameStates::MAINMENU && state_->getState() != GameStates::CONTROLS)
		heart_->render(destAux);
}

//Si el hamster muere cambiar textura a muerto
void HeartUI::dep() {
	heart_ = &sdlutils().images().at("heart3");
	alive = false;
}

//Si el hamster revive cambiar textura a vivo
void HeartUI::resurrection() {
	heart_ = &sdlutils().images().at("heart1");
	alive = true;
	latency = MAXLATENCY;
}

//Incrementa o disminuye la latencia en un 'aux'
void HeartUI::increaseLatency(float aux) {
	latencyAux = MAXLATENCY * (1 - aux / 100);
}