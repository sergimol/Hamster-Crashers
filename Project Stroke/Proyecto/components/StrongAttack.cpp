#include "StrongAttack.h"

StrongAttack::StrongAttack() :
	tr_(nullptr), w_(60), h_(30), cooldown_(500), time_(sdlutils().currRealTime()), attackSound_(sdlutils().soundEffects().at("strong_attack")), hitSound_(sdlutils().soundEffects().at("hit")) {
}

void StrongAttack::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void StrongAttack::update() {
	if (ih().mouseButtonEvent()) {
		if (ih().getMouseButtonState(ih().RIGHT) == 1 && sdlutils().currRealTime() > time_ + cooldown_) {

			auto size = tr_->getW();
			auto& pos = tr_->getPos();


			SDL_Rect rect;
			rect.w = w_;
			rect.h = h_;

			auto flip = tr_->getFlip();

			//Si esta flipeado...
			if (flip)
				//Le damos la vuelta al rect
				rect.x = pos.getX() - size / 2;
			else
				rect.x = pos.getX() + size / 2;

			rect.y = pos.getY();


			//Comprobamos si colisiona con alguno de los enemigos que tiene delante

			//Si se colisiona..
			if (CheckCollisions(rect))
				//Suena el hit y le pega
				hitSound_.play();
			//Si no colisiona..
			else
				//Suena el attackSound
				attackSound_.play();

			//this.anims.play(pegarse)

			time_ = sdlutils().currRealTime();
		}
	}
}

bool StrongAttack::CheckCollisions(const SDL_Rect& rectPlayer) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEnteties();

	for (Entity* e : ents) {
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
			if (SDL_HasIntersection(&rectPlayer, &rectEnemy)) {
				canHit = true;
				//Llamamos a un componente del enemy(Vida.getDa�o(dmg) y le restas el da�o
				//ents[i]->getComponent<Life>().getDmg(dmg_);
			}
		}
	}
	return canHit;
}