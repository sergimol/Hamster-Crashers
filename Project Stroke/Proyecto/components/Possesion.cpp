#include "Possesion.h"
#include "UI.h"
#include "../sdlutils/InputHandler.h"
#include "KeyGame.h"
#include "../ecs/Manager.h"

void Possesion::init() {
	active_ = false;
	//start();
}

void Possesion::render() {
	lineH->render(lineHPos);
	lineV->render(lineVPos);
}

void Possesion::update() {
	if (ih().keyDownEvent()) {
		key->getComponent<KeyGame>()->hitSkillCheck();
	}
}

void Possesion::onEnable() {
	start();
}

void Possesion::onDisable() {
	misstakes = 0;
	possesed = nullptr;
}

void Possesion::start() {
	assert(possesed != nullptr);
	Vector2D aux = possesed->getComponent<UI>()->getBarPos();
	
	Vector2D pos = Vector2D(aux.getX() + LINE_OFFSET_X, aux.getY() + LINE_OFFSET_Y);
	lineHPos = build_sdlrect(pos, LINE_SIZE_X, LINE_SIZE_Y);

	pos = Vector2D(aux.getX() + V_LINE_OFFSET_X, aux.getY() + V_LINE_OFFSET_Y);
	lineVPos = build_sdlrect(pos, V_LINE_SIZE_X, V_LINE_SIZE_Y);

	key = entity_->getMngr()->addEntity();
	key->addComponent<Transform>(Vector2D(aux.getX() + LINE_OFFSET_X, aux.getY() + V_LINE_OFFSET_Y), Vector2D(BOX_INI_VEL_X, 0), BOX_SIZE_X, BOX_SIZE_Y, 0);
	key->addComponent<KeyGame>(lineVPos, lineHPos, misstakes);
}
