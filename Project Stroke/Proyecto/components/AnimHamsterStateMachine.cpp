#include "AnimHamsterStateMachine.h"

void AnimHamsterStateMachine::init()
{
	anim = entity_->getComponent<Animator>();
	assert(anim != nullptr);
	ent = entity_->getComponent<EntityAttribs>();
	assert(ent != nullptr);
}

void AnimHamsterStateMachine::update()
{
	handleAnimState();
}

//Cambia las animaciones dependiendo del estado del hamster
void AnimHamsterStateMachine::handleAnimState()
{
	std::string id = ent->getId();
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