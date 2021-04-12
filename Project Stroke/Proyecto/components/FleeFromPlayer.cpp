﻿#include "FleeFromPlayer.h"
#include "Stroke.h"

FleeFromPlayer::FleeFromPlayer() :
	mov_(nullptr), tr_(nullptr), rangeOffsetX_(600), rangeOffsetY_(100), rangeOffset_(50), lockedHamState_(nullptr), lockedHamster_(nullptr), hamsterTr_(nullptr) {
}

void FleeFromPlayer::init() {
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
void FleeFromPlayer::lockHamster() {
	int hamstId = sdlutils().rand().nextInt(0, hamsters_.size());
	lockedHamster_ = hamsters_[hamstId];
	hamsterTr_ = lockedHamster_->getComponent<Transform>();
	lockedHamState_ = lockedHamster_->getComponent<HamsterStateMachine>();
}

//Fija a un hamster concreto
void FleeFromPlayer::lockHamster(int id) {
	lockedHamster_ = hamsters_[id];
	hamsterTr_ = lockedHamster_->getComponent<Transform>();
	lockedHamState_ = lockedHamster_->getComponent<HamsterStateMachine>();
}

//Esta a rango de debe de huir 
bool FleeFromPlayer::isWithinRange() {
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
		distX = xMidPoint - hamMidPointX;

	return((abs(distX) < rangeOffsetX_));
}

void FleeFromPlayer::behave() {
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
			distX = xMidPoint - hamMidPointX;

		auto& flip = tr_->getFlip();

		if (x + width / 2 < hamX + hamWidth / 2)
			flip = true;
		else
			flip = false;

		if (isWithinRange()) {


		std:cout << "Estoy dentro jefe\n";

			if (distX >= 0)
				mov_->updateKeymap(MovementSimple::RIGHT, true);
			else
				mov_->updateKeymap(MovementSimple::RIGHT, false);
			if (distX < 0)
				mov_->updateKeymap(MovementSimple::LEFT, true);
			else
				mov_->updateKeymap(MovementSimple::LEFT, false);
		}
		else { // Si esta por debajo del rango, se queda quieto
			/*
			// Movimiento del enemigo en base a pos del jugador
			if (y < hamY - rangeOffsetY_ / 10)
				mov_->updateKeymap(MovementSimple::DOWN, true);
			else
				mov_->updateKeymap(MovementSimple::DOWN, false);
			if (y > hamY + rangeOffsetY_)
				mov_->updateKeymap(MovementSimple::UP, true);
			else
				mov_->updateKeymap(MovementSimple::UP, false);
			*/

		mov_->updateKeymap(MovementSimple::RIGHT, false);
		mov_->updateKeymap(MovementSimple::LEFT, false);
		mov_->updateKeymap(MovementSimple::DOWN, false);
		mov_->updateKeymap(MovementSimple::UP, false);

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