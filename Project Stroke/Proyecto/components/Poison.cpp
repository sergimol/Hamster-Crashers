#include "Poison.h"
#include "Movement.h"
#include "Animator.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
#include "EntityAttribs.h"
#include "Transform.h"

Poison::Poison(int dmg) : Ability(CLOUDCD), dmg_(dmg) {
	
};

Poison::~Poison() {

}
void Poison::init() {
	Ability::init();
	cloud.h = tr_->getH() * 1.5;
	cloud.w = tr_->getW() * 1.5;
}

void Poison::update() {
	Ability::update();
	if (lastActive) {
		auto& ents = entity_->getMngr()->getEnteties();

		for (Entity* e : ents) {
			//Si la entidad es un enemigo...
			if (e->hasGroup<Enemy>()) {
				//Cogemos el transform del enemigo
				auto eTR = e->getComponent<Transform>();

				//Creamos su Rect
				SDL_Rect rectEnemy;
				rectEnemy.h = eTR->getH();
				rectEnemy.w = eTR->getW();
				rectEnemy.x = eTR->getPos().getX();
				rectEnemy.y = eTR->getPos().getY();

				//Y comprobamos si colisiona
				if (SDL_HasIntersection(&cloud, &rectEnemy)) {
					//Le restamos la vida al enemigo
					e->getComponent<EntityAttribs>()->recieveDmg(dmg_);
					//Y ponemos invulnerable al enemigo
				}
			}
		}



	}
}

void Poison::action() {
	//Realizamos las animaciones
	if (tr_->getFlip())
		cloud.x = tr_->getPos().getX() - 200;
	else
		cloud.x = tr_->getPos().getX() + 200;

	cloud.y = tr_->getPos().getY();
}

