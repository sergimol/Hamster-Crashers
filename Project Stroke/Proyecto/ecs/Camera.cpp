// This file is part of the course TPV2@UCM - Samir Genaim
#include "Camera.h"

void Camera::update() {
	if (cameraState == Players)
		followPlayer();
	else if (cameraState == GoingTo)
		Goto(CameraFollowPos);
	else if (cameraState == Static)
		std::cout << "guguinga\n";
}

void Camera::followPlayer() {
	camPos = Vector2D();
	players = 0;
	auto& players_ = entity_->getMngr()->getPlayers();

	//Cámara sigue a los personajes
	for (Entity* e : players_) {
		auto& playerpos = e->getComponent<Transform>()->getPos();

		// Operación para calcular el punto medio con más jugadores
		camPos = camPos + playerpos;
		players++;
	}
	//Actualizamos la posicion de la camara
	camera_.x = (camPos.getX() / players) - camera_.w / 2;
	camera_.y = (camPos.getY() / players) - camera_.h / 2;
}

void Camera::Goto(Vector2D objetive) {
	if (camera_.x < objetive.getX() - 5)
		camera_.x++;
	else if (camera_.x > objetive.getX() + 5)
		camera_.x--;

	if (camera_.y < objetive.getY() - 5)
		camera_.y++;
	else if (camera_.y > objetive.getY() + 5)
		camera_.y--;
}

// Bordes de la cámara
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