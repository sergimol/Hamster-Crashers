#include "KeyGame.h"
#include "../utils/Collisions.h"
#include "../sdlutils/Texture.h"

void KeyGame::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	assert(poss_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void KeyGame::render() {
	SDL_Rect box = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
	if (!down_)
		tx_->render(box);
	else
		txDown_->render(box);
}

void KeyGame::update() {
	if (state_->getState() == GameStates::RUNNING){
		if (dirX_ > 0) progress_ += speed_ / 2;
		else if (dirX_ < 0) progress_ += 1.5f * speed_;
		else progress_ += speed_;


		if (tr_->getPos().getX() > hitmarker_.x + hitmarker_.w) {
			goBack();
		}

		if (pressed_ && sdlutils().currRealTime() > timer_ + pressedTime_) {
			pressed_ = false;
			down_ = false;
		} 
	}
}

// Devuelve a la posición inicial y notifica a Possesion
void KeyGame::goBack() {
	tr_->getPos() = Vector2D(trail_.x, trail_.y);
	poss_->reachedEnd();
	pressed_ = false;
	progress_ = 0;
}

//Comprueba si es un acierto y se anima
bool KeyGame::hitSkillCheck() {
	pressed_ = true;
	down_ = true;
	timer_ = sdlutils().currRealTime();
	
	float x = tr_->getPos().getX(), y = tr_->getPos().getY();

	return Collisions::collides(Vector2D(x, y), tr_->getW(), tr_->getH(), 
						Vector2D(hitmarker_.x, hitmarker_.y), hitmarker_.w, hitmarker_.h);
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

void KeyGame::updateGamePos(const SDL_Rect& hit, const SDL_Rect& trai, int dir) {
	dirX_ = dir;
	
	hitmarker_ = hit;
	trail_ = trai;

	auto newPos = tr_->getPos();
	newPos.setX(trail_.x + tr_->getW() / 2 + progress_);
	newPos.setY(trail_.y - tr_->getH() / 2);
	
	tr_->setPos(newPos);
}