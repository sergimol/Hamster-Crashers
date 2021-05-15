#include "WarCry.h"
#include "Animator.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "Knockback.h"

#include "../ecs/Camera.h"
#include "../utils/Collisions.h"

WarCry::WarCry(float attCadenceM, float dmgM) :
	Ability(0), attCadenceMultiplier_(attCadenceM), dmgMultiplier_(dmgM),
	attribs_(nullptr), abTime_(0), fearCD_(1500), anim_(nullptr),
	buffCD_(5000), abilityState_(0) {
};

WarCry::~WarCry() {
}

void WarCry::init() {
	Ability::init();

	anim_ = entity_->getComponent<AnimHamsterStateMachine>();
	assert(anim_ != nullptr);

	attribs_ = entity_->getComponent<EntityAttribs>();
	assert(attribs_ != nullptr);
	lightAtt_ = entity_->getComponent<LightAttack>();
	assert(lightAtt_ != nullptr);
	strongAtt_ = entity_->getComponent<StrongAttack>();
	assert(strongAtt_ != nullptr);

	originalDmg_ = attribs_->getDmg();
	originalLightCadence_ = lightAtt_->getCadence();
	originalStrongCadence_ = strongAtt_->getCadence();
}

void WarCry::action() {
	//Ahora empiezas la animacion

	//Mete los buffs
	attribs_->setDmg(attribs_->getDmg() * dmgMultiplier_);
	lightAtt_->setCadence(lightAtt_->getCadence() * attCadenceMultiplier_);
	strongAtt_->setCadence(strongAtt_->getCadence() * attCadenceMultiplier_);
	abTime_ = sdlutils().currRealTime();
	slowEnemies(true);
}

void WarCry::endAbility() {

}

void WarCry::update() {
	if (state_->getState() == GameStates::RUNNING) {
		Ability::update();
		if (abilityState_ == fearStarted && sdlutils().currRealTime() > abTime_ + fearCD_) {
			//Termina el fear
			slowEnemies(false);
		}
		if (abilityState_ == fearFinished && sdlutils().currRealTime() > abTime_ + buffCD_) {
			//Termina la habilidad
			attribs_->setDmg(originalDmg_);
			lightAtt_->setCadence(originalLightCadence_);
			strongAtt_->setCadence(originalStrongCadence_);
			abilityState_ = notStarted;
		}

		//Fin animacion
		if (anim_->getState() == HamStatesAnim::ABILITY)
		{
			if (entity_->getComponent<Animator>()->OnAnimationFrameEnd())
			{
				anim_->setAnimBool(HamStatesAnim::ABILITY, false);
			}
		}
	}
}


void WarCry::slowEnemies(bool notEndAb) {

	notEndAb ? abilityState_ = fearStarted : abilityState_ = fearFinished;

	auto& ents = entity_->getMngr()->getEnemies();

	//Cogemos la camara
	SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

	for (Entity* e : ents) {

		//Si la entidad es un enemigo...
		//if (e->hasGroup<Enemy>()) {

			//Cogemos el transform del enemigo
		auto eTR = e->getComponent<Transform>();

		Vector2D newPos = Vector2D(eTR->getPos().getX(), eTR->getPos().getY());

		//Y comprobamos si colisiona
		if (Collisions::collides(newPos, eTR->getW(), eTR->getH(), Vector2D(cam.x, cam.y), cam.w, cam.h)) {

			EntityAttribs* eAttribs = e->getComponent<EntityAttribs>();
			Knockback* eKnockback = e->getComponent<Knockback>();

			//Ralentiza o resetea vel
			if (notEndAb) {
				eAttribs->setVel(eAttribs->getVel() / 5);
				if (eKnockback != nullptr)
					eKnockback->knockback(15);
			}
			else
				eAttribs->resetVel();
		}
		//}
	}
}

