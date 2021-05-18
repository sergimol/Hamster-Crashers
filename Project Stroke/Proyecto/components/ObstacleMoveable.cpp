﻿#include "ObstacleMoveable.h"
#include "Animator.h"
#include "SoundManager.h"
#include "../ecs/Manager.h"
#include "Dying.h"
#include "Item.h"
#include "Image.h"
#include "ContactDamage.h"
#include "LifeTime.h"

void ObstacleMoveable::init() {
	
	gamestate = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(gamestate != nullptr);
	
	
	lastTime_ = sdlutils().currRealTime();
}

void ObstacleMoveable::update()
{
	if (gamestate->getState() == GameStates::RUNNING) {

		time_ = sdlutils().currRealTime() - lastTime_;

		if (time_ >= spawnTime_ * spawns_) {

			//std::cout << "sale un chohecito cada 5 segundos \n";
			//se espawnea un coche
			
			//el coche funciona de manera independiente tiene un lifeTime que lo desactivara a si mismo
			//pero tmb podemos destruirlo desde aca de ser necesario

			auto coche = entity_->getMngr()->addEntity();
			//el transform, aun no se que valores darle
			coche->addComponent<Transform>(Vector2D(x_,y_), Vector2D(vel, 0), 255.0, 255.0,
				0, 1, 1);

			coche->addComponent<Animator>(
				&sdlutils().images().at("soldier1Sheet"),
				86,
				86,
				3,
				3,
				220,
				Vector2D(0, 0),
				3
				);

			//coche->addComponent<Image>(&sdlutils().images().at("catSmoking")); //por testing sin animacion
			coche->addComponent<ContactDamage>(10, 10, true, true);
			//la nueva componente, muerte en tiempo
			coche->addComponent<LifeTime>(lifeTime_);
			obstacle = coche;

			spawns_++;
		}

	}
	else lastTime_ = sdlutils().currRealTime() - time_;

}

void ObstacleMoveable::render()
{
	SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
	auto tr_ = entity_->getComponent<Transform>();

	Vector2D renderPos;
	if (vel > 0) 
		renderPos = Vector2D(0, y_ - cam.y);
	else 
		renderPos = Vector2D(cam.w - (warningTx->width()/2), y_ - cam.y);
	SDL_Rect dest = build_sdlrect(renderPos, tr_->getW(), tr_->getH());
	
	if (debug) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &dest);
	}

	//calcualr el alpha del warning segun el valor time_ y el numero de spawns

	if (time_ >= ((spawnTime_ * spawns_) - warningTime_)) {
		//se peude comenzar a caluclar el aplha
		float aux = (time_ - ((spawnTime_ * spawns_) - warningTime_));

		warningTx->setAlpha(255.0 * abs(sin(aux /warningTimeFlickering_)));

		std::cout << sin(aux / warningTimeFlickering_) << "\n";
	}
	else {

		warningTx->setAlpha(0.0);
	}

	//std::cout << renderPos.getX() << " " << renderPos.getY() << "\n";

	warningTx->render(dest, tr_->getRot());
}

ObstacleMoveable::~ObstacleMoveable() {
	
}
