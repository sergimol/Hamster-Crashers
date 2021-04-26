// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"

#include "Gravity.h"

class Transform : public Component {
public:
	Transform() :
		pos_(), vel_(), width_(), height_(), rotation_(), z_(), flip_(),scaleCollideW(),scaleCollideH() {
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
		scaleCollideH(scaleH)
	{
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
		scaleCollideH(scaleH)
	{
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
		if (grv_ != nullptr && grv_->isActive())
			z_ += velZ_;
		//pos_.setY(pos_.getY() - z_);
		pos_ = pos_ + vel_;
	}



private:
	Vector2D pos_;
	Vector2D vel_;
	Gravity* grv_;
	float width_;
	float height_;
	float rotation_;
	float z_;
	float velZ_;
	bool flip_;
	float scaleCollideW;
	float scaleCollideH;
	//Z del suelo en el que se encuentra
	int floor_;
};

