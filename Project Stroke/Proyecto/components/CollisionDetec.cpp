#include "CollisionDetec.h"
#include "Gravity.h"
#include "../ecs/Camera.h"

#include <cmath>
#include "../ecs/Entity.h"

//Para comprobar las colisiones
#include "MapMngr.h"

void CollisionDetec::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

}

void CollisionDetec::setMovement(MovementSimple* m) {
	mv_ = m;
	speed_ = mv_->getSpeed();
}

void CollisionDetec::tryToMove(Vector2D dir, Vector2D goalVel, SDL_Rect& rectPlayer, bool enemy) {
	//Cojo el rect del player y le sumo la supuesta siguiente posicion
	auto& vel = tr_->getVel();

	//Cogemos el mapa para comprobar luego las colisiones
	auto map = entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>();

	//Si me voy a chocar con una pared...
	SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
	Vector2D pCam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCamPos();

	if (map->intersectWall(rectPlayer) || map->intersectObstacles(rectPlayer)) {

		//Comprobamos si hay doble input
		if (dir.getX() != 0 && dir.getY() != 0 || vel.getX() != 0 && vel.getY() != 0) {

			//Probamos con ignorar el Y
			rectPlayer.y = tr_->getRectCollide().y;

			//Si con el Y bloqueado se mueve correctamente
			if (!map->intersectWall(rectPlayer) && !map->intersectObstacles(rectPlayer)) {
				goalVel.setY(0);
				vel.setY(0);
			}
			else {
				//Probamos ignorando la X
				rectPlayer.y += goalVel.getY();
				rectPlayer.x = tr_->getRectCollide().x;

				if (map->intersectWall(rectPlayer) || map->intersectObstacles(rectPlayer)) {
					goalVel.setX(0);
					vel.setX(0);
				}
				//Para las esquinas. NO QUITAR
				else {
					//Dejo de moverme
					vel.setX(0);
					vel.setY(0);
				}
			}
		}
		else {
			//Dejo de moverme
			vel.setX(0);
			vel.setY(0);
		}
	}

	//Comprobacion para los límites de la cámara
	if (enemy) {
		if (rectPlayer.x + rectPlayer.w < cam.x || rectPlayer.x  > pCam.getX() + cam.w / 2)
			mv_->setSpeed(speed_ * 4);
		else
			mv_->setSpeed(speed_);
		if (rectPlayer.y < cam.y || rectPlayer.y + tr_->getFloor() + rectPlayer.h + 120 > pCam.getY() + cam.h / 2)
			vel.setY(-speed_.getY());
	}
	else {
		if (rectPlayer.x < cam.x) {
			if (entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCamState() == State::GoingTo)
				vel.setX(20);
			else 
				vel.setX(0);			
		}
		else if (rectPlayer.x + rectPlayer.w > pCam.getX() + cam.w / 2) {
			if (entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCamState() == State::GoingTo)
				vel.setX(-20);
			else 
				vel.setX(0);
		}
		if (rectPlayer.y < cam.y || rectPlayer.y + rectPlayer.h - tr_->getFloor() + 60 > pCam.getY() + cam.h / 2)
			vel.setY(-0.5);		
	}

	if (vel.getX() < 0.001 && vel.getX() > -0.001) vel.setX(0);
	if (vel.getY() < 0.001 && vel.getY() > -0.001) vel.setY(0);
}