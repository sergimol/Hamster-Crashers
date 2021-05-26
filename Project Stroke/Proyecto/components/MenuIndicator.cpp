#include "MenuIndicator.h"
#include "MenuButtonManager.h"


MenuIndicator::MenuIndicator(std::string n, Vector2D position, int stateNum) :
	indicatorName_(n),
	renderCoords_(position),
	stateNumber_(stateNum)
{
	// Volúmenes
	if (indicatorName_ == "musicBar") {
		for (int i = 0; i <= 10; ++i) {
			possibleTextures_.push_back(&sdlutils().images().at(indicatorName_ + to_string(i)));
			texturesCount_++;
		}

		indicatorIndex_ = sdlutils().volumes().getX() * 10;
		indicator_ = possibleTextures_[indicatorIndex_];
	}

	else if (indicatorName_ == "fxBar") {
		for (int i = 0; i <= 10; ++i) {
			possibleTextures_.push_back(&sdlutils().images().at(indicatorName_ + to_string(i)));
			texturesCount_++;
		}

		indicatorIndex_ = sdlutils().volumes().getY() * 10;
		indicator_ = possibleTextures_[indicatorIndex_];
	}

	// Resoluciones
	else if (indicatorName_ == "resolutionIndicator") {
		for (int i = 0; i < RESOLUTIONSCOUNT; ++i) {
			possibleTextures_.push_back(&sdlutils().images().at(sdlutils().resolutionString(i)));
			texturesCount_++;
		}

		indicatorIndex_ = sdlutils().resolutionIndex();
		indicator_ = possibleTextures_[indicatorIndex_];
	}
	else if (indicatorName_ == "p") {
		for (int i = 1; i <= 4; ++i) {
			possibleTextures_.push_back(&sdlutils().images().at(indicatorName_ + to_string(i)));
			texturesCount_++;
		}

		indicatorIndex_ = 0;
		indicator_ = possibleTextures_[indicatorIndex_];
	}
	else {
		indicator_ = &sdlutils().images().at(indicatorName_);
	}

	dest_.x = renderCoords_.getX();
	dest_.y = renderCoords_.getY();
	dest_.w = indicator_->width();
	dest_.h = indicator_->height();
}

void MenuIndicator::init() {
	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
}

void MenuIndicator::render() {
	if (state_->getState() == stateNumber_) {
		indicator_->render(dest_);
	}
}

void MenuIndicator::updateTexture(bool isUp)
{
	if (isUp)
		indicatorIndex_++;
	else
		indicatorIndex_--;

	if (indicatorIndex_ >= texturesCount_)
		indicatorIndex_ = 0;
	else if (indicatorIndex_ < 0)
		indicatorIndex_ = texturesCount_ - 1;

	indicator_ = possibleTextures_[indicatorIndex_];
}

void MenuIndicator::reset()
{
	// Volúmenes
	if (indicatorName_ == "musicBar" || indicatorName_ == "fxBar") {
		indicatorIndex_ = 5;
		indicator_ = possibleTextures_[indicatorIndex_];
	}

	// Resoluciones
	else if (indicatorName_ == "resolutionIndicator") {
		indicatorIndex_ = RESOLUTIONSCOUNT - 1;
		indicator_ = possibleTextures_[indicatorIndex_];
	}
	else if (indicatorName_ == "p") {
		indicatorIndex_ = 0;
		indicator_ = possibleTextures_[indicatorIndex_];
	}
}

void MenuIndicator::moveX(bool isRight) {
	if (isRight)
		dest_.x += 450;
	else
		dest_.x -= 450;
}

// Para mover los indicadores del menu de seleccion de hamsters
void MenuIndicator::moveToButton(int but)
{
	// Abra cadabra
	dest_.x = 140 + 450 * but;
}
