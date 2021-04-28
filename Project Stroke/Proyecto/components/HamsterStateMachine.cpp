#include "HamsterStateMachine.h"
#include "AnimHamsterStateMachine.h"

void HamsterStateMachine::init() {
	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void HamsterStateMachine::update() {
	if (state_->getState() != GameStates::PAUSE) {
		//CAMBIOS INTERNOS DE ALGUNAS ANIMACIONES QUE VAN DIRECTAMENTE
		//LIGADOS A ESTADOS INTERNOS DEL HAMSTER
		//Fin Animacion
		auto* a = entity_->getComponent<AnimHamsterStateMachine>();
		if (a != nullptr)
		{

			auto& o = entity_->getComponent<AnimHamsterStateMachine>()->getState();
			if (o == HamStatesAnim::HITTED || o== HamStatesAnim::STUNNED)
			{

				if (entity_->getComponent<Animator>()->OnAnimationFrameEnd())
				{
					entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::HITTED, false);
					entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::STUNNED, false);
				}

			}
		}
	}
	//std::cout << currentstate() << std::endl;
}
