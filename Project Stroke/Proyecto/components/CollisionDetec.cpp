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

void CollisionDetec::tryToMove(Vector2D dir, Vector2D goalVel, SDL_Rect& rectPlayer) {
	//Cojo el rect del player y le sumo la supuesta siguiente posicion
	auto& vel = tr_->getVel();
	
	//Cogemos el mapa para comprobar luego las colisiones
	auto map = entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>();

	//Si me voy a chocar con una pared...
	SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

	if (map->intersectWall(rectPlayer)) {

		//Comprobamos si hay doble input
		if (dir.getX() != 0 && dir.getY() != 0) {

			//Probamos con ignorar el Y
			rectPlayer.y = tr_->getPos().getY();

			//Si con el Y bloqueado se mueve correctamente
			if (!map->intersectWall(rectPlayer)) {
				goalVel.setY(0);
				vel.setX(lerp(goalVel.getX(), vel.getX(), 0.9));
				vel.setY(0);
			}
			else {
				//Probamos ignorando la X
				rectPlayer.y = tr_->getPos().getY() + goalVel.getY();
				rectPlayer.x = tr_->getPos().getX();

				if (!map->intersectWall(rectPlayer)) {
					goalVel.setX(0);
					vel.setY(lerp(goalVel.getY(), vel.getY(), 0.9));
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

	if (rectPlayer.y + rectPlayer.h > map->getMaxH()) 
		vel.setY(0);	

	//Comprobacion para los límites de la cámara
	if (rectPlayer.x < cam.x || rectPlayer.x + rectPlayer.w > cam.x + cam.w)
		vel.setX(0);
	else if (rectPlayer.y < cam.y || rectPlayer.y + rectPlayer.h > cam.y + cam.h )
		vel.setY(0);
}

float CollisionDetec::lerp(float a, float b, float f)
{
	return (a + f * (b - a));
}