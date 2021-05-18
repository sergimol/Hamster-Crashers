#include "LifeTime.h"
#include "Animator.h"
#include "SoundManager.h"
#include "../ecs/Manager.h"
#include "Dying.h"
#include "Item.h"
#include "Image.h"
#include "ContactDamage.h"

void LifeTime::init() {
	
	gamestate = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(gamestate != nullptr);
	
	
	lastTime_ = sdlutils().currRealTime();
}

void LifeTime::update()
{
	if (gamestate->getState() == GameStates::RUNNING) {

		time_ = sdlutils().currRealTime() - lastTime_;

		if (time_ >= lifeTime_) {
			entity_->setActive(false);
		}
	}
	else lastTime_ = sdlutils().currRealTime() - time_;

}


