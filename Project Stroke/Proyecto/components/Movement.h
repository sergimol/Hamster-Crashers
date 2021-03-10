#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>
#include <cmath>

#include "Transform.h"



class Movement : public Component {
public:
	Movement() :
		tr_(nullptr), speed_(7.0f, 3.5f), goalVel_(0,0), dt_(0.0f), time_(sdlutils().currRealTime()){
	}

	virtual ~Movement() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);

		keymap.insert({ UP, false });
		keymap.insert({ DOWN, false });
		keymap.insert({ RIGHT, false });
		keymap.insert({ LEFT, false });
	}
	
	void update() override {

		dt_ = (sdlutils().currRealTime() - time_) / 1000;
		time_ = sdlutils().currRealTime();
		
		auto& vel = tr_->getVel();
		if (ih().keyDownEvent() || ih().keyUpEvent()) { //el rebote de teclao esta aqui en medio ajajajaja //mejor el estado del teclado no se jaja
			
			
			if (ih().isKeyDown(SDL_SCANCODE_UP))
				keymap.at(UP) = true;
			else if(ih().isKeyUp(SDL_SCANCODE_UP))
				keymap.at(UP) = false;

			if (ih().isKeyDown(SDL_SCANCODE_DOWN))
				keymap.at(DOWN) = true;
			else if (ih().isKeyUp(SDL_SCANCODE_DOWN))
				keymap.at(DOWN) = false;

			if (ih().isKeyDown(SDL_SCANCODE_RIGHT))
				keymap.at(RIGHT) = true;
			else if(ih().isKeyUp(SDL_SCANCODE_RIGHT))
				keymap.at(RIGHT) = false;

			if (ih().isKeyDown(SDL_SCANCODE_LEFT))
				keymap.at(LEFT) = true;
			else if (ih().isKeyUp(SDL_SCANCODE_LEFT))
				keymap.at(LEFT) = false;

			Vector2D dir = Vector2D(0,0);

			if (keymap.at(UP)) {
				dir.setY(-1.0f);
			}
			else if (keymap.at(DOWN)) {
				dir.setY(1.0f);
			}

			if (keymap.at(RIGHT)) {
				dir.setX(1.0f);
				tr_->getFlip() = false;
			}
			else if (keymap.at(LEFT)) {
				dir.setX(-1.0f);
				tr_->getFlip() = true;
			}

			if (dir.magnitude() != 0) {
				dir = dir.normalize();

				goalVel_ = Vector2D(dir.getX() * speed_.getX(), dir.getY() * speed_.getY());

				//vel = goalVel_;

				
			}
			else {
				//
				//se poenn teclas a true;
				std::cout << "hay un cero como?, si ocurre este dato no nos interesa, interpone en mitad de la matematica" << std::endl;
			}
			//hasta aqui todo bien,
			//ahora a ver como se hace el lerp,
			//el lerp no es darle la vuelta a la velocidad
			//si no una aceleracion y un freno,
			//esto quiere decir que
			//a la velocidad le vamos a sumar o restar un valor hasta llegar al "vel_maxima_"
			//cual es ese valor X?¿
			//el lerp
			//el lerp tine dos valores
			
			//aceleracion -> dependera de la direccion
			//friccion | Freno ->se le restara siempre en direccion contraria a la que se este moviemdo la velocidad

			// (se la friccion es pareja a la velocidad que lleva como podemos decir que ha parado comletamente?¿)


		}

		if (!keymap.at(UP) && !keymap.at(DOWN) && !keymap.at(LEFT) && !keymap.at(RIGHT)) { //esto no furrula porque calro el imput es antes
			//ocurre un error y es que cada dos lecturas de eventos pasa una vez por aqui, esto tmb es malo ay que se supone 
			vel.setX(lerp(vel.getX(), 0, /*dt_ **/ 0.1));
			vel.setY(lerp(vel.getY(), 0,  /*dt_ **/ 0.1));
			std::cout << "a" << std::endl;
		}
		else {
			vel.setX(lerp(goalVel_.getX(), vel.getX(), /*dt_ **/ 0.9));
			vel.setY(lerp(goalVel_.getY(), vel.getY(), /*dt_ **/ 0.9));

			std::cout << tr_->getVel() << std::endl;
		}
		 
		 
	}

	/*
	float lerp(float goal, float current, float dt) {
		float diff = goal - current;

		if (diff > dt)
			return current + dt;
		if (diff < dt)
			return current - dt;

		return goal;
	}
	*/
	
	float lerp(float a, float b, float f)
	{
		return (a + f*(b-a)); //solucionao \(^x^)/
	}
	

private:
	Transform* tr_;
	Vector2D speed_, goalVel_;
	float dt_, time_;
	const enum KEYS {UP, DOWN, LEFT, RIGHT};
	std::map<KEYS, bool> keymap;
};

