// This file is part of the course TPV2@UCM - Samir Gena
#include "BulletHit.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "EntityAttribs.h"
#include "../utils/Collisions.h"

BulletHit::BulletHit(float posY) : dmg_(DMG), y(posY) {
}

BulletHit::~BulletHit() {
}

void BulletHit::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void BulletHit::update() {
	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEnemies();

	for (Entity* e : ents) {
		cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
		//Cogemos el transform del enemigo
		auto eTR = e->getComponent<Transform>();


		Vector2D newPos = Vector2D(eTR->getPos().getX() - cam.x, eTR->getPos().getY() - cam.y);

		Vector2D otherPos = Vector2D(tr_->getPos().getX() - cam.x, tr_->getPos().getY() - cam.y);

		//Y comprobamos si colisiona
		if (Collisions::collides(otherPos, tr_->getW(), tr_->getH(), newPos, eTR->getW(), eTR->getH())) {

			//Si estás dentro del margen de la profundidad...
			if (abs((y) - (eTR->getPos().getY() + eTR->getH())) < 40) {

				//Le restamos la vida al enemigo
				e->getComponent<EntityAttribs>()->recieveDmg(dmg_);

				//Desactivamos la bala
				entity_->setActive(false);
				entity_->getMngr()->refreshEnemies();
			}
		}
	}
}


