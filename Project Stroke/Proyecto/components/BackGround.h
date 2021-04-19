#pragma once
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "Image.h"

class BackGround : public Image
{
private:
	float pxVel_;
	Vector2D camPos_;
public:
	BackGround(Texture* im, float vel) : Image(im) { pxVel_ = vel; };
	virtual ~BackGround() {};
	virtual void update();
};