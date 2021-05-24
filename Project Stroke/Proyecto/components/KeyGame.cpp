#include "KeyGame.h"
#include "../utils/Collisions.h"
#include "../sdlutils/Texture.h"

void KeyGame::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	assert(poss_ != nullptr);

	iniPos = tr_->getPos();

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void KeyGame::render() {
	SDL_Rect box = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
	if (!down)
		tx_->render(box);
	else
		txDown_->render(box);
}

void KeyGame::update() {
	if (state_->getState() == GameStates::RUNNING && tr_->getPos().getX() > trail.x + trail.w) {
		goBack();
	}

	if (pressed && sdlutils().currRealTime() > timer + pressedTime) {
		down = false;
	}
}

// Devuelve a la posición inicial y notifica a Possesion
void KeyGame::goBack() {
	tr_->getPos() = iniPos;
	poss_->reachedEnd();
	pressed = false;
}

//Comprueba si es un acierto y se anima
bool KeyGame::hitSkillCheck() {
	if (!pressed) {
		pressed = true;
		down = true;
		timer = sdlutils().currRealTime();
	}
	float x = tr_->getPos().getX(), y = tr_->getPos().getY();
	auto* cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>();
	x -= cam->getCamPos().getX() / 2.0f;
	y -= cam->getCamPos().getY() / 2.0f;

	return Collisions::collides(Vector2D(x, y), tr_->getW(), tr_->getH(), 
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
