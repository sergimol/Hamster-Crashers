// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include "../ecs/Camera.h"

#include "Gravity.h"
#include "GameStates.h"

class Transform : public Component {
public:
	Transform() :
		pos_(), vel_(), width_(), height_(), rotation_(), z_(), flip_(), scaleCollideW(), scaleCollideH(), grv_(nullptr), state_(nullptr) {
	}

	Transform(Vector2D pos, Vector2D vel, float width, float height,
		float rotation, float scaleW, float scaleH) :
		pos_(pos), //
		vel_(vel), //
		width_(width), //
		height_(height), //
		rotation_(rotation),
		z_(0),
		velZ_(0),
		flip_(false),
		scaleCollideW(scaleW),
		scaleCollideH(scaleH),
		grv_(nullptr)
	{
		rectCollide.w = (width_ * scaleCollideW);
		rectCollide.h = (height_ * scaleCollideH);
		rectCollide.x = pos.getX() + (width * ((1 - scaleCollideW) / 2));
		rectCollide.y = pos.getY() + (height * ((1 - scaleCollideH) / 2));

		rectCollideFeet.w = (width_ * scaleCollideW);
		rectCollideFeet.h = (height_ * scaleCollideH / 3);
		rectCollideFeet.x = pos.getX() + (width * ((1 - scaleCollideW) / 2));
		rectCollideFeet.y = pos.getY() + (height * ((1 - scaleCollideH) / 2) + height_ * scaleCollideH);
	}

	Transform(Vector2D pos, Vector2D vel, float width, float height,
		float rotation, float z, bool flip, float scaleW, float scaleH) :
		pos_(pos), //
		vel_(vel), //
		width_(width), //
		height_(height), //
		rotation_(rotation),
		z_(z),
		velZ_(0),
		flip_(flip),
		scaleCollideW(scaleW),
		scaleCollideH(scaleH),
		grv_(nullptr)
	{
		rectCollide.w = (width_ * scaleCollideW);
		rectCollide.h = (height_ * scaleCollideH);
		rectCollide.x = pos.getX() + (width * ((1 - scaleCollideW) / 2));
		rectCollide.y = pos.getY() + (height * ((1 - scaleCollideH) / 2));

		rectCollideFeet.w = (width_ * scaleCollideW);
		rectCollideFeet.h = (height_ * scaleCollideH / 3);
		rectCollideFeet.x = pos.getX() + (width * ((1 - scaleCollideW) / 2));
		rectCollideFeet.y = pos.getY() + (height * ((1 - scaleCollideH) / 2) + height_ * scaleCollideH);
	}

	void init() override {
		state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
		assert(state_ != nullptr);
	}

	void setGravity(Gravity* g) {
		grv_ = g;
	}

	virtual ~Transform() {
	}

	bool& getFlip() {
		return flip_;
	}

	float& getZ() {
		return z_;
	}

	float& getVelZ() {
		return velZ_;
	}

	void setVelZ(float velZ) {
		velZ_ = velZ;
	}

	Vector2D& getPos() {
		return pos_;
	}

	Vector2D& getVel() {
		return vel_;
	}

	float getH() const {
		return height_;
	}

	void setH(float height) {
		height_ = height;
	}

	float getW() const {
		return width_;
	}

	void setW(float width) {
		width_ = width;
	}

	float getRot() const {
		return rotation_;
	}

	float getScaleW() const {
		return scaleCollideW;
	}

	float getScaleH() const {
		return scaleCollideH;
	}

	SDL_Rect getRectCollide() const {
		return rectCollide;
	}	
	
	SDL_Rect getRectCollideFeet() const {
		return rectCollideFeet;
	}

	void setRot(float rot) {
		rotation_ = rot;
	}

	void setPos(Vector2D posNew) {
		pos_ = posNew;
	}

	void setVel(Vector2D velNew) {
		vel_ = velNew;
	}

	void setFloor(int f) {
		floor_ = f;
	}

	int getFloor() {
		return floor_;
	}

	void update() override {
		if (state_->getState() == GameStates::RUNNING) {
			//Movidas de gravedad
			if (grv_ != nullptr && grv_->isActive()) {
				z_ += velZ_;
			}

			pos_ = pos_ + vel_;

			rectCollide.x = pos_.getX() + (width_ * ((1 - scaleCollideW) / 2));
			rectCollide.y = pos_.getY() + (height_ * ((1 - scaleCollideH) / 2));

			rectCollideFeet.x = pos_.getX() + (width_ * ((1 - scaleCollideW) / 2));
			rectCollideFeet.y = pos_.getY() + (height_ * ((1 - scaleCollideH) / 2) + height_ * scaleCollideH);
		}
	}

	void render() override {
		Vector2D p = Vector2D(rectCollide.x - entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam().x,
			rectCollide.y - entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam().y);
		SDL_Rect loc = rectCollide;
		loc.x = p.getX();
		loc.y = p.getY();

		p = Vector2D(rectCollideFeet.x - entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam().x,
			rectCollideFeet.y - entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam().y);
		SDL_Rect loc2 = rectCollideFeet;
		loc2.x = p.getX();
		loc2.y = p.getY();

		if (debug) {
			SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 255);

			SDL_RenderDrawRect(sdlutils().renderer(), &loc);
			SDL_RenderDrawRect(sdlutils().renderer(), &loc2);
		}
	}

private:
	Vector2D pos_;
	Vector2D vel_;
	Gravity* grv_;
	GameStates* state_;
	float width_;
	float height_;
	float rotation_;
	float z_;
	float velZ_;
	bool flip_;
	float scaleCollideW;
	float scaleCollideH;
	SDL_Rect rectCollide;
	SDL_Rect rectCollideFeet;
	//Z del suelo en el que se encuentra
	int floor_;
};

