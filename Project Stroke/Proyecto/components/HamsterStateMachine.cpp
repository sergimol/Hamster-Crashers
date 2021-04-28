#include "HamsterStateMachine.h"
#include "AnimHamsterStateMachine.h"

void HamsterStateMachine::init() {
	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void HamsterStateMachine::update() {
	if (state_->getState() == GameStates::RUNNING) {
		//CAMBIOS INTERNOS DE ALGUNAS ANIMACIONES QUE VAN DIRECTAMENTE
		//LIGADOS A ESTADOS INTERNOS DEL HAMSTER
		//Fin Animacion
		if (currentState == HamStates::STUNNED || entity_->getComponent<AnimHamsterStateMachine>()->getState() == HamStatesAnim::HITTED)
		{
			if (entity_->getComponent<Animator>()->OnAnimationFrameEnd())
			{
				entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::HITTED, false);
			}
			else {
				entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::HITTED, true);
			}
		}
	}
	//std::cout << currentstate() << std::endl;
}
