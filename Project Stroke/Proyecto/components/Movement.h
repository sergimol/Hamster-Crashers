#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>
#include <cmath>

#include "Transform.h"
#include "Stroke.h"



class Movement : public Component {
public:
	Movement() :
		tr_(nullptr), speed_(7.0f, 3.5f), goalVel_(0, 0), jump_(0) {
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
		keymap.insert({ SPACE, false });

	}

	void update() override {

		auto& vel = tr_->getVel();
		if (ih().keyDownEvent() || ih().keyUpEvent()) {

			if (ih().isKeyDown(SDL_SCANCODE_UP) || ih().isKeyDown(SDLK_w))
				keymap.at(UP) = true;
			else if (ih().isKeyUp(SDL_SCANCODE_UP) && ih().isKeyUp(SDLK_w))
				keymap.at(UP) = false;

			if (ih().isKeyDown(SDL_SCANCODE_DOWN) || ih().isKeyDown(SDLK_s))
				keymap.at(DOWN) = true;
			else if (ih().isKeyUp(SDL_SCANCODE_DOWN) && ih().isKeyUp(SDLK_s))
				keymap.at(DOWN) = false;

			if (ih().isKeyDown(SDL_SCANCODE_RIGHT) || ih().isKeyDown(SDLK_d))
				keymap.at(RIGHT) = true;
			else if (ih().isKeyUp(SDL_SCANCODE_RIGHT) && ih().isKeyUp(SDLK_d))
				keymap.at(RIGHT) = false;

			if (ih().isKeyDown(SDL_SCANCODE_LEFT) || ih().isKeyDown(SDLK_a))
				keymap.at(LEFT) = true;
			else if (ih().isKeyUp(SDL_SCANCODE_LEFT) && ih().isKeyUp(SDLK_a))
				keymap.at(LEFT) = false;

			Vector2D dir = Vector2D(0, 0);

			if (!keymap.at(SPACE) && ih().isKeyDown(SDLK_SPACE)) {
				keymap.at(SPACE) = true;
				jump_ = -5;
				entity_->getComponent<Stroke>()->increaseChance(2, this);
			}

			if (keymap.at(UP)) {
				dir.setY(-1.0f);
			}
			else if (keymap.at(DOWN)) {
				dir.setY(1.0f);
			}

			if (keymap.at(RIGHT)) {
				dir.setX(1.0f);
				tr_->getFlip() = false;
			}
			else if (keymap.at(LEFT)) {
				dir.setX(-1.0f);
				tr_->getFlip() = true;
			}

			if (dir.magnitude() != 0) {
				dir = dir.normalize();

				goalVel_ = Vector2D(dir.getX() * speed_.getX(), dir.getY() * speed_.getY());
			}
		}

		if (!keymap.at(UP) && !keymap.at(DOWN) && !keymap.at(LEFT) && !keymap.at(RIGHT)) {
			vel.setX(lerp(vel.getX(), 0, 0.1));
			vel.setY(lerp(vel.getY(), 0, 0.1));
		}
		else {
			vel.setX(lerp(goalVel_.getX(), vel.getX(), 0.5));
			vel.setY(lerp(goalVel_.getY(), vel.getY(), 0.5));
		}

		if (keymap.at(SPACE) && jump_ != 0) {
			tr_->setVelZ(tr_->getVelZ() + jump_);
			if (jump_ < 5) jump_ += 1.2;
		}
		if (tr_->getZ() < 0) {
			keymap.at(SPACE) = false;
			jump_ = 0;
			tr_->setVelZ(0);
			tr_->setZ(0);
		}
	}

	float lerp(float a, float b, float f)
	{
		return (a + f * (b - a));
	}

private:
	Transform* tr_;
	Vector2D speed_, goalVel_;
	float jump_;
	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	std::map<KEYS, bool> keymap;
};

