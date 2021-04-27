#include "ReanimationGame.h"

void ReanimationGame::init() {
	// No se habilita hasta que otro jugador lo inicia
	active_ = false;
	
	auto pos = entity_->getComponent<Transform>()->getPos();
	pos.set(pos.getX() + OFFSET_X, pos.getY() + OFFSET_Y);

	buttonPos = build_sdlrect(pos, WIDTH, HEIGHT);

	infarct_ = entity_->getComponent<InfarctedBody>();
	assert(infarct_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void ReanimationGame::update() {
	if (state_->getState() != GameStates::PAUSE) {
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(key) && !down) {
				down = true;
				progress += BEAT;
			}
		}
		else if (ih().keyUpEvent()) {
			if (ih().isKeyUp(key) && down) {
				down = false;
			}
		}

		if (sdlutils().currRealTime() > timer + TIME_BETWEEN_DROPS) {
			if (progress > 0)
				progress -= DROP;
			else
				progress = 0;

			timer = sdlutils().currRealTime();
		}

		if (progress >= MAX_PROGRESS) {
			endGame();
		}
	}

}

void ReanimationGame::render() {
	if (down) txDown_->render(buttonPos);
	else txUp_->render(buttonPos);
}

void ReanimationGame::onDisable() {
	down = false;
	progress = 0;
}

void ReanimationGame::endGame() {
	//Reseteamos variables
	down = false;
	progress = 0;
	//Desactivamos el componente
	active_ = false;
	//Reanimamos al hamster
	infarct_->reanimate();
}

void ReanimationGame::onResume() {
	timer += sdlutils().currRealTime() - timer;
}