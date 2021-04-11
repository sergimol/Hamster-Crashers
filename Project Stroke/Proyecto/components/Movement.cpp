#include "Movement.h"
#include "Stroke.h"
#include "Combos.h"
#include "AnimHamsterStateMachine.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

//Para comprobar las colisiones
#include "MapMngr.h"

void Movement::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);

	anim_ = entity_->getComponent<Animator>();
	assert(anim_ != nullptr);

	speed_ = entity_->getComponent<EntityAttribs>()->getVel();
	assert(speed_ != Vector2D());

	keymap.insert({ UP, false });
	keymap.insert({ DOWN, false });
	keymap.insert({ RIGHT, false });
	keymap.insert({ LEFT, false });
	keymap.insert({ SPACE, false });

}

void Movement::updateKeymap(KEYS x, bool is) {
	if (x != SPACE || !keymap.at(SPACE))
		keymap.at(x) = is;
}

void Movement::update() {

	auto& vel = tr_->getVel();
	auto& state = hms_->getState();
	auto& z = tr_->getZ();
	auto& velZ = tr_->getVelZ();

	Vector2D dir = Vector2D(0, 0);

	//Cogemos el mapa para comprobar luego las colisiones
	auto map = entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>();


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
	}

	lastDir_ = dir; //Recogemos siempre la última dirección para quien la necesite

	//Cojo el rect del player y le sumo la supuesta siguiente posicion
	SDL_Rect rectPlayer{ tr_->getPos().getX() + goalVel_.getX(), tr_->getPos().getY() + goalVel_.getY(), tr_->getW(),tr_->getH() };

	//Si me voy a chocar con una pared...
	if (map->intersectWall(rectPlayer)) {
		//Dejo de moverme
		vel.setX(0);
		vel.setY(0);

		//Y me quedo quieto
		entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::MOVE, false);
		entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::IDLE, true);
	}
	//Si no me voy a chocar...
	else {
		if (!keymap.at(UP) && !keymap.at(DOWN) && !keymap.at(LEFT) && !keymap.at(RIGHT)) {		//Deceleracion
			vel.setX(lerp(vel.getX(), 0, 0.25));
			vel.setY(lerp(vel.getY(), 0, 0.25));
			//std:cout << "estoy decelerando supuestamente porque no decelero bien? who knows \n";

			//ANIMACION DE IDLE
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::MOVE, false);
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::IDLE, true);
		}
		else if (hms_->canMove()) {		//Aceleracion

			vel.setX(lerp(goalVel_.getX(), vel.getX(), 0.9));
			vel.setY(lerp(goalVel_.getY(), vel.getY(), 0.9));


			//cout << "Up: " << keymap.at(UP) << " DOWN: " << keymap.at(DOWN) << " LEFT: " << keymap.at(LEFT) << " RIGHT: " << keymap.at(RIGHT)
			//	<< " DIR: " << dir.getX() << " " << dir.getY() << "\n";

			//ANIMACION DE MOVIMIENTO
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::MOVE, true);
			entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::IDLE, false);
		}
		else {
			cout << "Estado : " << hms_->currentstate() << "\n";
			//porque esta kaput el bixo

			vel.setX(lerp(vel.getX(), 0, 0.25));
			vel.setY(lerp(vel.getY(), 0, 0.25));

			//ANIMACION DE MORIRSE
			//if (state != HamStates::DEAD)
			//	;// anim_->play(sdlutils().anims().at("sardinilla_morirse"));
			//if (state != HamStates::INFARCTED)
				// anim_->play(sdlutils().anims().at("sardinilla_chungo"));
		}
	}

	//if (z > 0 && sdlutils().currRealTime() > timer + jumpTimer_) {			//Aceleracion del salto afectado por gravedad
	//	 -= gravity_;
	//	timer = sdlutils().currRealTime();
	//}

	// 0 se debería sustituir por la z mínima del mapa
	if (z <= 0) {
		// Inicio del salto
		if (keymap.at(SPACE)) {
			entity_->getComponent<Combos>()->checkCombo(2);
			entity_->getComponent<Stroke>()->increaseChance(2, false);
			velZ = jump_;
			keymap.at(SPACE) = false;
		}
		// Fin del salto
		if (velZ < 0) {
			entity_->getComponent<Combos>()->popUntilEmpty();
			/*keymap.at(SPACE) = false;*/
		}
	}
}

float Movement::lerp(float a, float b, float f)
{
	return (a + f * (b - a));
}

void Movement::onEnable() {
	if (tr_->getVel() == Vector2D(0, 0))
		anim_->play(sdlutils().anims().at("sardinilla_idle")); // Idle
	else
		anim_->play(sdlutils().anims().at("sardinilla_move")); //Movimiento
}

void Movement::onDisable()
{
	auto& vel = tr_->getVel();
	vel = Vector2D();
}