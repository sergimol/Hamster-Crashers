#include "Roll.h"
#include "Movement.h"
#include "Animator.h"
#include "Stroke.h"
#include "CollisionDetec.h"


void Roll::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	st_ = entity_->getComponent<HamsterStateMachine>();
	assert(st_ != nullptr);

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

	speed_ = entity_->getComponent<EntityAttribs>()->getVel();
	assert(speed_ != Vector2D());

	col_ = entity_->getComponent<CollisionDetec>();
	assert(col_ != nullptr);

	keymap.insert({ UP, false });
	keymap.insert({ DOWN, false });
	keymap.insert({ RIGHT, false });
	keymap.insert({ LEFT, false });
}

Roll::~Roll() {
}

void Roll::action()
{
	if (entity_->getComponent<Movement>()->isActive()) {
		entity_->getComponent<Movement>()->setActive(false);

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
		anim_->play(sdlutils().anims().at("sardinilla_ability"));

		SDL_Rect rectPlayer = tr_->getRectCollide();
		rectPlayer.x += tr_->getVel().getX();
		rectPlayer.y += tr_->getVel().getY();
		col_->tryToMove(tr_->getVel(), goalVel_, rectPlayer);
		//Mete invulnerabilidad durante la habilidad
		entity_->getComponent<EntityAttribs>()->setInvincibility(true);
	}
}

void Roll::updateKeymap(KEYS x, bool is) {
	keymap.at(x) = is;
}

void Roll::update() {

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
			vel.setX(col_->lerp(goalVel_.getX(), vel.getX(), 0.95));
			vel.setY(col_->lerp(goalVel_.getY(), vel.getY(), 0.95));
		}

		SDL_Rect rectPlayer = tr_->getRectCollide();
		rectPlayer.x += vel.getX();
		rectPlayer.y += vel.getY();
		col_->tryToMove(vel, goalVel_, rectPlayer);
		//Si se colisiona..
		if (checkCollisions())
			//Suena el hit y le pega
			hitSound_.play();
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

		//Cogemos el transform del jugador
		auto pTr = entity_->getComponent<Transform>();

		EntityAttribs* eAttribs = ents[i]->getComponent<EntityAttribs>();

		//Comprobamos si hay colision
		if (!eAttribs->checkInvulnerability() && Collisions::collides(pTr->getPos(), pTr->getW(), pTr->getH(), eTr->getPos(), eTr->getW(), eTr->getH()))
		{
			//he puesto que le matas de una 
			//creo que lo suyo seria stunnearlo y quitar la mitad de la vida o asi
			int dmg = eAttribs->getMaxLife();
			if (eAttribs->getLife() > 0)
			{
				eAttribs->recieveDmg(dmg);
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
}