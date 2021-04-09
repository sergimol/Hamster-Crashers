#include "Camera.h"


void Camera::update() {
	players = 0;	//Jugadores a los que sigue la camara (se actualiza todo el rato por si se muere uno)

	auto& players_ = entity_->getMngr()->getPlayers();
	//C�mara sigue a los personajes
	for (Entity* e : players_) {
		auto& playerpos = e->getComponent<Transform>()->getPos();

		// Operaci�n para calcular el punto medio con m�s jugadores
		pos_ = pos_ + playerpos;
		players++;
	}

	camera_.x = (pos_.getX() / players) - camera_.w / 2;
	camera_.y = (pos_.getY() / players) - camera_.h / 2;
}