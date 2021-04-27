#include "EnemyStateMachine.h"
#include "AnimEnemyStateMachine.h"


void EnemyStateMachine::update() {

	//CAMBIOS INTERNOS DE ALGUNAS ANIMACIONES QUE VAN DIRECTAMENTE
	//LIGADOS A ESTADOS INTERNOS DEL HAMSTER
	//Fin Animacion
	if (entity_->getComponent<AnimEnemyStateMachine>() != nullptr)
	{
		if (currentState == EnemyStates::ENM_STUNNED || entity_->getComponent<AnimEnemyStateMachine>()->getState() == EnemyStatesAnim::HITTED)
		{

			if (entity_->getComponent<Animator>()->OnAnimationFrameEnd() )
			{
				entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, false);
			}

		}
	}
	

	//std::cout << currentstate() << std::endl;
}