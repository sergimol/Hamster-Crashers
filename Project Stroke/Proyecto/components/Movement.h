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

		keymap.insert({ UP, false });
		keymap.insert({ DOWN, false });
		keymap.insert({ RIGHT, false });
		keymap.insert({ LEFT, false });
	}

	void update() override {
		if (ih().keyDownEvent() || ih().keyUpEvent()) {
			auto& vel = tr_->getVel();

			if (ih().isKeyDown(SDL_SCANCODE_UP))
				keymap.at(UP) = true;
			else if(ih().isKeyUp(SDL_SCANCODE_UP))
				keymap.at(UP) = false;

			if (ih().isKeyDown(SDL_SCANCODE_DOWN))
				keymap.at(DOWN) = true;
			else if (ih().isKeyUp(SDL_SCANCODE_DOWN))
				keymap.at(DOWN) = false;

			if (ih().isKeyDown(SDL_SCANCODE_RIGHT))
				keymap.at(RIGHT) = true;
			else if(ih().isKeyUp(SDL_SCANCODE_RIGHT))
				keymap.at(RIGHT) = false;

			if (ih().isKeyDown(SDL_SCANCODE_LEFT))
				keymap.at(LEFT) = true;
			else if (ih().isKeyUp(SDL_SCANCODE_LEFT))
				keymap.at(LEFT) = false;

			if (keymap.at(UP)) {
				vel.setY(-mov_);
			}
			else if (keymap.at(DOWN)) {
				vel.setY(mov_);
			}
			else {
				vel.setY(0);
			}

			if (keymap.at(RIGHT)) {
				vel.setX(mov_);
				tr_->getFlip() = false;
			}
			else if (keymap.at(LEFT)) {
				vel.setX(-mov_);
				tr_->getFlip() = true;
			}
			else {
				vel.setX(0);
			}


			/*if(ih().isKeyDown(SDL_SCANCODE_UP))
				vel.setY(-mov_);
			else if(ih().isKeyDown(SDL_SCANCODE_DOWN)) {
				vel.setY(mov_);
			}
			else {
				vel.setY(0);
			}

			if (ih().isKeyDown(SDL_SCANCODE_RIGHT))
				vel.setX(mov_);
			else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				vel.setX(-mov_);
			}
			else {
				vel.setX(0);
			}*/

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
	const enum KEYS {
		UP, DOWN, LEFT, RIGHT
	};
	std::map<KEYS, bool> keymap;
};

