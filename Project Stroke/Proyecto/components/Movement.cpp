#include "Movement.h"
#include "Stroke.h"
#include <cmath>
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

void Movement:: init() {
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
	if (x != SPACE)
	keymap.at(x) = is;
	else if (!keymap.at(SPACE)) {
		keymap.at(SPACE) = true;
		entity_->getComponent<Stroke>()->increaseChance(2, false);
	}
}
void Movement:: update() {

	auto& vel = tr_->getVel();
	auto& state = hms_->getState();
	auto& z = tr_->getZ();
	auto& velZ = tr_->getVelZ();

	Vector2D dir = Vector2D(0, 0);

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

	if (!keymap.at(UP) && !keymap.at(DOWN) && !keymap.at(LEFT) && !keymap.at(RIGHT)) {		//Deceleracion
		vel.setX(lerp(vel.getX(), 0, 0.25));
		vel.setY(lerp(vel.getY(), 0, 0.25));

	//std:cout << "estoy decelerando supuestamente porque no decelero bien? who knows \n";

		//ANIMACION DE IDLE
		if (state != HamStates::IDLE && state != HamStates::INFARCTED)
			anim_->play(sdlutils().anims().at("sardinilla_idle"));
		if (state != HamStates::JUMPING && state != HamStates::INFARCTED && state != HamStates::STUNNED) state = HamStates::IDLE;

	}
	else if (hms_->canMove()) {		//Aceleracion
		vel.setX(lerp(goalVel_.getX(), vel.getX(), 0.9));
		vel.setY(lerp(goalVel_.getY(), vel.getY(), 0.9));


		//cout << "Up: " << keymap.at(UP) << " DOWN: " << keymap.at(DOWN) << " LEFT: " << keymap.at(LEFT) << " RIGHT: " << keymap.at(RIGHT)
		//	<< " DIR: " << dir.getX() << " " << dir.getY() << "\n";

		//ANIMACION DE MOVIMIENTO
		if (state != HamStates::MOVING && state != HamStates::INFARCTED)
			anim_->play(sdlutils().anims().at("sardinilla_move"));
		if (state != HamStates::JUMPING && state != HamStates::INFARCTED && state != HamStates::STUNNED) state = HamStates::MOVING;

	}
	else  {
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

	if (hms_->canJump() && keymap.at(SPACE)) {		//Inicio del salto
		velZ = jump_;
		state = HamStates::JUMPING;
		//timer = sdlutils().currRealTime();
	}

	//if (z > 0 && sdlutils().currRealTime() > timer + jumpTimer_) {			//Aceleracion del salto afectado por gravedad
	//	 -= gravity_;
	//	timer = sdlutils().currRealTime();
	//}

	if (z <= 0 && velZ < 0) {			//Final del salto	!!!!!!!!!(0 SE SUSTITUIRA POR LA Z DEL MAPA)!!!!!!!!
		
		keymap.at(SPACE) = false;
		//velZ = 0;
		//z = 0;
		if(state != HamStates::INFARCTED)
			state = HamStates::IDLE;
		//timer = sdlutils().currRealTime();
	}
}

float Movement::lerp(float a, float b, float f)
{
	return (a + f * (b - a));
}

void Movement::onEnable(){
	if(tr_->getVel() == Vector2D(0,0))
		anim_->play(sdlutils().anims().at("sardinilla_idle")); // Idle
	else
		anim_->play(sdlutils().anims().at("sardinilla_move")); //Movimiento
}

void Movement::onDisable()
{
	auto& vel = tr_->getVel();
	vel = Vector2D();
}