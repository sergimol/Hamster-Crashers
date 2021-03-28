#include "EntityAttribs.h"

EntityAttribs::EntityAttribs() :
	health_(100),
	maxHealth_(100),
	strokeResist_(0.0),
	attackRange_(0.0),
	critProbability_(0.05),
	maxCrit_(0.2),
	critDamage_(1.0),
	velocity_(Vector2D(7, 3.5)),
	damage_(20),
	cadence_(0.0)
{}

EntityAttribs::EntityAttribs(int life, std::string id) :
	health_(life),
	maxHealth_(life),
	strokeResist_(0.0),
	attackRange_(0.0),
	critProbability_(0.05),
	maxCrit_(0.2),
	critDamage_(1.0),
	velocity_(Vector2D(7, 3.5)),
	damage_(20),
	id_(id),
	cadence_(0.0)
{}

EntityAttribs::EntityAttribs(int life, float range, std::string id) :
	health_(life),
	maxHealth_(life),
	strokeResist_(0.0),
	attackRange_(range),
	critProbability_(0.05),
	maxCrit_(0.2),
	critDamage_(1.0),
	velocity_(Vector2D(7, 3.5)),
	damage_(20),
	id_(id),
	cadence_(0.0)
{}

void EntityAttribs::init() {
	hms_ = entity_->getComponent<HamsterStateMachine>();
}

void EntityAttribs::update() {
	//Timer de invencibilidad
	if (invencible_ && sdlutils().currRealTime() > time + INVENCIBLECD) {
		invencible_ = false;
	}
}

//Resta el da�o y devuelve true si ha muerto
bool EntityAttribs::recieveDmg(int dmg) {

	if (!invencible_) {
		//Timer de invulnerabilidad
		time = sdlutils().currRealTime();
		invencible_ = true;

		health_ -= dmg;
		//std::cout << health_ << std::endl;
		//Actualizamos la healthBar
		if (entity_->hasComponent<UI>())
			entity_->getComponent<UI>()->bar(-dmg);
		std::cout << "me cago en tus muertos" << health_ << std::endl;
		//Si la vida ha bajado de 0...
		if (health_ <= 0) {
			if (hms_ != nullptr) {
				hms_->getState() = HamStates::DEAD;
			}
			//Actualizamos UI
			if (entity_->hasComponent<UI>())
				entity_->getComponent<UI>()->dep();

			health_ = 0;
			//Desactivamos la entidad
			//entity_->setActive(false);

			return true;
		}
		else
			return false;
	}
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