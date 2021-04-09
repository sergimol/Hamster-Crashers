#include "AnimHamsterStateMachine.h"
#include "EntityAttribs.h"
#include "Animator.h"

void AnimHamsterStateMachine::init()
{
	anim = entity_->getComponent<Animator>();
	assert(anim != nullptr);
	ent = entity_->getComponent<EntityAttribs>();
	assert(ent != nullptr);
	id = ent->getId();
}

void AnimHamsterStateMachine::update()
{
	HandleAnimState();
	CheckAnimState();
}


//Maneja las transiciones entre los estados
void AnimHamsterStateMachine::HandleAnimState()
{
	//idle
	if (idle && !attack && !move)
		currentState = HamStatesAnim::IDLE;
	//move
	else if (move && !attack && !idle)
		currentState = HamStatesAnim::MOVE;
	//attack
	else if (attack)
		currentState = HamStatesAnim::LIGHTATTACK1;
}

//Cambia las animaciones dependiendo del estado del hamster
void AnimHamsterStateMachine::CheckAnimState()
{

	//Si es diferente al anterior hay que cambiar la animacion
	if (lastState != currentState)
	{
		//Depende del estado playeamos una animacion u otra
		switch (currentState)
		{
		case HamStatesAnim::IDLE:
			anim->play(sdlutils().anims().at(id + "_idle"));
			break;
		case HamStatesAnim::MOVE:
			anim->play(sdlutils().anims().at(id + "_move"));
			break;
		case HamStatesAnim::ABILITY:
			anim->play(sdlutils().anims().at(id + "_ability"));
			break;
		case HamStatesAnim::JUMPUP:
			anim->play(sdlutils().anims().at(id + "_idle")); //CAMBIAR
			break;
		case HamStatesAnim::JUMPDOWN:
			anim->play(sdlutils().anims().at(id + "_idle")); //CAMBIAR
			break;
		case HamStatesAnim::LIGHTATTACK1:
			anim->play(sdlutils().anims().at(id + "_light_attack1"));
			break;
		case HamStatesAnim::LIGHTATTACK2:
			anim->play(sdlutils().anims().at(id + "_light_attack2"));
			break;
		case HamStatesAnim::LIGHTCOMBO:
			anim->play(sdlutils().anims().at(id + "_light_combo"));
			break;
		case HamStatesAnim::STRONGATTACK:
			anim->play(sdlutils().anims().at(id + "_strong_attack"));
			break;
		case HamStatesAnim::STRONGCOMBO:
			anim->play(sdlutils().anims().at(id + "_strong_combo"));
			break;
		case HamStatesAnim::HITTED:
			anim->play(sdlutils().anims().at(id + "_hit"));
			break;
		case HamStatesAnim::STUNNED:
			anim->play(sdlutils().anims().at(id + "_stun"));
			break;
		case HamStatesAnim::DEAD:
			anim->play(sdlutils().anims().at(id + "_death"));
			break;
		case HamStatesAnim::STROKE:
			anim->play(sdlutils().anims().at(id + "_ghost_spawn"));
			break;
		}
	}

	//Recogemos
	lastState = currentState;

}

//PONE A TRUE O FALSE LOS BOOLEANOS DE ANIMACION
void AnimHamsterStateMachine::setAnimBool(HamStatesAnim h, bool b) 
{

	switch (h)
	{
	case HamStatesAnim::IDLE:
		idle = b;
		break;
	case HamStatesAnim::MOVE:
		move = b;
		break;
	case HamStatesAnim::ABILITY:
		idle = b;
		break;
	case HamStatesAnim::JUMPUP:
		idle = b;
		break;
	case HamStatesAnim::JUMPDOWN:
		idle = b;
		break;
	case HamStatesAnim::LIGHTATTACK1:
		attack = b;
		break;
	case HamStatesAnim::LIGHTATTACK2:
		idle = b;
		break;
	case HamStatesAnim::LIGHTCOMBO:
		idle = b;
		break;
	case HamStatesAnim::STRONGATTACK:
		idle = b;
		break;
	case HamStatesAnim::STRONGCOMBO:
		idle = b;
		break;
	case HamStatesAnim::HITTED:
		idle = b;
		break;
	case HamStatesAnim::STUNNED:
		idle = b;
		break;
	case HamStatesAnim::DEAD:
		idle = b;
		break;
	case HamStatesAnim::STROKE:
		idle = b;
		break;
	}
}