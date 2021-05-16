#pragma once

#include "Image.h"

/*
*	Sigue al transform dado en la constructora y cambia de tama�o en funci�n de la relaci�n de Z y el suelo
*	Adem�s tiene una ligera animaci�n de idle
*/


class ShadowFollow : public Component {
public:
	ShadowFollow(Transform* other, bool useCollision) : otherTr_(other), tr_(nullptr), useCollision_(useCollision){};
	virtual ~ShadowFollow() {};
	
	virtual void init() override;
	virtual void update() override;

private:

	float pixelMargin;

	Transform* tr_, *otherTr_;
	
	float baseWidth_, baseHeight_,
		width_, height_,
		otherWidth_, otherHeight_;

	bool useCollision_, anim_;

	const float animOff_ = 0.01f, animTime_ = 230.0f;
	unsigned int timer_ = 0;
};