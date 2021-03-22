// This file is part of the course TPV2@UCM - Samir Gena
#include "BulletHit.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "EntityAttribs.h"

BulletHit::BulletHit() : dmg_(DMG) {
}

BulletHit::~BulletHit() {
}

void BulletHit::update() {

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEnteties();

	for (Entity* e : ents) {
		//Si la entidad es un enemigo...
		if (e->hasGroup<Enemy>()) {
			//Cogemos el transform del enemigo
			auto eTR = e->getComponent<Transform>();
			auto myTR = entity_->getComponent<Transform>();

			//Creamos nuestroRect
			SDL_Rect rectPlayer;
			rectPlayer.h = myTR->getH();
			rectPlayer.w = myTR->getW();
			rectPlayer.x = myTR->getPos().getX();
			rectPlayer.y = myTR->getPos().getY();

			//Creamos su Rect
			SDL_Rect rectEnemy;
			rectEnemy.h = eTR->getH();
			rectEnemy.w = eTR->getW();
			rectEnemy.x = eTR->getPos().getX();
			rectEnemy.y = eTR->getPos().getY();

			//Y comprobamos si colisiona
			if (SDL_HasIntersection(&rectPlayer, &rectEnemy)) {
				//Le restamos la vida al enemigo
				e->getComponent<EntityAttribs>()->recieveDmg(dmg_);

				//Desactivamos la bala(aunque hay que destruirla)
				entity_->setActive(false);
			}
		}
	}
}


