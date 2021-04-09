// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <SDL_rect.h>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class Camera : public Component {
public:
	Camera(SDL_Rect cameraRect) : players(0), camera_(cameraRect), pos_(Vector2D(0, 0)) {
	}

	virtual ~Camera() {
	}

	void update() override;

	/*Vector2D getCamPos() {
		return Vector2D(camera_.x, camera_.y);
	}*/

	/*Vector2D& getPos() {
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

	void setRot(float rot) {
		rotation_ = rot;
	}

	void setPos(Vector2D posNew) {
		pos_ = posNew;
	}
	void setVel(Vector2D velNew) {
		vel_ = velNew;
	}*/






private:
	SDL_Rect camera_;	//Rectangulo de la camara
	Vector2D pos_;		//Posicion de la camara
	int players;		//Jugadores que sigue la camara

	/*Vector2D vel_;
	float width_;
	float height_;
	float rotation_;
	float z_;
	float velZ_;
	bool flip_;*/
};

