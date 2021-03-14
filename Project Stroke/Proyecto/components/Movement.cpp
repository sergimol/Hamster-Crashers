#include "Movement.h"
#include "Stroke.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

void Movement:: init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);

	keymap.insert({ UP, false });
	keymap.insert({ DOWN, false });
	keymap.insert({ RIGHT, false });
	keymap.insert({ LEFT, false });
	keymap.insert({ SPACE, false });

}

void Movement:: update() {

	auto& vel = tr_->getVel();
	auto& state = hms_->getState();
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
		state = IDLE;
	}
	else if (state == IDLE || state == MOVING || state == JUMPING) {
		vel.setX(lerp(goalVel_.getX(), vel.getX(), 0.5));
		vel.setY(lerp(goalVel_.getY(), vel.getY(), 0.5));
		state = MOVING;
	}

	if ((state == IDLE || state == MOVING) && keymap.at(SPACE)) {
		tr_->setVelZ(tr_->getVelZ() + jump_);
		if (jump_ < 5) jump_ += 1.2;
		state = JUMPING;
	}
	if (tr_->getZ() < 0) {
		keymap.at(SPACE) = false;
		jump_ = 0;
		tr_->setVelZ(0);
		tr_->setZ(0);
		state = IDLE;
	}
}

float Movement::lerp(float a, float b, float f)
{
	return (a + f * (b - a));
}