#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>
#include <cmath>
#include "../utils/checkML.h"

#include "../components/Transform.h"
#include "../components/HamsterStateMachine.h"
#include "../components/Animator.h"
//#include "../components/EnemyBehaviour.h"

#include "EnemyBehaviour.h"

//Esta clase es meramente virtual sirve como estrutura para hacer los comportamientos de los enemigos a cada cual ams complejo no se va a ser la repera
class Behavior {
public:
	virtual void behave() = 0;//Es el update de behavior
	virtual void init() {
	}
	virtual ~Behavior(){}
	virtual void setOwner(EnemyBehaviour* ow);
	virtual void setObjetive();

protected:
	EnemyBehaviour* owner_; //le pediremos acceso a todas las componentes que vaya a necesitar cada Behavior para no sobrecargar
							//aqui es mi pregunta de si es necesaria inclusion circular o no, con un par de chapuzas sera no circular
	
	int hamsId_ = 0; //creo que lo voy a quitar
	MovementSimple* mov_; //Igual esto es major al reves, que el movement coja los datos del follow y se mueva en la dir que le indique

	Transform* tr_;
	Transform* hamsterTr_;

	Entity* lockedHamster_;

	HamsterStateMachine* lockedHamState_;
};

