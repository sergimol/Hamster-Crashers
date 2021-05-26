#include "ShadowFollow.h"

void ShadowFollow::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	
	auto* mngr = entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>();

	pixelMargin = mngr->getCellSize();

	baseWidth_ = tr_->getW();
	baseHeight_ = tr_->getH();

	
	if (!useCollision_) {
		otherWidth_ = otherTr_->getW();
		otherHeight_ = otherTr_->getH();
	}
	else {
		auto rect = otherTr_->getRectCollideFeet();
		rect.w *= 2;
		rect.h *= 2;

		otherWidth_ = rect.w;
		otherHeight_ = rect.h;

		baseWidth_ = rect.w;
		baseHeight_ = rect.h;
	}
	

	anim_ = false;
}

void ShadowFollow::update() {
	//ESCALA DE LA SOMBRA EN FUNCIÓN DE LA ALTURA
	float new_scale = 1 / ((otherTr_->getZ() - otherTr_->getFloor() + 1) / pixelMargin);

	if (new_scale < 0) new_scale = 0;
	else if (new_scale > 1) new_scale = 1;

	new_scale = sdlutils().lerp(0.5, 1, new_scale);

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

	float otherX, otherY;
	if (!useCollision_) {
		otherX = otherTr_->getPos().getX() + otherWidth_ / 2;
		otherY = otherTr_->getPos().getY() + 4 * otherHeight_ / 5;
	}
	else {
		auto rect = otherTr_->getRectCollideFeet();
		otherX = rect.x + otherWidth_ / 4;
		otherY = rect.y + otherHeight_ / 4;
	}

	float newX, newY;
	newX = otherX - width_ / 2;
	newY = otherY - height_ / 2 - tr_->getFloor() - (tr_->getZ()-tr_->getFloor());

	//ACTUALIZAMOS POSICIÓN, TAMAÑO Y TOMAMOS EL SUELO DEL PLAYER
	tr_->setPos(Vector2D(newX, newY));

	tr_->setH(height_);
	tr_->setW(width_);

	//tr_->getZ() = otherTr_->getFloor();	
}