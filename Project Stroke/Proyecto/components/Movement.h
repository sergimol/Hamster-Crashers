#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>
#include <cmath>

#include "Transform.h"



class Movement : public Component {
public:
	Movement() :
		tr_(nullptr), speed_(7.0f, 3.5f), goalVel_(0,0), dt_(0.0f), time_(sdlutils().currRealTime()){
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

		dt_ = (sdlutils().currRealTime() - time_) / 1000;
		time_ = sdlutils().currRealTime();
		
		auto& vel = tr_->getVel();
		if (ih().keyDownEvent() || ih().keyUpEvent()) {
			
			
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

			Vector2D dir = Vector2D(0,0);

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

			if(dir.magnitude() != 0)
				dir = dir.normalize();
			
			goalVel_ = Vector2D(dir.getX() * speed_.getX(), dir.getY() * speed_.getY());

			vel = goalVel_;

			//vel.setX(lerp(goalVel_.getX(),  vel.getX(), dt_ * 50));
			//vel.setY(lerp(goalVel_.getY(), vel.getY(), dt_ * 50));

			//std::cout << tr_->getPos() << std::endl;
		}
		/*else {
			vel.setX(lerp(0, vel.getX(), dt_ * 50));
			vel.setY(lerp(0, vel.getY(), dt_ * 50));
		}*/
		//std::cout << dt_ << std::endl;
	}


	/*float lerp(float goal, float current, float dt) {
		float diff = goal - current;

		if (diff > dt)
			return current + dt;
		if (diff < dt)
			return current - dt;

		return goal;
	}*/

	float lerp(float a, float b, float f)
	{
		return (a + f*(b-a));
	}

private:
	Transform* tr_;
	Vector2D speed_, goalVel_;
	float dt_, time_;
	const enum KEYS {UP, DOWN, LEFT, RIGHT};
	std::map<KEYS, bool> keymap;
};

