#include "EntityAttribs.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "Animator.h"

EntityAttribs::EntityAttribs() :
	health_(100),
	maxHealth_(100),
	velocity_(Vector2D(7, 3.5)),
	strokeResist_(0.0),
	attackRange_(0.0),
	cadence_(0.0),
	damage_(20),

	critProbability_(0.05),
	maxCrit_(0.2),
	critDamage_(1.0),

	poisonDamage_(2),
	poisonProbability_(0.0),
	canPoison_(poisonProbability_ > 0),
	poisoned_(false),
	poisonTime_(sdlutils().currRealTime()),
	poisonCD_(7000),
	timeLastUpdate_(sdlutils().currRealTime()),
	updateCD_(1500),

	invincible_(false),
	invincibilityTime_(sdlutils().currRealTime()),
	abilityInvul_(false),

	hms_(nullptr),
	hmsText_(nullptr),
	enmState_(nullptr),
	tr_(nullptr)
{}

EntityAttribs::EntityAttribs(int life, float range, std::string id, Vector2D speed, int number, float poisonProb) :
	playerNumber_(number),
	id_(id),
	health_(life),
	maxHealth_(life),
	velocity_(speed),
	strokeResist_(0.0),
	attackRange_(range),
	cadence_(0.0),
	damage_(20),

	critProbability_(0.05),
	maxCrit_(0.2),
	critDamage_(1.5),
	
	poisonDamage_(2),
	poisonProbability_(poisonProb),
	canPoison_(poisonProbability_ > 0),
	poisoned_(false),
	poisonTime_(sdlutils().currRealTime()),
	poisonCD_(7000),
	timeLastUpdate_(sdlutils().currRealTime()),
	updateCD_(1500),

	invincible_(false),
	invincibilityTime_(sdlutils().currRealTime()),
	abilityInvul_(false),

	hms_(nullptr),
	hmsText_(nullptr),
	enmState_(nullptr),
	tr_(nullptr)
{}

void EntityAttribs::init() {
	// Estados si es jugador o enemigo
	if (!entity_->hasGroup<Enemy>()) {
		hms_ = entity_->getComponent<HamsterStateMachine>();
		//assert(hms_ != nullptr);
	}
	else {
		enmState_ = entity_->getComponent<EnemyStateMachine>();
		//assert(enmState_ != nullptr);
	}
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void EntityAttribs::update() {
	//Timer de invencibilidad
	if (invincible_ && sdlutils().currRealTime() > invincibilityTime_ + INVINCIBLECD) {
		invincible_ = false;
	}
	//Timer de envenenamiento
	if (poisoned_) {
		//cada x segundos
		if (sdlutils().currRealTime() >= timeLastUpdate_ + updateCD_) {
			//Daño por veneno
			recieveDmg(poisonDamage_);
			timeLastUpdate_ = sdlutils().currRealTime();
		}
		if (sdlutils().currRealTime() >= poisonTime_ + poisonCD_) {
			poisoned_ = false;
		}
	}
}

//Resta el da�o y devuelve true si ha muerto
bool EntityAttribs::recieveDmg(int dmg) {
	if (!invincible_) {
		health_ -= dmg;
		//Timer de invulnerabilidad
		invincibilityTime_ = sdlutils().currRealTime();
		invincible_ = true;
		//Actualizamos la healthBar
		if (entity_->hasComponent<UI>())
			entity_->getComponent<UI>()->bar(-dmg);
		std::cout << "me cago en tus muertos" << health_ << std::endl;
		//Si la vida ha bajado de 0...
		if (health_ <= 0) {
			if (hms_ != nullptr) {
				hms_->getState() = HamStates::DEAD;
			}
			else if (enmState_ != nullptr) {
				enmState_->getState() = EnemyStates::ENM_DEAD;
			}
			//Actualizamos UI
			if (entity_->hasComponent<UI>())
				entity_->getComponent<UI>()->dep();
			//Actualizamos UI
			if (entity_->hasComponent<HeartUI>())
				entity_->getComponent<HeartUI>()->dep();

			health_ = 0;
			//Desactivamos la entidad
			die();

			//entity_->setActive(false);

			return true;
		}
		else
			return false;
	}
	return false;
}

void EntityAttribs::die() {

	//Creamos una entidad
	Entity* e = entity_->getMngr()->addEntity();

	//Le metemos un transform para su posicion
	e->addComponent<Transform>(tr_->getPos(), Vector2D(0, 0), tr_->getW(), tr_->getH(), 0, tr_->getZ(), tr_->getFlip());

	//Y reproducimos la animacion de muerto
	e->addComponent<Animator>(&sdlutils().images().at("sardinillaSheet"),
		86,
		86,
		3,
		3,
		220,
		Vector2D(0, 0),
		3)->play(sdlutils().anims().at("sardinilla_death"));

	entity_->setActive(false);
	//Si la persona que muere es un hamster...
	if (!entity_->hasGroup<Enemy>()) {
		//Ponemos su UI a 'Muerto'
		e->addComponent<UI>(id_, entity_->getComponent<UI>()->getPosUI())->dep();
		hms_->getState() = HamStates::DEAD;
	}
	else {
		e->addComponent<Dying>();
		enmState_->getState() = EnemyStates::ENM_DEAD;
		entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>()->reduceNumberEnemyRoom();	//Reduce el numero total de enemigos que hay en una sala
	}

	//Desactivamos el componente del hasmter vivo

}


//Sana 'hp' unidades
void EntityAttribs::heal(int hp) {
	if (health_ + hp >= maxHealth_) {
		hp = maxHealth_ - health_;
		health_ = maxHealth_;
	}
	else {
		health_ += hp;
	}
	if (entity_->hasComponent<UI>())
		entity_->getComponent<UI>()->bar(hp);

	std::cout << "ave maria" << health_ << std::endl;
}

void EntityAttribs::addCritProbability(float probability) {

	critProbability_ += probability;

	if (critProbability_ > maxCrit_) {
		critProbability_ = maxCrit_;
	}
}

//Comienza el envenenamiento
void EntityAttribs::poison() {
	//int SDL_SetTextureColorMod(hmsText_, 96, 227, 70);
	poisonTime_ = sdlutils().currRealTime();
	poisoned_ = true;
}