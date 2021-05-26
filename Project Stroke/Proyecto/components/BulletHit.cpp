#include "BulletHit.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "EntityAttribs.h"
#include "EnemyStateMachine.h"
#include "AnimEnemyStateMachine.h"
#include "EnemyStun.h"
#include "Knockback.h"
#include "EntityAttribs.h"
#include "../utils/Collisions.h"

BulletHit::BulletHit() : dmg_(12), state_(nullptr), tr_(nullptr) {
}

BulletHit::~BulletHit() {
}

void BulletHit::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void BulletHit::update() {
	if (state_->getState() == GameStates::RUNNING) {
		//Cogemos todas las entidades del juego
		auto& ents = entity_->getMngr()->getEnemies();

		for (Entity* e : ents) {

			if (e->isActive()) {
				//Cogemos la camara
				cam_ = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
				//Cogemos el transform del enemigo
				auto eTR = e->getComponent<Transform>();
				auto eRectCollide = eTR->getRectCollide();
				auto rectCollide = tr_->getRectCollide();


				Vector2D newPos = Vector2D(eRectCollide.x - cam_.x, eRectCollide.y - cam_.y);

				Vector2D otherPos = Vector2D(rectCollide.x - cam_.x, rectCollide.y - cam_.y);

				//Y comprobamos si colisiona
				if (Collisions::collides(otherPos, rectCollide.w, rectCollide.h, newPos, eRectCollide.w, eRectCollide.h)) {
					auto eAttribs = e->getComponent<EntityAttribs>();

					//Si estás dentro del margen de la profundidad...
					if ((eAttribs->ignoresMargin() || abs((rectCollide.y) - (eRectCollide.y)) < eAttribs->getMarginToAttack() + 70) && !eAttribs->checkInvulnerability()) {

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

						//Desactivamos la bala
						entity_->setActive(false);
						entity_->getMngr()->refreshEnemies();
					}
				}
			}
		}
	}
}


