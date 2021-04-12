#include "Pray.h"
#include "Movement.h"
#include "Animator.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
#include "EntityAttribs.h"
#include "Transform.h"
#include "../ecs/Camera.h"

Pray::Pray(int dmg, int heal) : Ability(WAIT), dmg_(dmg), heal_(heal), evil(true){
};

Pray::~Pray() {

}

void Pray::action() {
	//Ahora empiezas la animacion
}

void Pray::endAbility() {
	prayAbility();
}

void Pray::prayAbility() {
	auto& ents = entity_->getMngr()->getEntities();
	SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
	for (Entity* e : ents) {
		if (evil) {
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
				if (SDL_HasIntersection(&cam, &rectEnemy)) {
					//Le restamos la vida al enemigo
					e->getComponent<EntityAttribs>()->recieveDmg(dmg_);
					//entity_->getComponent<Life>()->recieveDmg(dmg_);
				}
			}
		}
		else {
			//Si la entidad es un enemigo...
			if (e->hasGroup<Ally>()) {
				//Cogemos el transform del enemigo
				auto eTR = e->getComponent<Transform>();

				//Creamos su Rect
				SDL_Rect rectEnemy;
				rectEnemy.h = eTR->getH();
				rectEnemy.w = eTR->getW();
				rectEnemy.x = eTR->getPos().getX();
				rectEnemy.y = eTR->getPos().getY();

				//Y comprobamos si colisiona
				if (SDL_HasIntersection(&cam, &rectEnemy)) {
					//Le restamos la vida al enemigo
					auto& state = st_->getState();
					if (state != HamStates::DEAD && e->getComponent<EntityAttribs>()->getLife() > 0) //deberia que valer con el DEAD que cuando muera desactive cosas
						e->getComponent<EntityAttribs>()->heal(heal_);
				}
			}
		}
	}
	evil = !evil;
}

