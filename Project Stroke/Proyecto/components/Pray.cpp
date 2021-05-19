#include "Pray.h"
#include "Animator.h"
#include "ControlHandler.h"
#include "AnimHamsterStateMachine.h"
#include "AnimEnemyStateMachine.h"
#include "EnemyStateMachine.h"
#include "EnemyStun.h"
#include "Knockback.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "../ecs/Camera.h"
#include "../utils/Collisions.h"
#include "EntityAttribs.h"

Pray::Pray(int dmg, int heal) : Ability(2000), dmg_(dmg), heal_(heal), evil_(true) {
};

Pray::~Pray() {
}

void Pray::action() {
	//Ahora empiezas la animacion
	entity_->getComponent<ControlHandler>()->setActive(false);
	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("canelonSpecial");
}

void Pray::endAbility() {
	prayAbility();
	entity_->getComponent<ControlHandler>()->setActive(true);
}

void Pray::prayAbility() {
	auto& ents = entity_->getMngr()->getEnemies();

	//Cogemos la camara
	SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

	bool hasHit = false;
	for (Entity* e : ents) {

		if (evil_) {

			//Si la entidad es un enemigo...
			if (e->hasGroup<Enemy>() && e->isActive()) {

				//Cogemos el transform del enemigo
				auto eTR = e->getComponent<Transform>();

				Vector2D newPos = Vector2D(eTR->getPos().getX(), eTR->getPos().getY());

				//Y comprobamos si colisiona
				if (Collisions::collides(newPos, eTR->getW(), eTR->getH(), Vector2D(cam.x, cam.y), cam.w, cam.h)) {
					// Sonido de golpe una sola vez
					if (!hasHit)
						entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("lighthit");
					hasHit = true;

					auto& enmStateM = e->getComponent<EnemyStateMachine>()->getState();


					//Aturdir
					if (enmStateM != EnemyStates::ENM_DEAD) {
						//Si tiene stun, se aplica
						EnemyStun* enmStun = e->getComponent<EnemyStun>();
						if (enmStun != nullptr && enmStun->isActive()) {

							e->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, true);

							//Si no estaba aturdido ya
							if (enmStateM != EnemyStates::ENM_STUNNED) {
								//Aturdimos al enemigo
								enmStateM = EnemyStates::ENM_STUNNED;
							}
							//Reiniciamos tiempo de stun
							enmStun->restartStunTime(false);
						}
						//Si tiene Knockback, se aplica
						Knockback* enmKnockback = e->getComponent<Knockback>();
						if (enmKnockback != nullptr) {
							//Damos la vuelta si es atacado por detras
							auto& enmFlip = eTR->getFlip();
							if (enmFlip == tr_->getFlip())
								enmFlip = !enmFlip;

							enmKnockback->knockback();
						}
					}

					//Le restamos la vida al enemigo
					e->getComponent<EntityAttribs>()->recieveDmg(dmg_);
					entity_->getMngr()->refreshEnemies();
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
	entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::ABILITY, false);
	evil_ = !evil_;

	if (evil_) {
		entity_->getComponent<EntityAttribs>()->setId("canelon");
		entity_->getComponent<Animator>()->setTexture(&sdlutils().images().at("canelonSheet"));
	}
	else {
		entity_->getComponent<EntityAttribs>()->setId("canelonDemon");
		entity_->getComponent<Animator>()->setTexture(&sdlutils().images().at("canelonDemonSheet"));
	}
}

