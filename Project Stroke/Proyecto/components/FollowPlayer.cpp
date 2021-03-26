#include "FollowPlayer.h"
#include "Stroke.h"

FollowPlayer::FollowPlayer(std::vector<Entity*>& players) :
	mov_(nullptr), tr_(nullptr), rangeOffsetX_(50), rangeOffsetY_(50), lockedHamState_(nullptr), lockedHamster_(nullptr), hamsterTr_(nullptr), hamsters_(players) {
}

void FollowPlayer::init() {
	//mov_ = entity_->getComponent<MovementSimple>();
	//assert(mov_ != nullptr);

	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	lockHamster();
	assert(lockedHamster_ != nullptr);
	assert(lockedHamState_ != nullptr);
	assert(hamsterTr_ != nullptr);
}


//Fija a un hamster aleatorio
void FollowPlayer::lockHamster() {
	int hamstId = sdlutils().rand().nextInt(0, hamsters_.size());
	lockedHamster_ = hamsters_[hamstId];
	hamsterTr_ = lockedHamster_->getComponent<Transform>();
	lockedHamState_ = lockedHamster_->getComponent<HamsterStateMachine>();
}

//Fija a un hamster concreto
void FollowPlayer::lockHamster(int id) {
	lockedHamster_ = hamsters_[id];
	hamsterTr_ = lockedHamster_->getComponent<Transform>();
}

//Esta a rango de ataque
bool FollowPlayer::isWithinAttackRange() {
	auto& hamPos = hamsterTr_->getPos();
	auto& pos = tr_->getPos();
	int hamX = hamPos.getX(),
		hamY = hamPos.getX(),
		x = pos.getX(),
		y = pos.getY();

	return((hamX + rangeOffsetX_ >= x && hamX - rangeOffsetX_ <= x) &&
		(hamY + rangeOffsetY_ >= y && hamY - rangeOffsetY_ <= y));
}

void FollowPlayer::update() {
	// Cambia el foco si el actual muere o le da un infarto
	auto& state = lockedHamState_->getState();
	if (state == HamStates::DEAD || state == HamStates::INFARCTED) {
		lockHamster(); // Habría que hacerlo quitando el actual para que no repita
	}
}


void FollowPlayer::onEnable() {
	lockHamster();
}

void FollowPlayer::onDisable() {
}