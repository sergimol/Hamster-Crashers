#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"

#include "Transform.h"

class Movement : public Component {
public:
	Movement() :
		tr_(nullptr), mov_(5.0f) {
	}
	virtual ~Movement() {
	}
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			auto& pos = tr_->getPos();

			if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				pos.setY(pos.getY() - mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_DOWN)) {
				pos.setY(pos.getY() + mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				pos.setX(pos.getX() - mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				pos.setX(pos.getX() + mov_);
			}
		}
	}

private:
	Transform* tr_;
	float mov_;
};

