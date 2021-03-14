#include "Camera.h"

Camera::Camera() :
	tr_(nullptr), w_(60), h_(30), cooldown_(350), time_(sdlutils().currRealTime()),
	attackSound_(sdlutils().soundEffects().at("light_attack")), hitSound_(sdlutils().soundEffects().at("hit")) {}

void Camera::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Camera::update() {

}

bool Camera::CheckCollisions(const SDL_Rect& rectPlayer) {
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
				//Le restamos la vida al enemigo
				e->getComponent<Life>()->recieveDmg(dmg_);
			}
		}
	}
	return canHit;
}