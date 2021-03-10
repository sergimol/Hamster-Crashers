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
		tr_(nullptr), speed(7.0f, 3.5f) {
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


			Vector2D dir = Vector2D();

			if (keymap.at(UP)) {
				//vel.setY(-speedY_);
				dir.setY(-1.0f);
			}
			else if (keymap.at(DOWN)) {
				//vel.setY(speedY_);
				dir.setY(1.0f);
			}
			else {
				//vel.setY(0);
			}

			if (keymap.at(RIGHT)) {
				//vel.setX(speedX_);
				dir.setX(1.0f);
				tr_->getFlip() = false;
			}
			else if (keymap.at(LEFT)) {
				//vel.setX(-speedX_);
				dir.setX(-1.0f);
				tr_->getFlip() = true;
			}
			else {
				//vel.setX(0);
			}

			Vector2D newVel = Vector2D(dir.getX() * speed.getX(), dir.getY() * speed.getY());
			vel = newVel;

		}
	}

private:
	Transform* tr_;
	Vector2D speed;
	const enum KEYS {
		UP, DOWN, LEFT, RIGHT
	};
	std::map<KEYS, bool> keymap;
};

