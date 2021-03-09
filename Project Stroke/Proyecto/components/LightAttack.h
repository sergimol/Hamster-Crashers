#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "Transform.h"

class LightAttack : public Component {
public:
	LightAttack() :
		tr_(nullptr),w_(60), h_(30), cooldown_(350), time_(sdlutils().currRealTime())/*, attackSound_(sdlutils().soundEffects().at("lightAttack"))*/ {
	}
	virtual ~LightAttack() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().mouseButtonEvent()) {
			if (ih().getMouseButtonState(ih().LEFT) == 1 && sdlutils().currRealTime() > time_ + cooldown_) {

				auto size = tr_->getW();
				auto& pos = tr_->getPos();


				SDL_Rect rect;
				rect.w = w_;
				rect.h = h_;
				rect.x = pos.getX() + size/2/* * orientation*/;
				rect.y = pos.getY();


				//this.anims.play(pegarse)
				//attackSound_.play();

				time_ = sdlutils().currRealTime();
			}
		}
	}

private:
	Transform* tr_;
	short unsigned int w_, h_;
	long unsigned int cooldown_, time_;
	//SoundEffect& attackSound_;
}
;