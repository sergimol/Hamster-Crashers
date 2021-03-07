#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"

const float THRUST = 0.8f;
const float SPEEDLIMIT = 3.0f;
class FighterCtrl : public Component {
public:
	FighterCtrl() :
		tr_(nullptr) {
	}
	virtual ~FighterCtrl() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			auto& vel = tr_->getVel();
			if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				tr_->setRot(tr_->getRot() - 5.0f);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				tr_->setRot(tr_->getRot() + 5.0f);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_UP)) {				
				vel.set(vel + Vector2D(0, -1).rotate(tr_->getRot()) * THRUST);
			}

			if (vel.magnitude() > SPEEDLIMIT) {
				vel.set(vel.normalize() * SPEEDLIMIT);
			}
		}
	}

private:
	Transform* tr_;
}
;