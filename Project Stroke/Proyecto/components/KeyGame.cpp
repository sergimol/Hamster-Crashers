#include "KeyGame.h"
#include "../utils/Collisions.h"
#include "../sdlutils/Texture.h"

void KeyGame::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	iniPos = tr_->getPos();
	setKey();
}

void KeyGame::render() {
	SDL_Rect box = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
	tx_->render(box);
}

void KeyGame::update() {
	if (!Collisions::collides(tr_->getPos(), tr_->getW(), tr_->getH(), Vector2D(), endLine.w, endLine.h)) {
		missedSkillCheck();
	}
}


void KeyGame::missedSkillCheck() {
	if(!hit)
		misstakes++;
	setKey();
	tr_->setPos(iniPos);
}

void KeyGame::hitSkillCheck() {
	if (ih().isKeyDown(key_) && Collisions::collides(tr_->getPos(), tr_->getW(), tr_->getH(), Vector2D(checkRect.x, checkRect.y), checkRect.w, checkRect.h)) {
			hit = true;
	}
	else hit = false;
}

void KeyGame::setKey() {
	int rand = sdlutils().rand().nextInt(0, 5);
	tx_ = keys[rand];
	key_ = keyCodes[rand];
}
