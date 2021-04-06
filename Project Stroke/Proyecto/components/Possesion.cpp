#include "Possesion.h"
#include "UI.h"

void Possesion::init() {
	active_ = false;
	//start();
}

void Possesion::render() {
	lineH->render(lineHPos);
	lineV->render(lineVPos);
}

void Possesion::update() {

}

void Possesion::onEnable() {
	start();
}

void Possesion::onDisable() {
	mistakes = 0;
	possesed = nullptr;
}

void Possesion::start() {
	assert(possesed != nullptr);
	Vector2D aux = possesed->getComponent<UI>()->getBarPos();
	
	Vector2D pos = Vector2D(aux.getX() + LINE_OFFSET_X, aux.getY() + LINE_OFFSET_Y);
	lineHPos = build_sdlrect(pos, LINE_SIZE_X, LINE_SIZE_Y);

	pos = Vector2D(aux.getX() + V_LINE_OFFSET_X, aux.getY() + V_LINE_OFFSET_Y);
	lineVPos = build_sdlrect(pos, V_LINE_SIZE_X, V_LINE_SIZE_Y);
}
