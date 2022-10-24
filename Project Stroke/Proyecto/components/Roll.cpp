#include "Roll.h"
#include "Movement.h"
#include "Animator.h"
#include "Stroke.h"
#include "CollisionDetec.h"
#include "EnemyStun.h"
#include "Knockback.h"
#include "AnimEnemyStateMachine.h"
#include "EnemyStateMachine.h"
#include "AnimHamsterStateMachine.h"


void Roll::init() {
	Ability::init();

	speed_ = entity_->getComponent<EntityAttribs>()->getVel();
	assert(speed_ != Vector2D());

	col_ = entity_->getComponent<CollisionDetec>();
	assert(col_ != nullptr);

	mov_ = entity_->getComponent<Movement>();
	assert(mov_ != nullptr);

	grav_ = entity_->getComponent<Gravity>();
	assert(grav_ != nullptr);



	keymap.insert({ UP, false });
	keymap.insert({ DOWN, false });
	keymap.insert({ RIGHT, false });
	keymap.insert({ LEFT, false });
}

Roll::~Roll() {
}

void Roll::action()
{
	if (mov_->isActive()) {

		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("sardinillaSpecial");

		mov_->setActive(false);

		rolling = true;

		dir_ = entity_->getComponent<Movement>()->getLastDir();

		if (dir_ == Vector2D(0, 0)) {
			if (tr_->getFlip())
				tr_->getVel().setX(-iniAccel);
			else
				tr_->getVel().setX(iniAccel);
		}
		else {
			tr_->getVel() = dir_ * iniAccel;
		}

		SDL_Rect rectPlayer = tr_->getRectCollide();
		rectPlayer.x += tr_->getVel().getX();
		rectPlayer.y += tr_->getVel().getY() + tr_->getFloor();

		SDL_Rect rectFoot = tr_->getRectCollideFeet();
		rectFoot.x += goalVel_.getX();
		rectFoot.y += goalVel_.getY() + tr_->getFloor();

		col_->tryToMove(dir_, goalVel_, rectPlayer, false);
		col_->tryToMoveObs(dir_, goalVel_, rectFoot, false);

		//Mete invulnerabilidad durante la habilidad
		entity_->getComponent<EntityAttribs>()->setInvincibility(true);
	}
}

void Roll::updateKeymap(KEYS x, bool is) {
	keymap.at(x) = is;
}

void Roll::update() {
	if (state_->getState() == GameStates::RUNNING) {
		Ability::update();
		auto& state = st_->getState();

		if (rolling)
		{
			auto& vel = tr_->getVel();
			auto& z = tr_->getZ();
			auto& velZ = tr_->getVelZ();

			if (keymap.at(UP)) {
				dir_.setY(-1.0f);
			}
			else if (keymap.at(DOWN)) {
				dir_.setY(1.0f);
			}

			if (keymap.at(RIGHT)) {
				dir_.setX(1.0f);
				tr_->getFlip() = false;
			}
			else if (keymap.at(LEFT)) {
				dir_.setX(-1.0f);
				tr_->getFlip() = true;
			}

			if (dir_.magnitude() != 0) {
				dir_ = dir_.normalize();

				goalVel_ = Vector2D(dir_.getX() * speed_.getX() * maxAccel, dir_.getY() * speed_.getY() * maxAccel);
			}

			if (st_->canMove()) {		//Aceleracion
				vel.setX(sdlutils().lerp(goalVel_.getX(), vel.getX(), 0.95));
				vel.setY(sdlutils().lerp(goalVel_.getY(), vel.getY(), 0.95));
			}

			SDL_Rect rectPlayer = tr_->getRectCollide();
			rectPlayer.x += goalVel_.getX();
			rectPlayer.y += goalVel_.getY() + tr_->getFloor();

			SDL_Rect rectFoot = tr_->getRectCollideFeet();
			rectFoot.x += goalVel_.getX();
			rectFoot.y += goalVel_.getY() + tr_->getFloor();

			col_->tryToMove(dir_, goalVel_, rectPlayer, false);
			col_->tryToMoveObs(dir_, goalVel_, rectFoot, false);

			if (grav_->isActive())
				grav_->checkHeight(rectPlayer);

			if (grav_->getStuck())  vel.setX(-vel.getX());
			//Si se colisiona..
			if (checkCollisions())
				entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("lighthit");
		}
	}
}

bool Roll::checkCollisions()
{
	//Comprueba si has golpeado
	bool hit = false;

	//Cogemos todas las entidades
	auto& ents = entity_->getMngr()->getEnemies();

	//Recorremos la lista de componentes
	for (int i = 0; i < ents.size(); ++i)
	{
		//Si es un enemigo

			//Cogemos el transform del enemigo
		auto eTr = ents[i]->getComponent<Transform>();
		auto eColRect = eTr->getRectCollide();

		//Cogemos el transform del jugador
		auto pTr = entity_->getComponent<Transform>();
		auto pColRect = pTr->getRectCollide();

		EntityAttribs* eAttribs = ents[i]->getComponent<EntityAttribs>();

		//Comprobamos si hay colision
		if (!eAttribs->checkInvulnerability() && Collisions::collides(Vector2D(pColRect.x, pColRect.y), pColRect.w, pColRect.h, Vector2D(eColRect.x, eColRect.y), eColRect.w, eColRect.h))
		{
			//he puesto que le matas de una 
			//creo que lo suyo seria stunnearlo y quitar la mitad de la vida o asi
			//abDmg_ = eAttribs->getMaxLife();

			auto& enmStateM = ents[i]->getComponent<EnemyStateMachine>()->getState();
			if (enmStateM != EnemyStates::ENM_DEAD)
			{

				//Si tiene stun, se aplica
				EnemyStun* enmStun = ents[i]->getComponent<EnemyStun>();
				if (enmStun != nullptr && enmStun->isActive()) {

					ents[i]->getComponent<AnimEnemyStateMachine>()->setAnimBool(EnemyStatesAnim::HITTED, true);

					//Si no estaba aturdido ya
					if (enmStateM != EnemyStates::ENM_STUNNED) {
						//Aturdimos al enemigo
						enmStateM = EnemyStates::ENM_STUNNED;
					}
					//Reiniciamos tiempo de stun
					enmStun->restartStunTime(true);
				}

				//Si tiene Knockback, se aplica
				Knockback* enmKnockback = ents[i]->getComponent<Knockback>();
				if (enmKnockback != nullptr) {
					//Damos la vuelta si es atacado por detras
					auto& enmFlip = eTr->getFlip();
					if (enmFlip == tr_->getFlip())
						enmFlip = !enmFlip;

					enmKnockback->setKnockbackDistance(85);
					enmKnockback->knockback();
					enmKnockback->setKnockbackDistance(5);
				}

				eAttribs->recieveDmg(abDmg_);
				hit = true;
				entity_->getMngr()->refreshEnemies();
			}
		}

	}

	return hit;
}

void Roll::endAbility() {
	entity_->getComponent<Movement>()->setActive(true);
	rolling = false;
	tr_->getVel() = Vector2D(0, 0);
	entity_->getComponent<EntityAttribs>()->setInvincibility(false);

	//DESACTIVAMOS LA ANIMACION
	entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::ABILITY, false);
}