#include "Camera.h"
#include "../components/Transform.h"

void Camera::init() {
	map_ = entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>();
	assert(map_ != nullptr);
}

void Camera::update() {
	if (cameraState == Players)
		followPlayer();
	else if (cameraState == GoingTo)
		Goto();
	else if (cameraState == Static)
		StaticCamera();
	else if (cameraState == BossCat)
		followBossCat();

	//if(minH_ == heightMap_)
		checkBounds();
}

void Camera::checkBounds() {

	if (camera_.x < 0) {
		camera_.x = 0;
	}
	else if (camera_.x + camera_.w > map_->getMaxW()) {
		camera_.x = map_->getMaxW() - camera_.w;
	}

	if (camera_.y < upOffset - heightMap_)
		camera_.y = upOffset - heightMap_;
	else if (camera_.y + camera_.h > map_->getMaxH())
		camera_.y = map_->getMaxH() - camera_.h;

	camPos.setX(camera_.x + camera_.w / 2);
	camPos.setY(camera_.y + camera_.h / 2);
}

void Camera::followPlayer() {
	cameraFollowPos_ = Vector2D(-1, -1);
	camPos = newObjetivo();
	players = 0;

	//Actualizamos la posicion de la camara
	camera_.x = camPos.getX() - camera_.w / 2.0;
	camera_.y = camPos.getY() - camera_.h / 2.0;

}

void Camera::followBossCat() {
	auto cat = entity_->getMngr()->getHandler<Cat_>()->getComponent<Transform>();

	//Camara sigue al gato dejándolo justo en la esquina derecha
	camPos = cat->getPos() - Vector2D(sdlutils().width() / 2 - cat->getW(), 0);

	//Actualizamos la posicion de la camara
	camera_.x = camPos.getX() - camera_.w / 2;
	camera_.y = camPos.getY() - camera_.h / 2;
}

void Camera::StaticCamera() {
	Vector2D CamStaticPos = newObjetivo();

	camera_.x = CamStaticPos.getX() - camera_.w / 2;
	camera_.y = CamStaticPos.getY() - camera_.h / 2;
}

void Camera::Goto() {
	Vector2D CamStaticPos = newObjetivo();

	bool check1 = false;

	int speed = 9;

	if (camera_.x < CamStaticPos.getX() - 24 - camera_.w / 2)
		camera_.x = camera_.x + speed;
	else if (camera_.x > CamStaticPos.getX() + 24 - camera_.w / 2)
		camera_.x = camera_.x - speed;
	else
		check1 = true;

	camera_.y = CamStaticPos.getY() - camera_.h / 2;

	//Cuando se ajusta la camara pasa al estado "Static"
	if (check1 && GoToTracker)
		cameraState = Static;

	else if (check1 && !GoToTracker)
		cameraState = Players;
}


//Calcula el punto al que tiene que ir la camara con el punto de direcci�n dado
Vector2D Camera::newObjetivo() {
	Vector2D CamStaticPos;
	camPos = Vector2D();
	players = 0;
	minH_ = -1;

	//Calculamos punto medio de los hamsters
	Vector2D playerMidPos;
	auto& players_ = entity_->getMngr()->getPlayers();
	for (Entity* e : players_) {
		auto* tr = e->getComponent<Transform>();
		auto playerpos = tr->getPos();
		// Operaci�n para calcular el punto medio con m�s jugadores
		camPos = camPos + playerpos + (Vector2D(tr->getW(), tr->getH()) / 2);
		players++;
		if (minH_ == -1 || tr->getFloor() < minH_)
			minH_ = tr->getFloor();
	}
	//Actualizamos la posicion central de los 4 jugadores
	playerMidPos = Vector2D((camPos.getX() / players), (camPos.getY() / players));

	int osci = (playerMidPos.getX() - cameraFollowPos_.getX()) / 4;
	//Dependiendo del valor de "CameraFollowPos" vamos a devolver el punto medio entre el punto que se pasa y la posici�n de los jugadores, o la posicion de los jugadores
	//Calculamos un punto que se encuentra a 1/2 entre la posicion fija de la camara (objetive) y el punto medio de los 4 jugadores (playerMidPos)

	CamStaticPos = playerMidPos;
	if (cameraFollowPos_.getX() != -1 && cameraFollowPos_.getY() != -1)
		CamStaticPos.setX(cameraFollowPos_.getX() + osci);

	float aux = heightMap_;
	if (minH_ != -1 && minH_ != heightMap_) {
		if (heightMap_ - minH_ < 0.1 && heightMap_ - minH_ > -0.1) {
			heightMap_ = minH_;
		}
		else 
			heightMap_ = sdlutils().lerp(minH_, heightMap_, 0.88f);
	}
	if(aux != heightMap_)
		map_->setMaxH(map_->getMaxH() + (aux - heightMap_));
	else
		map_->setMaxH(camera_.h - heightMap_);

	CamStaticPos.setY(CamStaticPos.getY() + upOffset - heightMap_);
	return CamStaticPos;
}

//Cambia el punto al que sigue la camara
void Camera::changeCamFollowPos(int objetive) {
	//Si el vector que se le pasa no es valido, CameraFollowPos pasa a valer el punto medio entre los hamsters
	cameraFollowPos_ = newObjetivo();

	if (GoToTracker)
		cameraFollowPos_.setX(objetive);
}