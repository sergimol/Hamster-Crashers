#include "AmbushPlayer.h"
#include "Stroke.h"

AmbushPlayer::AmbushPlayer() :
	mov_(nullptr), tr_(nullptr), rangeX_(500), rangeY_(200), rangeOffsetX_(100), rangeOffsetY_(100), lockedHamState_(nullptr), lockedHamster_(nullptr), hamsterTr_(nullptr) {
}

void AmbushPlayer::init() {
	Entity* owEntity = owner_->getEntity();
	mov_ = owEntity->getComponent<MovementSimple>();
	assert(mov_ != nullptr);

	tr_ = owEntity->getComponent<Transform>();
	assert(tr_ != nullptr);

	enAtk_ = owEntity->getComponent<EnemyAttack>();
	assert(enAtk_ != nullptr);

	hamsters_ = owEntity->getMngr()->getPlayers();

	lockHamster(); // De momento un hamster concreto para manejar mejor
	assert(lockedHamster_ != nullptr);
	assert(lockedHamState_ != nullptr);
	assert(hamsterTr_ != nullptr);
}


//Fija a un hamster aleatorio
void AmbushPlayer::lockHamster() {
	int hamstId = sdlutils().rand().nextInt(0, hamsters_.size());
	lockedHamster_ = hamsters_[hamstId];
	hamsterTr_ = lockedHamster_->getComponent<Transform>();
	lockedHamState_ = lockedHamster_->getComponent<HamsterStateMachine>();
}

//Fija a un hamster concreto
void AmbushPlayer::lockHamster(int id) {
	lockedHamster_ = hamsters_[id];
	hamsterTr_ = lockedHamster_->getComponent<Transform>();
	lockedHamState_ = lockedHamster_->getComponent<HamsterStateMachine>();
}

//Esta a rango de ataque
bool AmbushPlayer::isWithinRange() {
	auto width = tr_->getW();
	auto hamWidth = hamsterTr_->getW();

	auto& hamPos = hamsterTr_->getPos();
	auto& pos = tr_->getPos();
	int hamX = hamPos.getX(),
		hamY = hamPos.getY() + hamsterTr_->getH(),
		x = pos.getX(),
		y = pos.getY() + tr_->getH(),
		xMidPoint = x + (width / 2),
		hamMidPointX = hamX + hamWidth / 2,
		distX = xMidPoint - hamMidPointX,
		distY = y - hamY;

	return((abs(distX) < rangeX_) && (abs(distY) < rangeY_));
}

void AmbushPlayer::behave() {
	if ( lockedHamster_ != nullptr) {
		// Cambia el foco si el actual muere o le da un infarto
		auto& state = lockedHamState_->getState();
		if (lockedHamState_->cantBeTargeted()) {
			lockHamster(); // Habr�a que hacerlo quitando el actual para que no repita
		}
		auto& hamPos = hamsterTr_->getPos();
		auto& pos = tr_->getPos();

		auto width = tr_->getW();
		auto hamWidth = hamsterTr_->getW();

		int hamX = hamPos.getX(),
			hamY = hamPos.getY() + hamsterTr_->getH(),
			x = pos.getX(),
			y = pos.getY() + tr_->getH(),
			xMidPoint = x + (width / 2),
			hamMidPointX = hamX + hamWidth / 2,
			distX = xMidPoint - hamMidPointX,
			distY = y - hamY;

		auto& flip = tr_->getFlip();

		if (x + width / 2 < hamX + hamWidth / 2)
			flip = false;
		else
			flip = true;

		//para evitar que una instruccion se quede atascada entre el offset
		mov_->updateKeymap(MovementSimple::RIGHT, false);
		mov_->updateKeymap(MovementSimple::LEFT, false);
		mov_->updateKeymap(MovementSimple::DOWN, false);
		mov_->updateKeymap(MovementSimple::UP, false);

		if (!isWithinRange()) {
			// Movimiento del enemigo en base a pos del jugador
			
		std:cout << "acercandome  \n";
			if (y < hamY - rangeY_ / 10)
				mov_->updateKeymap(MovementSimple::DOWN, true);
			else
				mov_->updateKeymap(MovementSimple::DOWN, false);
			if (y > hamY + rangeY_)
				mov_->updateKeymap(MovementSimple::UP, true);
			else
				mov_->updateKeymap(MovementSimple::UP, false);


			if (x > hamX + rangeX_)
				mov_->updateKeymap(MovementSimple::LEFT, true);
			else
				mov_->updateKeymap(MovementSimple::LEFT, false);
			if (x < hamX - rangeX_ / 2 - tr_->getW() / 2)
				mov_->updateKeymap(MovementSimple::RIGHT, true);
			else
				mov_->updateKeymap(MovementSimple::RIGHT, false);
			
		}
		else { // Si esta por debajo del rango, s emueve en la direccion contraia para mantener la distancia

			cout << "Esoty dentro\n";
			//Parte Y

			if (distY > 0 && distY <= rangeY_ - rangeOffsetY_)
				mov_->updateKeymap(MovementSimple::DOWN, true);
			else
				mov_->updateKeymap(MovementSimple::DOWN, false);
			if (distY < 0 && distY > -rangeY_ + rangeOffsetY_)
				mov_->updateKeymap(MovementSimple::UP, true);
			else
				mov_->updateKeymap(MovementSimple::UP, false);



			//PARTE X
			if (distX > 0 && distX <= rangeX_ - rangeOffsetX_)
				mov_->updateKeymap(MovementSimple::RIGHT, true);
			else
				mov_->updateKeymap(MovementSimple::RIGHT, false);
			if (distX < 0 && distX > -rangeX_ + rangeOffsetX_)
				mov_->updateKeymap(MovementSimple::LEFT, true);
			else
				mov_->updateKeymap(MovementSimple::LEFT, false);

			cout << distY;

			

		}
	}
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