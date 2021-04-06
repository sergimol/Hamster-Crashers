#include "KeyGame.h"
#include "../utils/Collisions.h"
#include "../sdlutils/Texture.h"

void KeyGame::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	assert(poss_ != nullptr);

	iniPos = tr_->getPos();
}

void KeyGame::render() {
	SDL_Rect box = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
	tx_->render(box);
}

void KeyGame::update() {
	if (tr_->getPos().getX() > trail.x + trail.w) {
		goBack();
	}
}

void KeyGame::goBack() {
	tr_->getPos() = iniPos;
	poss_->reachedEnd();
}

//Comprueba si es un acierto
bool KeyGame::hitSkillCheck() {
	return Collisions::collides(tr_->getPos(), tr_->getW(), tr_->getH(), 
						Vector2D(hitmarker.x, hitmarker.y), hitmarker.w, hitmarker.h);
}

//void KeyGame::setKey() {
//	int rand = sdlutils().rand().nextInt(0, 5);
//	tx_ = keys[rand];
//	key_ = keyCodes[rand];
//}

//void KeyGame::missedSkillCheck() {
//	if(!hit)
//		misstakes++;
//	setKey();
//	tr_->setPos(iniPos);
//}
