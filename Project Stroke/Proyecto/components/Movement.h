#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>

#include "Transform.h"

class Movement : public Component {
public:
	Movement() :
		tr_(nullptr), mov_(7.0f) {
	}
	virtual ~Movement() {
	}
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent() || ih().keyUpEvent()) {
			auto& vel = tr_->getVel();

			if (ih().isKeyDown(SDL_SCANCODE_UP) && ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				vel.set(- mov_, - mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_UP) && ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				vel.set(mov_, - mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				vel.set(0, - mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_DOWN) && ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				vel.set(- mov_, mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_DOWN) && ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				vel.set(mov_, mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_DOWN)) {
				vel.set(0, mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				vel.set(- mov_, 0);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				vel.set(mov_, 0);
			}
			else {
				vel.set(0, 0);
			}

			/*
				auto& pos = tr_->getPos();
			if (ih().isKeyDown(SDL_SCANCODE_UP) && ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				pos.set(pos.getX() - mov_, pos.getY() - mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_UP) && ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				pos.set(pos.getX() + mov_, pos.getY() - mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				pos.setY(pos.getY() - mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_DOWN) && ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				pos.set(pos.getX() - mov_, pos.getY() + mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_DOWN) && ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				pos.set(pos.getX() + mov_, pos.getY() + mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_DOWN)) {
				pos.setY(pos.getY() + mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				pos.setX(pos.getX() - mov_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				pos.setX(pos.getX() + mov_);
			}*/
		}
	}

private:
	Transform* tr_;
	float mov_;
};

