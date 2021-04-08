#include "EntityAttribs.h"

EntityAttribs::EntityAttribs() :
	health_(100),
	maxHealth_(100),
	strokeResist_(0.0),
	attackRange_(0.0),
	critProbability_(0.05),
	maxCrit_(0.2),
	critDamage_(1.0),
	poisonDamage_(2),
	velocity_(Vector2D(7, 3.5)),
	cadence_(0.0),
	damage_(20),
	poisonProbability_(0.0),
	canPoison_(poisonProbability_ > 0),
	poisonCD_(7000),
	updateCD_(1500),
	invincible_(false),
	poisonTime_(sdlutils().currRealTime()),
	invincibilityTime_(sdlutils().currRealTime()),
	hms_(nullptr),
	poisoned_(false),
	enmState_(nullptr)
{}

EntityAttribs::EntityAttribs(int life, float range, std::string id, Vector2D speed, int number, float poisonProb) :
	health_(life),
	maxHealth_(life),
	strokeResist_(0.0),
	attackRange_(range),
	critProbability_(0.05),
	maxCrit_(0.2),
	critDamage_(1.0),
	velocity_(speed),
	damage_(20),
	poisonDamage_(2),
	poisonCD_(7000),
	updateCD_(1500),
	poisonProbability_(poisonProb),
	canPoison_(poisonProbability_ > 0),
	invincible_(false),
	hms_(nullptr),
	id_(id),
	cadence_(0.0),
	poisoned_(false),
	poisonTime_(sdlutils().currRealTime()),
	invincibilityTime_(sdlutils().currRealTime()),
	enmState_(nullptr),
	playerNumber_(number)
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

}

void EntityAttribs::update() {
	//Timer de invencibilidad
	if (invincible_ && sdlutils().currRealTime() > invincibilityTime_ + INVINCIBLECD) {
		invincible_ = false;
	}
	//Timer de envenenamiento
	else if (poisoned_) {
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
			//entity_->setActive(false);

			return true;
		}
		else
			return false;
	}
	return false;
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