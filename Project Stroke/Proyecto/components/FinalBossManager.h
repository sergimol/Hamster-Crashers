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
#include "AnimEnemyStateMachine.h" 
#include "Animator.h"
#include "Image.h"
#include "EntityAttribs.h"
#include "MovementSimple.h"
#include "FinalBossAttack.h"
#include "FinalBossPunch.h"

class FinalBossManager : public Component {
public:
	FinalBossManager(int hamN, float scale);

	virtual ~FinalBossManager() {};

	void init() override;

	void update() override;

	void lockHamster();
	bool isWithinAttackRange(Transform* tr, bool fist);

protected:
private:

	void movement(Transform* tr, Transform* hamsterTr, MovementSimple* mov);
	
	//hamster al que va a perseguir* en verdad solo queremos la propiedad tranform ahora mismo pero
	// mas adelante es posible que nos interese conocer estados o componentes oportunos, por ahora no ahce daño verdad¿?¿
	std::vector<Entity*> hamsters_;
	//std::vector<> 
	//MovementSimple* mov_; //Igual esto es major al reves, que el movement coja los datos del follow y se mueva en la dir que le indique

	bool handTurn_;
	Transform* tr_;
	Transform* handTr_;
	Transform* fistTr_;

	Entity* hand_;		//Referencias a las manos
	Entity* fist_;

	EntityAttribs* handAttribs_;
	EntityAttribs* fistAttribs_;

	Transform* hamsterTr_;		//Referencias a los hamsters fijados
	Transform* hamsterTrPunch_;
	
	Entity* lockedHamster_;
	Entity* lockedHamsterPunch_;
	
	HamsterStateMachine* lockedHamState_;
	HamsterStateMachine* lockedHamStatePunch_;

	MovementSimple* movHand_;
	MovementSimple* movPunch_;
	
	int hamsNum_;
	float scale_;

	int rangeOffsetX_; // Esta movida habra que balancearla
	int rangeOffsetY_; // Esta movida habra que balancearla
	bool attackAvailable_;

	FinalBossAttack* bossAtk_; //componente de ataque
	FinalBossPunch* bossPunch_;

	float waitingTime_; //Tiempo antes de que decida atacar
	float waitingCD_;

	float stunTime_; //Tiempo parado antes de recuperar el comportamiento
	float stunCD_;

	bool startBehavior_;

	AnimEnemyStateMachine* handAnim_; //
	AnimEnemyStateMachine* fistAnim_; //
};

