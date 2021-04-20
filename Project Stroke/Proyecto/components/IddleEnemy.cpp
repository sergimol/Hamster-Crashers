#include "IddleEnemy.h"
#include "Stroke.h"
#include "FleeFromPlayer.h"

IddleEnemy::IddleEnemy() :
	mov_(nullptr), tr_(nullptr), rangeOffsetX_(250), rangeOffsetY_(100), lockedHamState_(nullptr), lockedHamster_(nullptr), hamsterTr_(nullptr), hamsId_(-1) {
}

void IddleEnemy::init() {
	Entity* owEntity = owner_->getEntity();
	mov_ = owEntity->getComponent<MovementSimple>();
	assert(mov_ != nullptr);

	tr_ = owEntity->getComponent<Transform>();
	assert(tr_ != nullptr);

	enAtk_ = owEntity->getComponent<EnemyAttack>();
	assert(enAtk_ != nullptr);

	hamsters_ = owEntity->getMngr()->getPlayers();

	//el puto iddle no necesita hacer lock hamster lockHamster(); // De momento un hamster concreto para manejar mejor
	/*
	assert(lockedHamster_ != nullptr);
	assert(lockedHamState_ != nullptr);
	assert(hamsterTr_ != nullptr);
	*/

	//poner todo a false

	//se supone que los para >:C
}


//Fija a un hamster en orden desde el siguiente al último elegido
void IddleEnemy::lockHamster() {
	//Variable que contralará el recorrido de los hamsters
	int start;
	if (hamsId_ + 1 == hamsters_.size()) {
		start = 0;
	}
	else {
		start = hamsId_ + 1;
	}

	//Va comprobando cual es elegible;
	lockedHamster_ = nullptr;
	for (int i = start; i != hamsId_ && lockedHamster_ == nullptr; i++) {
		//Si puede ser elegido
		lockedHamState_ = hamsters_[i]->getComponent<HamsterStateMachine>();
		if (!lockedHamState_->cantBeTargeted()) {
			//Elige hamster
			hamsId_ = i;
			lockedHamster_ = hamsters_[i];
			hamsterTr_ = lockedHamster_->getComponent<Transform>();
		}
		//Si llega al final, da la vuelta
		if (i + 1 == hamsters_.size()) {
			i = 0;
		}
		//Si es -1, entra en el ciclo de ids
		if (hamsId_ == -1)
			hamsId_ = 0;
	}
	//Si ninguno esta activo pone todo a null
	if (lockedHamster_ == nullptr) {
		lockedHamState_ = nullptr;
		hamsterTr_ = nullptr;
		hamsId_ = -1;
	}
}

//Fija a un hamster concreto
void IddleEnemy::lockHamster(int id) {
	lockedHamster_ = hamsters_[id];
	hamsterTr_ = lockedHamster_->getComponent<Transform>();
	lockedHamState_ = lockedHamster_->getComponent<HamsterStateMachine>();
}

//Esta a rango de ataque
bool IddleEnemy::isWithinAttackRange() {
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

void IddleEnemy::behave() {
	//no hay nada esta iddle es un fideo
	//que se yo imagina que estamos en un solo jugador, si esta infartado no se le puede traquear pos los bichos se paran, y aqui lo que decimos es que intenten lockear a alguien ahsta que puedan, aka cuando se recupere de un infarto, danlles te lo he puesto todo en un linea porque vas a ser tu quien lo lea con carinyo el nene

	mov_->updateKeymap(MovementSimple::DOWN, false);
	mov_->updateKeymap(MovementSimple::UP, false);
	mov_->updateKeymap(MovementSimple::LEFT, false);
	mov_->updateKeymap(MovementSimple::RIGHT, false);
}

/*
void FollowPlayer::onEnable() {
	lockHamster();
}

void FollowPlayer::onDisable() {

	mov_->updateKeymap(MovementSimple::RIGHT, false);
	mov_->updateKeymap(MovementSimple::LEFT, false);
	mov_->updateKeymap(MovementSimple::DOWN, false);
	mov_->updateKeymap(MovementSimple::UP, false);

	lockedHamster_ = nullptr;
}
*/