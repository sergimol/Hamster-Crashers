#include "FollowPlayer.h"
#include "Stroke.h"
#include "FleeFromPlayer.h"
#include "IddleEnemy.h"

FollowPlayer::FollowPlayer() :
	rangeOffsetX_(250), rangeOffsetY_(50) {
}

void FollowPlayer::init() {
	Entity* owEntity = owner_->getEntity();

	enmState_ = owEntity->getComponent<EnemyStateMachine>();
	assert(enmState_ != nullptr);

	mov_ = owEntity->getComponent<MovementSimple>();
	assert(mov_ != nullptr);

	tr_ = owEntity->getComponent<Transform>();
	assert(tr_ != nullptr);

	enAtk_ = owEntity->getComponent<EnemyAttack>();
	assert(enAtk_ != nullptr);

	hamsters_ = owEntity->getMngr()->getPlayers(); //no la necesitamos pero es que me da pereza tocar el lockHamster

	/* Ya no, ahora dependemos de mama para que nos diga a quien vamos a fijar
	lockHamster(); // De momento un hamster concreto para manejar mejor
	assert(lockedHamster_ != nullptr);
	assert(lockedHamState_ != nullptr);
	assert(hamsterTr_ != nullptr);
	*/
}

//Esta a rango de ataque
bool FollowPlayer::isWithinAttackRange() {
	auto hamPos = hamsterTr_->getRectCollide();
	auto pos = tr_->getRectCollide();

	auto width = pos.w;
	auto hamWidth = hamPos.w;

	int hamX = hamPos.x,
		hamY = hamPos.y + hamPos.h,
		x = pos.x,
		y = pos.y + pos.h;

	return((hamX <= x + width + width / 2 && hamX + hamWidth >= x - width / 2) &&
		(hamY + rangeOffsetY_ >= y && hamY - rangeOffsetY_ / 10 <= y));
}

//Esta a rango de ataque OUTDATED
//bool FollowPlayer::isWithinAttackRange() {
//	auto width = tr_->getW();
//	auto hamWidth = hamsterTr_->getW();
//
//	auto& hamPos = hamsterTr_->getPos();
//	auto& pos = tr_->getPos();
//	int hamX = hamPos.getX(),
//		hamY = hamPos.getY() + hamsterTr_->getH(),
//		x = pos.getX(),
//		y = pos.getY() + tr_->getH();
//
//	return((hamX /*+ rangeOffsetX_*/ + hamWidth * 2 >= x + width && hamX + hamWidth - rangeOffsetX_ <= x + width) &&
//		(hamY + rangeOffsetY_ >= y && hamY - rangeOffsetY_ / 10 <= y));
//}

void FollowPlayer::behave() {
	if (lockedHamster_ != nullptr) {

		// Cambia el foco si el actual muere o le da un infarto
		auto& state = lockedHamState_->getState();
		if (lockedHamState_->cantBeTargeted()) {
			//le pedira a su madre que le reasigne objetivo
			//TODO MOM
			//se pone en iddle (como parte de codigo defensivo, ya que
			//al entrar en al lista por defecto deberia de estar en iddle)
			owner_->SetBehavior(new IddleEnemy); //y chinpong
		}
		else if (enmState_->getState() != EnemyStates::ENM_STUNNED) { // si no cambia de hamster marcado y no está aturdido
			auto hamPos = hamsterTr_->getRectCollide();
			auto pos = tr_->getRectCollide();

			auto width = pos.w;
			auto hamWidth = hamPos.w;

			int hamX = hamPos.x,
				hamY = hamPos.y + hamPos.h,
				x = pos.x,
				y = pos.y + pos.h;

			auto& flip = tr_->getFlip();

			if (x + width / 2 < hamX + hamWidth / 2)
				flip = false;
			else
				flip = true;

			if (!isWithinAttackRange()) {
				// Movimiento del enemigo en base a pos del jugador
				if (y < hamY - rangeOffsetY_ / 10)
					mov_->updateKeymap(MovementSimple::DOWN, true);
				else
					mov_->updateKeymap(MovementSimple::DOWN, false);
				if (y > hamY + rangeOffsetY_)
					mov_->updateKeymap(MovementSimple::UP, true);
				else
					mov_->updateKeymap(MovementSimple::UP, false);


				if (hamX + hamWidth < x - width / 2)
					mov_->updateKeymap(MovementSimple::LEFT, true);
				else
					mov_->updateKeymap(MovementSimple::LEFT, false);
				if (hamX > x + width + width / 2)
					mov_->updateKeymap(MovementSimple::RIGHT, true);
				else
					mov_->updateKeymap(MovementSimple::RIGHT, false);
			}
			else { // Si est� a rango, no necesita moverse e intentara atacar

				mov_->updateKeymap(MovementSimple::RIGHT, false);
				mov_->updateKeymap(MovementSimple::LEFT, false);
				mov_->updateKeymap(MovementSimple::DOWN, false);
				mov_->updateKeymap(MovementSimple::UP, false);

				enAtk_->LaunchAttack();
			}
		}
	}
}

//void FollowPlayer::behave() {
//
//	Entity* owEntity = owner_->getEntity();
//	if (owEntity->getComponent<EntityAttribs>()->getLife() <= 40) {
//		/*
//		owner_->SetBehavior(new FleeFromPlayer);
//		return;
//		*/
//	}
//	else if (lockedHamster_ != nullptr) {
//
//		// Cambia el foco si el actual muere o le da un infarto
//		auto& state = lockedHamState_->getState();
//		if (lockedHamState_->cantBeTargeted()) {
//			//le pedira a su madre que le reasigne objetivo
//			//TODO MOM
//			//se pone en iddle (como parte de codigo defensivo, ya que
//			//al entrar en al lista por defecto deberia de estar en iddle)
//			owner_->SetBehavior(new IddleEnemy); //y chinpong
//		}
//		else if (enmState_->getState() != EnemyStates::ENM_STUNNED) { // si no cambia de hamster marcado y no está aturdido
//			auto& hamPos = hamsterTr_->getPos();
//			auto& pos = tr_->getPos();
//			int hamX = hamPos.getX(),
//				hamY = hamPos.getY() + hamsterTr_->getH(),
//				x = pos.getX(),
//				y = pos.getY() + tr_->getH();
//
//			auto width = tr_->getW();
//			auto hamWidth = hamsterTr_->getW();
//			auto& flip = tr_->getFlip();
//
//			if (x + width / 2 < hamX + hamWidth / 2)
//				flip = false;
//			else
//				flip = true;
//
//			if (!isWithinAttackRange()) {
//				// Movimiento del enemigo en base a pos del jugador
//				if (y < hamY - rangeOffsetY_ / 10)
//					mov_->updateKeymap(MovementSimple::DOWN, true);
//				else
//					mov_->updateKeymap(MovementSimple::DOWN, false);
//				if (y > hamY + rangeOffsetY_)
//					mov_->updateKeymap(MovementSimple::UP, true);
//				else
//					mov_->updateKeymap(MovementSimple::UP, false);
//
//
//				if (x > hamX + rangeOffsetX_)
//					mov_->updateKeymap(MovementSimple::LEFT, true);
//				else
//					mov_->updateKeymap(MovementSimple::LEFT, false);
//				if (x < hamX - rangeOffsetX_ / 2 - tr_->getW() / 2)
//					mov_->updateKeymap(MovementSimple::RIGHT, true);
//				else
//					mov_->updateKeymap(MovementSimple::RIGHT, false);
//			}
//			else { // Si est� a rango, no necesita moverse e intentara atacar
//
//				mov_->updateKeymap(MovementSimple::RIGHT, false);
//				mov_->updateKeymap(MovementSimple::LEFT, false);
//				mov_->updateKeymap(MovementSimple::DOWN, false);
//				mov_->updateKeymap(MovementSimple::UP, false);
//
//				enAtk_->LaunchAttack();
//			}
//		}
//	}
//}
