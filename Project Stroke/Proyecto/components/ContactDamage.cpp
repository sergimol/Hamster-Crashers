#include "EnemyAttack.h"
#include "Stroke.h"
#include "Combos.h"
#include "Stun.h"
#include "Knockback.h"
#include "ControlHandler.h"
#include "StrongAttack.h"
#include "ContactDamage.h"

ContactDamage::ContactDamage(int danyo) :
	tr_(nullptr), attRect_(), DEBUG_isAttacking_(false),
	attackSound_(sdlutils().soundEffects().at("light_attack")), hitSound_(sdlutils().soundEffects().at("hit")), dmg_(danyo) {}

void ContactDamage::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void ContactDamage::update() {
	//Deja de mostrar el collider
	/*
	if (sdlutils().currRealTime() > time_ / 1.5) {
		DEBUG_isAttacking_ = false;
	}
	*/
	updateRect();
}

void ContactDamage::updateRect() {

	cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
	auto sizeW = tr_->getW();
	auto sizeH = tr_->getH();
	auto& pos = tr_->getPos();

	//crear el rectangulo que va a hacer el contact damage

	attRect_.w = sizeW;
	attRect_.h = sizeH;
	attRect_.x = pos.getX() - cam.x;
	attRect_.y = pos.getY() - cam.y;

	//Comprobamos si colisiona con alguno de los players

	//Si se colisiona..
	if (CheckCollisions(attRect_, true))
		//Suena el hit y le pega
		hitSound_.play();
	//Si no colisiona..
	else
		//NO  NO QUIERO Suena el attackSound
		//attackSound_.play();

	//this.anims.play(pegarse)

		DEBUG_isAttacking_ = true;
	time_ = sdlutils().currRealTime();

}

bool ContactDamage::CheckCollisions(const SDL_Rect& enemyRect, bool finCombo) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getPlayers();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un player...

			//Cogemos el transform del player
		auto eTR = ents[i]->getComponent<Transform>();

		//Creamos su Rect 
		SDL_Rect allyRect;
		allyRect.h = eTR->getH();
		allyRect.w = eTR->getW();
		allyRect.x = eTR->getPos().getX() - cam.x;
		allyRect.y = eTR->getPos().getY() - cam.y;


		//Y comprobamos si colisiona
		//es can attacks porque coninciden lso estados
		//TODO si se cambian lso estados DEAD STUNNED INFARTED hayq eu cambiar este booleano por otro ams combeniente
		if (ents[i]->getComponent<HamsterStateMachine>()->canAttack() && SDL_HasIntersection(&enemyRect, &allyRect)) {
			//TODO no voy a definir una entidad ahora
			//int dmg = entity_->getComponent<EntityAttribs>()->getDmg();
			//if (finCombo) {
			//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
			//	//Empujar y stun al aliado
			//}
			canHit = true;
			//Le restamos la vida al aliado
			ents[i]->getComponent<EntityAttribs>()->recieveDmg(dmg_);

			auto& hamStateM = ents[i]->getComponent<HamsterStateMachine>()->getState();

			if (hamStateM != HamStates::DEAD && hamStateM != HamStates::INFARCTED) {
				//Si tiene stun, se aplica
				Stun* stun = ents[i]->getComponent<Stun>();
				if (stun != nullptr && stun->isActive()) {

					//Si no estaba aturdido ya
					if (hamStateM != HamStates::STUNNED) {
						//Aturdimos al hamster
						hamStateM = HamStates::STUNNED;

						//Animaci�n de stun
						//anim_->play(sdlutils().anims().at("sardinilla_stun"));

						//Desactivamos control de movimiento 
						ControlHandler* ctrl = ents[i]->getComponent<ControlHandler>();
						if (ctrl != nullptr)
							ctrl->setActive(false);

						//Desactivamos componentes de ataque
						StrongAttack* strAtt = ents[i]->getComponent<StrongAttack>();
						if (strAtt != nullptr)
							strAtt->setActive(false);

						LightAttack* lghtAtt = ents[i]->getComponent<LightAttack>();
						if (lghtAtt != nullptr)
							lghtAtt->setActive(false);

					}
					//Reiniciamos tiempo de stun
					stun->restartStunTime();
				}
			}
			//Si tiene Knockback, se aplica
			Knockback* hamKnockback = ents[i]->getComponent<Knockback>();
			if (hamKnockback != nullptr && hamKnockback->isActive()) {
				//Damos la vuelta si es atacado por detras

				//DEPENDE DE LA posicion de X y el width al medio
				attRect_.x;
				attRect_.w;
				allyRect.w;
				allyRect.x;

				//MIRADNOA AL DERECHA ES !flip, izquierda es flip, por default quuiero que sea !flip
				auto& hamFlip = eTR->getFlip();
				if (attRect_.x + (attRect_.w / 2) > allyRect.x + (allyRect.w / 2)) //esta a ala izquierda entonces !flip
					hamFlip = false;
				else
					hamFlip = true;

				hamKnockback->knockback();
			}
		}

	}
	return canHit;
}

void ContactDamage::render() {
	if (DEBUG_isAttacking_) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 170, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
	}
}
