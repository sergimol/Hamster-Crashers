#include "EnemyStun.h"
#include "EnemyBehaviour.h"

EnemyStun::EnemyStun() :
	enmState_(nullptr), cooldown_(1500), time_(sdlutils().currRealTime()), simpMov_(nullptr), movCancelled_(false), state_(nullptr) {}

void EnemyStun::init() {
	 
	enmState_ = entity_->getComponent<EnemyStateMachine>();
	assert(enmState_ != nullptr);

	//enBehave_ = entity_->getComponent<EnemyBehaviour>();
	//assert(enBehave_ != nullptr);
	
	simpMov_ = entity_->getComponent<MovementSimple>();
	assert(simpMov_ != nullptr);
	
	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void EnemyStun::update() {
	if (state_->getState() == GameStates::RUNNING) {
		auto& state = enmState_->getState();
		if (state == EnemyStates::ENM_STUNNED) {
			if (!movCancelled_) {

				simpMov_->updateKeymap(MovementSimple::RIGHT, false);
				simpMov_->updateKeymap(MovementSimple::LEFT, false);
				simpMov_->updateKeymap(MovementSimple::DOWN, false);
				simpMov_->updateKeymap(MovementSimple::UP, false);

				movCancelled_ = true;
			}
			//Deja de estar stunneado
			if (sdlutils().currRealTime() > time_ + cooldown_) {
				//flwPlayer_->setActive(true);
				state = EnemyStates::ENM_IDLE;
				movCancelled_ = false;
			}
		}
	}
}

//TODO distinguir entre varios tipos de stun, que pongan ams o menos tiempo de stun y meuvan a los enemigos de lsitas
void EnemyStun::restartStunTime(bool finCombo) {
	time_ = sdlutils().currRealTime(); 
	if (finCombo)
	entity_->getComponent<EnemyBehaviour>()->changeToAmbush();
}

void EnemyStun::onResume() {
	time_ += sdlutils().currRealTime() - time_;
}