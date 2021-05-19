#include "Pray.h"
#include "Animator.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "../ecs/Camera.h"
#include "../utils/Collisions.h"
#include "EntityAttribs.h"

Pray::Pray(int dmg, int heal) : Ability(2000), dmg_(dmg), heal_(heal), evil_(true){
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
	auto& ents = entity_->getMngr()->getEnemies();

	//Cogemos la camara
	SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

	for (Entity* e : ents) {

		if (evil_) {

			//Si la entidad es un enemigo...
			if (e->hasGroup<Enemy>()) {

				//Cogemos el transform del enemigo
				auto eTR = e->getComponent<Transform>();

				Vector2D newPos = Vector2D(eTR->getPos().getX(), eTR->getPos().getY());

				//Y comprobamos si colisiona
				if (Collisions::collides(newPos, eTR->getW(), eTR->getH(), Vector2D(cam.x, cam.y), cam.w, cam.h)) {

					//Le restamos la vida al enemigo
					e->getComponent<EntityAttribs>()->recieveDmg(dmg_);
				}
			}
		}
		else {

			//Si la entidad es un enemigo...
			if (e->hasGroup<Ally>()) {

				//Cogemos el transform del enemigo
				auto eTR = e->getComponent<Transform>();

				Vector2D newPos = Vector2D(eTR->getPos().getX() - cam.x, eTR->getPos().getY() - cam.y);

				//Y comprobamos si colisiona
				if (Collisions::collides(newPos, eTR->getW(), eTR->getH(), Vector2D(cam.x, cam.y), cam.w, cam.h)) {

					//Le restamos la vida al enemigo
					auto& state = st_->getState();
					if (state != HamStates::DEAD && e->getComponent<EntityAttribs>()->getLife() > 0) //deberia que valer con el DEAD que cuando muera desactive cosas
						e->getComponent<EntityAttribs>()->heal(heal_);
				}
			}
		}
	}
	evil_ = !evil_;
}

