// This file is part of the course TPV2@UCM - Samir Gena
#include "Cloud.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "EntityAttribs.h"
#include "../game/Game.h"
#include "../ecs/Camera.h"
#include "../utils/Collisions.h"

void Cloud::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Cloud::update() {

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEnemies();

	for (Entity* e : ents) {
		cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
		//Si la entidad es un enemigo...

			//Cogemos el transform del enemigo
		auto eTR = e->getComponent<Transform>();

		//Creamos nuestroRect
		Vector2D newPos = Vector2D(eTR->getPos().getX() - cam.x, eTR->getPos().getY() - cam.y);

		Vector2D otherPos = Vector2D(tr_->getPos().getX() - cam.x, tr_->getPos().getY() - cam.y);

		//Y comprobamos si colisiona
		if (Collisions::collides(otherPos, tr_->getW(), tr_->getH(), newPos, eTR->getW(), eTR->getH())) {
			//Le restamos la vida al enemigo
			e->getComponent<EntityAttribs>()->recieveDmg(dmg_);
			entity_->getMngr()->refreshEnemies();
		}
	}
}

void Cloud::render() {


}

