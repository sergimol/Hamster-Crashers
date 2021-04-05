#include "Possesion.h"
#include "UI.h"

void Possesion::init() {
	active_ = false;
	start();
}

void Possesion::render() {
	line->render(gamePos);
}

void Possesion::update() {

}

void Possesion::onEnable() {
	start();

}

void Possesion::onDisable() {
	mistakes = 0;
	entity_ = nullptr;
}

void Possesion::start() {
	assert(entity_ != nullptr);
	Vector2D pos = entity_->getComponent<UI>()->getBarPos();

	gamePos = build_sdlrect(pos, LINE_SIZE_X, LINE_SIZE_Y);

}