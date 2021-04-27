#include "ShadowFollow.h"

void ShadowFollow::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	
	baseWidth_ = tr_->getW();
	baseHeight_ = tr_->getH();

	anim_ = false;
}

void ShadowFollow::update() {
	//ESCALA DE LA SOMBRA EN FUNCIÓN DE LA ALTURA
	float new_scale = (otherTr_->getFloor() + 1) / (otherTr_->getZ() + 1);

	if (new_scale < 0) new_scale = 0;
	else if (new_scale > 1) new_scale = 1;

	new_scale = lerp(0.5, 1, new_scale);

	//SENSACIÓN DE MOVIMIENTO
	if (anim_) new_scale += animOff_;
	else new_scale -= animOff_;

	if (sdlutils().currRealTime() > timer_ + animTime_) {
		anim_ = !anim_;
		timer_ = sdlutils().currRealTime();
	}
	//CALCULAMOS NUEVA POSICIÓN Y NUEVO TAMAÑO PARA DEJAR CENTRADA ABAJO LA SOMBRA
	height_ = baseHeight_ * new_scale;
	width_ = baseWidth_ * new_scale;

	float otherX = otherTr_->getPos().getX() + otherTr_->getW() / 2;
	float otherY = otherTr_->getPos().getY() + 4*otherTr_->getH() / 5;

	float newX = otherX - width_ / 2;
	float newY = otherY - height_ / 2;

	//ACTUALIZAMOS POSICIÓN, TAMAÑO Y TOMAMOS EL SUELO DEL PLAYER
	tr_->getPos().set(newX, newY);

	tr_->setH(height_);
	tr_->setW(width_);

	tr_->getZ() = -otherTr_->getFloor();	
}

float ShadowFollow::lerp(float a, float b, float f) {
	return (a + f * (b - a));
}