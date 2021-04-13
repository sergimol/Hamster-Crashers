#include "HamsterStateMachine.h"
#include "AnimHamsterStateMachine.h"


void HamsterStateMachine::update() {

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

	//std::cout << currentstate() << std::endl;
}
