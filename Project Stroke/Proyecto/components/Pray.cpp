#include "Pray.h"
#include "Movement.h"
#include "Animator.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
#include "Life.h"
#include "Transform.h"

Pray::Pray(int dmg, int heal) : Ability(), dmg_(dmg), heal_(heal), evil(true), magicTime(false), waitTime(0.0){
};

Pray::~Pray() {

}

void Pray::init() {
	Ability::init();
	came_ = Game::camera_;
}

void Pray::update() {
	Ability::update();
	if (magicTime) {
		if (sdlutils().currRealTime() > waitTime + WAIT) {
			prayAbility();
		}
	}

}

void Pray::action() {
	waitTime = sdlutils().currRealTime();
	magicTime = true;
}

void Pray::prayAbility() {
	magicTime = false;
	auto& ents = entity_->getMngr()->getEnteties();

	for (Entity* e : ents) {
		if (evil) {
			//Si la entidad es un enemigo...
			if (e->hasGroup<Enemy>()) {
				//Cogemos el transform del enemigo
				auto eTR = e->getComponent<Transform>();

				//Creamos su Rect
				SDL_Rect rectEnemy;
				rectEnemy.h = eTR->getH();
				rectEnemy.w = eTR->getW();
				rectEnemy.x = eTR->getPos().getX();
				rectEnemy.y = eTR->getPos().getY();

				//Y comprobamos si colisiona
				if (SDL_HasIntersection(&came_, &rectEnemy)) {
					//Le restamos la vida al enemigo
					e->getComponent<Life>()->recieveDmg(dmg_);
					//entity_->getComponent<Life>()->recieveDmg(dmg_);
				}
			}
		}
		else {
			//Si la entidad es un enemigo...
			if (e->hasGroup<Ally>()) {
				//Cogemos el transform del enemigo
				auto eTR = e->getComponent<Transform>();

				//Creamos su Rect
				SDL_Rect rectEnemy;
				rectEnemy.h = eTR->getH();
				rectEnemy.w = eTR->getW();
				rectEnemy.x = eTR->getPos().getX();
				rectEnemy.y = eTR->getPos().getY();

				//Y comprobamos si colisiona
				if (SDL_HasIntersection(&came_, &rectEnemy)) {
					//Le restamos la vida al enemigo
					if (state_ != HamStates::DEAD && e->getComponent<Life>()->getLife() > 0) //deberia que valer con el DEAD que cuando muera desactive cosas
						e->getComponent<Life>()->heal(heal_);
				}
			}
		}
	}
	evil = !evil;
}

