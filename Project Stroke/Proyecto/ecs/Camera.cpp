// This file is part of the course TPV2@UCM - Samir Genaim
#include "Camera.h"

void Camera::update() {

	Vector2D camPos;
	int players(0);
	auto& players_ = entity_->getMngr()->getPlayers();

	//C�mara sigue a los personajes
	for (Entity* e : players_) {
		auto& playerpos = e->getComponent<Transform>()->getPos();

		// Operaci�n para calcular el punto medio con m�s jugadores
		camPos = camPos + playerpos;
		players++;
	}

	camera_.x = (camPos.getX() / players) - camera_.w / 2;
	camera_.y = (camPos.getY() / players) - camera_.h / 2;

	// Bordes de la c�mara
	/*
	if (camera_.x < 0)
		camera_.x = 0;
	if (camera_.y < 0)
		camera_.y = 0;
	if (camera_.x > camera_.w)
		camera_.x = camera_.w;
	if (camera_.h > camera_.h)
		camera_.y = camera_.h;
	*/

	//std::cout << camera_.x << " " << camera_.y << "\n";
}