#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim
#include <SDL.h>
#include <cassert>
#include <vector>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"

#include "Transform.h"
#include "HamsterStateMachine.h"
#include "Animator.h"
#include "Image.h"
#include "EntityAttribs.h"
#include "MovementSimple.h"
#include "FinalBossAttack.h"
#include "FinalBossPunch.h"

class MicroOndasManager : public Component {
public:
	MicroOndasManager(int hamN);

	virtual ~MicroOndasManager() {};

	void init() override;

	void update() override;
protected:
private:
	
	//hamster al que va a perseguir* en verdad solo queremos la propiedad tranform ahora mismo pero
	// mas adelante es posible que nos interese conocer estados o componentes oportunos, por ahora no ahce daño verdad¿?¿
	std::vector<Entity*> hamsters_;
	//std::vector<> 
	//MovementSimple* mov_; //Igual esto es major al reves, que el movement coja los datos del follow y se mueva en la dir que le indique

	bool handTurn_;
	Transform* tr_;
	Transform* leftTr_;
	Transform* rightTr_;
	Transform* bateriaTr_;

	Entity* left_;		//Referencias a las elementos
	Entity* right_;
	Entity* bateria_;

	EntityAttribs* rightAttribs_;
	EntityAttribs* leftAttribs_;
	EntityAttribs* bateriaAttribs_;
	EntityAttribs* thisEnttityAttribs_;

	
	int hamsNum_;

	float timeToEnd_; //el tiempo que vana  estar ene l microondas

};

