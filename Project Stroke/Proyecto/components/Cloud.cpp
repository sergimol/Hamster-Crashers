#include "Cloud.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "EntityAttribs.h"
#include "AnimEnemyStateMachine.h"
#include "EnemyStun.h"
#include "../ecs/Camera.h"
#include "../utils/Collisions.h"


Cloud::~Cloud() {
	//Devuelve las velocidades originales
	refreshAffectedEnemies();
	for (size_t i = 0; i < affectedEnemies_.size(); ++i)
	{
		affectedEnemies_[i]->getComponent<EntityAttribs>()->resetVel();
	}
};

void Cloud::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void Cloud::update() {
	if (state_->getState() == GameStates::RUNNING) {
		//Cogemos todas las entidades del juego
		auto& ents = entity_->getMngr()->getEnemies();

		for (int i = 0; i < ents.size(); ++i) {
			cam_ = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
			//Si la entidad es un enemigo...

				//Cogemos el transform del enemigo
			auto eTR = ents[i]->getComponent<Transform>();
			auto eRectCol = eTR->getRectCollide();

			//Creamos nuestroRect
			Vector2D newPos = Vector2D(eRectCol.x - cam_.x, eRectCol.y - cam_.y);

			Vector2D otherPos = Vector2D(tr_->getPos().getX() - cam_.x, tr_->getPos().getY() - cam_.y);

			//Y comprobamos si colisiona
			if (Collisions::collides(otherPos, tr_->getW(), tr_->getH(), newPos, eRectCol.w, eRectCol.h)) {

				ents[i]->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, true);

				auto& enmStateM = ents[i]->getComponent<EnemyStateMachine>()->getState();


				//STUN si lo vemos mejor
				//if (enmStateM != EnemyStates::ENM_DEAD) {
				//	//Si tiene stun, se aplica
				//	EnemyStun* enmStun = ents[i]->getComponent<EnemyStun>();
				//	if (enmStun != nullptr && enmStun->isActive()) {

				//		ents[i]->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, true);

				//		//Si no estaba aturdido ya
				//		if (enmStateM != EnemyStates::ENM_STUNNED) {
				//			//Aturdimos al enemigo
				//			enmStateM = EnemyStates::ENM_STUNNED;
				//		}
				//		//Reiniciamos tiempo de stun
				//		enmStun->restartStunTime(false);
				//	}
				//}
				auto eAttribs = ents[i]->getComponent<EntityAttribs>();

				// Reducimos velocidad a los afectados
				int j = 0;

				while (j < affectedEnemies_.size() && ents[i] != affectedEnemies_[j]) { ++j; }

				if (j == affectedEnemies_.size())
					eAttribs->setVel(eAttribs->getVel() / 5);

				//Le restamos la vida al enemigo
				eAttribs->recieveDmg(dmg_);

				affectedEnemies_.push_back(ents[i]);
				
				entity_->getMngr()->refreshEnemies();
				refreshAffectedEnemies();
			}
		}
	}
}

void Cloud::refreshAffectedEnemies() {
	affectedEnemies_.erase( //
		std::remove_if( //
			affectedEnemies_.begin(), //
			affectedEnemies_.end(), //
			[](const Entity* e) { //
				return !e->isActive();
			}), //
		affectedEnemies_.end());
}

void Cloud::render() {


}

