// This file is part of the course TPV2@UCM - Samir Genaim
#include "Camera.h"
#include "../components/Transform.h"

void Camera::update() {
	if (cameraState == Players)
		followPlayer();
	else if (cameraState == GoingTo)
		Goto();
	else if (cameraState == Static)
		StaticCamera();

	checkBounds();

}

void Camera::checkBounds() {

	if (camera_.x < 0)
		camera_.x = 0;
	else if (camera_.x + camera_.w > 5100 * 3.8f)
		camera_.x = (5100 * 3.8f) - camera_.w;

	if (camera_.y < -205)
		camera_.y = -205;
	else if (camera_.y + camera_.h > 384 * 3.8f)
		camera_.y = (384 * 3.8f) - camera_.h;
}

void Camera::followPlayer() {
	camPos = Vector2D();
	players = 0;
	auto& players_ = entity_->getMngr()->getPlayers();

	//C�mara sigue a los personajes
	for (Entity* e : players_) {
		auto& playerpos = e->getComponent<Transform>()->getPos();
		// Operaci�n para calcular el punto medio con m�s jugadores
		camPos = camPos + playerpos + Vector2D(e->getComponent<Transform>()->getW(), e->getComponent<Transform>()->getH()) / 2;
		players++;
	}
	//Actualizamos la posicion de la camara
	camera_.x = (camPos.getX() / players) - camera_.w / 2;
	camera_.y = (camPos.getY() / players) - camera_.h / 2;
}

void Camera::StaticCamera() {
	Vector2D CamStaticPos = newObjetivo();

	camera_.x = CamStaticPos.getX() - camera_.w / 2;
	camera_.y = CamStaticPos.getY() - camera_.h / 2;
}

void Camera::Goto() {
	Vector2D CamStaticPos = newObjetivo();

	bool check1 = false;
	bool check2 = false;
	int speed = 4;
	if (camera_.x < CamStaticPos.getX() - 12 - camera_.w / 2)
		camera_.x = camera_.x + speed;
	else if (camera_.x > CamStaticPos.getX() + 12 - camera_.w / 2)
		camera_.x = camera_.x - speed;
	else
		check1 = true;

	if (camera_.y < CamStaticPos.getY() - 12 - camera_.h / 2)
		camera_.y = camera_.y + speed;
	else if (camera_.y > CamStaticPos.getY() + 12 - camera_.h / 2)
		camera_.y = camera_.y - speed;
	else
		check2 = true;

	//Cuando se ajusta la camara pasa al estado "Static"
	if (check1 && check2 && GoToTracker)
		cameraState = Static;
	else if (check1 && check2 && !GoToTracker)
		cameraState = Players;
}


//Calcula el punto al que tiene que ir la camara con el punto de direcci�n dado
Vector2D Camera::newObjetivo() {
	Vector2D CamStaticPos;
	camPos = Vector2D();
	players = 0;
	//Calculamos punto medio de los hamsters
	Vector2D playerMidPos;
	auto& players_ = entity_->getMngr()->getPlayers();
	for (Entity* e : players_) {
		auto& playerpos = e->getComponent<Transform>()->getPos();
		// Operaci�n para calcular el punto medio con m�s jugadores
		camPos = camPos + playerpos + Vector2D(e->getComponent<Transform>()->getW(), e->getComponent<Transform>()->getH()) / 2;
		players++;
	}
	//Actualizamos la posicion central de los 4 jugadores
	playerMidPos = Vector2D((camPos.getX() / players), (camPos.getY() / players));

	//Dependiendo del valor de "CameraFollowPos" vamos a devolver el punto medio entre el punto que se pasa y la posici�n de los jugadores, o la posicion de los jugadores
	//Calculamos un punto que se encuentra a 1/2 entre la posicion fija de la camara (objetive) y el punto medio de los 4 jugadores (playerMidPos)
	if (CameraFollowPos.getX() == -1 || CameraFollowPos.getY() == -1)
		CamStaticPos = playerMidPos;
	else
		CamStaticPos = ((playerMidPos / 4 + CameraFollowPos));

	return CamStaticPos;
}

//Cambia el punto al que sigue la camara
void Camera::changeCamFollowPos(Vector2D objetive) {
	//Si el vector que se le pasa no es valido, CameraFollowPos pasa a valer el punto medio entre los hamsters
	if (!GoToTracker) {
		CameraFollowPos = newObjetivo();
	}
	else
		CameraFollowPos = objetive;
}