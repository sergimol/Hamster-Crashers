// This file is part of the course TPV2@UCM - Samir Gena
#include "Cloud.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "EntityAttribs.h"
#include "../game/Game.h"
#include "../ecs/Camera.h"

void Cloud::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Cloud::update() {
	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEntities();

	for (Entity* e : ents) {
		cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
		//Si la entidad es un enemigo...
		if (e->hasGroup<Enemy>()) {
			//Cogemos el transform del enemigo
			auto eTR = e->getComponent<Transform>();

			//Creamos nuestroRect
			SDL_Rect rectPlayer;
			rectPlayer.h = tr_->getH();
			rectPlayer.w = tr_->getW();
			rectPlayer.x = tr_->getPos().getX() - cam.x;
			rectPlayer.y = tr_->getPos().getY() - cam.y;

			//Creamos su Rect
			SDL_Rect rectEnemy;
			rectEnemy.h = eTR->getH();
			rectEnemy.w = eTR->getW();
			rectEnemy.x = eTR->getPos().getX() - cam.x;
			rectEnemy.y = eTR->getPos().getY() - cam.y;

			//Y comprobamos si colisiona
			if (SDL_HasIntersection(&rectPlayer, &rectEnemy)) {
				//Le restamos la vida al enemigo
				e->getComponent<EntityAttribs>()->recieveDmg(dmg_);
			}
		}
	}
}

void Cloud::render() {


}

