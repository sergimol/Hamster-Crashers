// This file is part of the course TPV2@UCM - Samir Genaim
#include "Camera.h"

void Camera::update() {
	if (cameraState == Players)
		followPlayer();
	else if (cameraState == GoingTo)
		Goto(CameraFollowPos);
	else if (cameraState == Static)
		StaticCamera();
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

void Camera::StaticCamera() {
	camPos = Vector2D();
	players = 0;
	//Calculamos punto medio de los hamsters
	Vector2D playerMidPos;
	auto& players_ = entity_->getMngr()->getPlayers();
	for (Entity* e : players_) {
		auto& playerpos = e->getComponent<Transform>()->getPos();
		// Operación para calcular el punto medio con más jugadores
		camPos = camPos + playerpos;
		players++;
	}
	//Actualizamos la posicion central de los 4 jugadores
	playerMidPos = Vector2D((camPos.getX() / players), (camPos.getY() / players));

	//Calculamos un punto que se encuentra a 1/4 entre la posicion fija de la camara (objetive) y el punto medio de los 4 jugadores (playerMidPos)
	Vector2D CamStaticPos = ((playerMidPos + CameraFollowPos * entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>()->getScale()) / 2);

	camera_.x = CamStaticPos.getX() - camera_.w / 2;
	camera_.y = CamStaticPos.getY() - camera_.h / 2;
}

void Camera::Goto(Vector2D objetive) {

	if (camera_.x < objetive.getX() - 5)
		camera_.x++;
	else if (camera_.x > objetive.getX() + 5)
		camera_.x--;
	//else
		//booleano true

	if (camera_.y < objetive.getY() - 5)
		camera_.y++;
	else if (camera_.y > objetive.getY() + 5)
		camera_.y--;
	//else
		//booleano true
		//Si se cumplen los dos booleanos es que ha llegado + o - al punto que tenia que llegar -> pasa al estado "Static"
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