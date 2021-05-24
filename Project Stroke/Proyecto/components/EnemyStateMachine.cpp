#include "EnemyStateMachine.h"
#include "AnimEnemyStateMachine.h"
#include "EntityAttribs.h"


void EnemyStateMachine::update() {

	//CAMBIOS INTERNOS DE ALGUNAS ANIMACIONES QUE VAN DIRECTAMENTE
	//LIGADOS A ESTADOS INTERNOS DEL HAMSTER
	//Fin Animacion
	if (entity_->getComponent<AnimEnemyStateMachine>() != nullptr)
	{
		if (currentState == EnemyStates::ENM_STUNNED || entity_->getComponent<AnimEnemyStateMachine>()->getState() == EnemyStatesAnim::HITTED 
			|| entity_->getComponent<AnimEnemyStateMachine>()->getState() == EnemyStatesAnim::STUNNED)
		{

			if (entity_->getComponent<Animator>()->OnAnimationFrameEnd() )
			{
				//COMPROBAMOS QUE NO SEA UN BOSS
				if (entity_->getComponent<EntityAttribs>()->getId() != "calcetin")
				{
					entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, false);
					entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::STUNNED, false);
				}
				else
				{
					entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, false);
					//entity_->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::ONFLOOR, true);
				}

			}

		}
	}
	

	//std::cout << currentstate() << std::endl;
}