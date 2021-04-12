#include "EnemyBehaviour.h"
#include "Stroke.h"

EnemyBehaviour::EnemyBehaviour(Behavior* auxbh) :
	mov_(nullptr), tr_(nullptr), rangeOffsetX_(250), rangeOffsetY_(100), lockedHamState_(nullptr), lockedHamster_(nullptr), hamsterTr_(nullptr), bh_(auxbh) {
}

void EnemyBehaviour::init() {
	mov_ = entity_->getComponent<MovementSimple>();
	assert(mov_ != nullptr);

	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	enAtk_ = entity_->getComponent<EnemyAttack>();
	assert(enAtk_ != nullptr);

	hamsters_ = entity_->getMngr()->getPlayers();

	lockHamster(); // De momento un hamster concreto para manejar mejor
	assert(lockedHamster_ != nullptr);
	assert(lockedHamState_ != nullptr);
	assert(hamsterTr_ != nullptr);

	bh_->setOwner(this);
	bh_->init();
}

void EnemyBehaviour::SetBehavior(Behavior* bs) {
	{
		bh_ = bs;
		bh_->init(); 
	}
}


//Fija a un hamster aleatorio
void EnemyBehaviour::lockHamster() {
	int hamstId = sdlutils().rand().nextInt(0, hamsters_.size());
	lockedHamster_ = hamsters_[hamstId];
	hamsterTr_ = lockedHamster_->getComponent<Transform>();
	lockedHamState_ = lockedHamster_->getComponent<HamsterStateMachine>();
}

//Fija a un hamster concreto
void EnemyBehaviour::lockHamster(int id) {
	lockedHamster_ = hamsters_[id];
	hamsterTr_ = lockedHamster_->getComponent<Transform>();
	lockedHamState_ = lockedHamster_->getComponent<HamsterStateMachine>();
}

//Esta a rango de ataque
bool EnemyBehaviour::isWithinAttackRange() {
	auto width = tr_->getW();
	auto hamWidth = hamsterTr_->getW();

	auto& hamPos = hamsterTr_->getPos();
	auto& pos = tr_->getPos();
	int hamX = hamPos.getX(),
		hamY = hamPos.getY() + hamsterTr_->getH(),
		x = pos.getX(),
		y = pos.getY() + tr_->getH();

	return((hamX /*+ rangeOffsetX_*/ + hamWidth * 2 >= x + width && hamX + hamWidth - rangeOffsetX_ <= x + width) &&
		(hamY + rangeOffsetY_ >= y && hamY - rangeOffsetY_ / 10 <= y));
}

void EnemyBehaviour::update() {
	//ejecuta el metodo de behavior que le dice como comportarse (atacar, como moverse, cuando, el hace las condiciones el resto nos olvidamos)
	bh_->behave();
	//tambien seria oportuno que esta misma clase hiciese los cambios de bh_, aunque suene y parezca raro que sea este objeto el que indique cual es
	//el siguiente comportamiento/Behavior no es algo tan descabezado.. <3
}


void EnemyBehaviour::onEnable() {
	lockHamster();
}

void EnemyBehaviour::onDisable() {

	mov_->updateKeymap(MovementSimple::RIGHT, false);
	mov_->updateKeymap(MovementSimple::LEFT, false);
	mov_->updateKeymap(MovementSimple::DOWN, false);
	mov_->updateKeymap(MovementSimple::UP, false);

	lockedHamster_ = nullptr;
}