#pragma once

#include "Image.h"

/*
*	Sigue al transform dado en la constructora y cambia de tamaño en función de la relación de Z y el suelo
*	Además tiene una ligera animación de idle
*/


class ShadowFollow : public Component {
public:
	ShadowFollow(Transform* other) : otherTr_(other), tr_(nullptr) {};
	virtual ~ShadowFollow() {};
	
	virtual void init() override;
	virtual void update() override;

private:
	float lerp(float a, float b, float f);


	Transform* tr_, *otherTr_;
	float baseWidth_, baseHeight_, width_, height_;
	bool anim_;

	const float animOff_ = 0.01f, animTime_ = 230.0f;
	unsigned int timer_ = 0;
};