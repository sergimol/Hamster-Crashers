#include "Roll.h"
#include "Movement.h"
#include "Animator.h"
#include "Stroke.h"


//Roll::Roll() : Ability() {
//
//};
void Roll::init() {
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

Roll::~Roll() {
	//me follo a tu madre
}

float Roll::lerp(float a, float b, float f){
	return (a + f * (b - a));
}

void Roll::action() 
{
	if (entity_->getComponent<Movement>()->isActive()){
		entity_->getComponent<Movement>()->setActive(false);
		
		rolling = true;
		
		dir_ = entity_->getComponent<Movement>()->getLastDir();
		
		if (dir_ == Vector2D(0, 0)) {
			if(tr_->getFlip())
				tr_->getVel().setX(-iniAccel);
			else
				tr_->getVel().setX(iniAccel);
		}
		else {
			tr_->getVel() = dir_ * iniAccel;
		}
		anim_->play(sdlutils().anims().at("sardinilla_ability"));
	}
}

void Roll::updateKeymap(KEYS x, bool is) {
	if (x != SPACE)
		keymap.at(x) = is;
	else if (!keymap.at(SPACE)) {
		keymap.at(SPACE) = true;
		entity_->getComponent<Stroke>()->increaseChance(2, this);
	}
}

void Roll::update() {

	Ability::update();
	auto& state = hms_->getState();

	if (rolling)
	{
		auto& vel = tr_->getVel();
		auto& z = tr_->getZ();
		auto& velZ = tr_->getVelZ();

		if (!keymap.at(SPACE) && ih().isKeyDown(SDLK_SPACE)) {
			keymap.at(SPACE) = true;
			entity_->getComponent<Stroke>()->increaseChance(2, this);
		}

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

		if (!keymap.at(UP) && !keymap.at(DOWN) && !keymap.at(LEFT) && !keymap.at(RIGHT)) {		//Deceleracion
			//vel.setX(lerp(vel.getX(), 0, 0.25));
			//vel.setY(lerp(vel.getY(), 0, 0.25));

			//ANIMACION DE IDLE
			if (state != HamStates::IDLE)
				anim_->play(sdlutils().anims().at("sardinilla_ability"));
			if (state != HamStates::JUMPING) 
				state = HamStates::IDLE;

		}
		else if (hms_->canMove()) {		//Aceleracion
			vel.setX(lerp(goalVel_.getX(), vel.getX(), 0.95));
			vel.setY(lerp(goalVel_.getY(), vel.getY(), 0.95));

			//ANIMACION DE MOVIMIENTO
			if (state != HamStates::MOVING)
				anim_->play(sdlutils().anims().at("sardinilla_ability"));
			if (state != HamStates::JUMPING) 
				state = HamStates::MOVING;

		}


		if (hms_->canJump() && keymap.at(SPACE)) {		//Inicio del salto
			velZ = jump_;
			state = HamStates::JUMPING;
			timer = sdlutils().currRealTime();
		}

		if (z > 0 && sdlutils().currRealTime() > timer + jumpTimer_) {			//Aceleracion del salto afectado por gravedad
			velZ -= gravity_;
			timer = sdlutils().currRealTime();
		}

		else if (z < 0) {			//Final del salto	!!!!!!!!!(0 SE SUSTITUIRA POR LA Z DEL MAPA)!!!!!!!!
			keymap.at(SPACE) = false;
			velZ = 0;
			z = 0;
			state = HamStates::IDLE;
			timer = sdlutils().currRealTime();
		}

		//Si se colisiona..
		if (checkCollisions())
			//Suena el hit y le pega
			hitSound_.play();
	}
	//else if(!entity_->getComponent<Movement>()->isActive())
	//{
	//	/*auto& vel = tr_->getVel();
	//	vel = Vector2D();*/
	//	entity_->getComponent<Movement>()->setActive(true);
	//}
}

bool Roll::checkCollisions()
{
	//Comprueba si has golpeado
	bool hit = false;

	//Cogemos todas las entidades
	auto& ents = entity_->getMngr()->getEntities();

	//Recorremos la lista de componentes
	for (int i = 0; i < ents.size(); ++i)
	{
		//Si es un enemigo
		if (ents[i]->hasGroup<Enemy>())
		{
			//Cogemos el transform del enemigo
			auto eTr = ents[i]->getComponent<Transform>();
			//Creamos su "collider"
			SDL_Rect rectEnemy = build_sdlrect(eTr->getPos(), eTr->getW(), eTr->getH());

			//Cogemos el transform del jugador
			auto pTr = entity_->getComponent<Transform>();
			//Creamos su "collider"
			SDL_Rect rectPlayer = build_sdlrect(pTr->getPos(), pTr->getW(), pTr->getH());

			//Comprobamos si hay colision
			if (SDL_HasIntersection(&rectPlayer, &rectEnemy))
			{
				//he puesto que le matas de una 
				//creo que lo suyo seria stunnearlo y quitar la mitad de la vida o asi
				int dmg = ents[i]->getComponent<EntityAttribs>()->getMaxLife();
				if (ents[i]->getComponent<EntityAttribs>()->getLife() > 0)
				{
					ents[i]->getComponent<EntityAttribs>()->recieveDmg(dmg);
					hit = true;
				}
			}

		}
	}

	return hit;
}

void Roll::deActivate() {
	entity_->getComponent<Movement>()->setActive(true);
	rolling = false;
	tr_->getVel() = Vector2D(0,0);
}