#include "LightAttack.h"
#include "Stroke.h"
#include "Combos.h"

LightAttack::LightAttack() :
	tr_(nullptr), w_(60), h_(30), cooldown_(350), time_(sdlutils().currRealTime()),
	attackSound_(sdlutils().soundEffects().at("light_attack")), hitSound_(sdlutils().soundEffects().at("hit")) {}

void LightAttack::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);
}

void LightAttack::update() {
	if (ih().mouseButtonEvent()) {
		auto state = hms_->getState();
		if (!(state == HamStates::DEAD || state == HamStates::STUNNED || state == HamStates::INFARCTED) && ih().getMouseButtonState(ih().LEFT) == 1 && sdlutils().currRealTime() > time_ + cooldown_) {

			auto size = tr_->getW();
			auto& pos = tr_->getPos();
			auto range = entity_->getComponent<EntityAttribs>()->getAttackRange(); // Cogemos el rango del ataque
			state = HamStates::LIGHTATTACK;

			SDL_Rect rect;
			rect.w = w_ + w_ * range;
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
			//A�adimos a los combos
			bool finCombo = entity_->getComponent<Combos>()->checkCombo(0);

			//Si se colisiona..
			if (CheckCollisions(rect, finCombo))
				//Suena el hit y le pega
				hitSound_.play();
			//Si no colisiona..
			else
				//Suena el attackSound
				attackSound_.play();

			//this.anims.play(pegarse)

			time_ = sdlutils().currRealTime();
			entity_->getComponent<Stroke>()->increaseChance(5, this);
		}
		else if (sdlutils().currRealTime() > time_ + cooldown_ / 2) {
			state = HamStates::IDLE;
		}
	}
}

bool LightAttack::CheckCollisions(const SDL_Rect& rectPlayer, bool finCombo) {
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
				int dmg = entity_->getComponent<EntityAttribs>()->getDmg();
				if (finCombo) {
					if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
					//Empujar y stunn al enemigo 
				}
				canHit = true;
				//Le restamos la vida al enemigo
				e->getComponent<EntityAttribs>()->recieveDmg(dmg);
			}
		}
	}
	return canHit;
}