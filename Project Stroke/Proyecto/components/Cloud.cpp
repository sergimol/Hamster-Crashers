// This file is part of the course TPV2@UCM - Samir Gena
#include "Cloud.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "EntityAttribs.h"
#include "../game/Game.h"

void Cloud::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Cloud::update() {

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEntities();

	for (Entity* e : ents) {
		//Si la entidad es un enemigo...
		if (e->hasGroup<Enemy>()) {
			//Cogemos el transform del enemigo
			auto eTR = e->getComponent<Transform>();
			//Creamos nuestroRect
			SDL_Rect rectPlayer;
			rectPlayer.h = tr_->getH();
			rectPlayer.w = tr_->getW();
			rectPlayer.x = tr_->getPos().getX() - Game::camera_->getComponent<Transform>()->getPos().getX();
			rectPlayer.y = tr_->getPos().getY() - Game::camera_->getComponent<Transform>()->getPos().getY();

			//Creamos su Rect
			SDL_Rect rectEnemy;
			rectEnemy.h = eTR->getH();
			rectEnemy.w = eTR->getW();
			rectEnemy.x = eTR->getPos().getX() - Game::camera_->getComponent<Transform>()->getPos().getX();
			rectEnemy.y = eTR->getPos().getY() - Game::camera_->getComponent<Transform>()->getPos().getY();

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

