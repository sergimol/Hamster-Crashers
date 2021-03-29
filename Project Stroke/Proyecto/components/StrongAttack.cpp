#include "StrongAttack.h"
#include "Stroke.h"
#include "Combos.h"

StrongAttack::StrongAttack() :
	tr_(nullptr), w_(60), h_(30), cooldown_(500), time_(sdlutils().currRealTime()), attRect_(),
	attackSound_(sdlutils().soundEffects().at("strong_attack")), hitSound_(sdlutils().soundEffects().at("hit")) {
}

void StrongAttack::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);
}

void StrongAttack::update() {
	if (ih().mouseButtonEvent()) {
		auto state = hms_->getState();
		if (!(state == HamStates::DEAD || state == HamStates::STUNNED || state == HamStates::INFARCTED) && ih().getMouseButtonState(ih().RIGHT) == 1 && sdlutils().currRealTime() > time_ + cooldown_) {

			auto size = tr_->getW();
			auto& pos = tr_->getPos();
			auto range = entity_->getComponent<EntityAttribs>()->getAttackRange(); // Cogemos el rango del ataque
			state = HamStates::STRONGATTACK;


			/*attRect_ = new SDL_Rect;*/
			attRect_.w = w_ + w_ * range;
			attRect_.h = h_;

			auto flip = tr_->getFlip();

			//Si esta flipeado...
			if (flip)
				//Le damos la vuelta al rect
				attRect_.x = pos.getX() - size / 2 - Game::camera_.x;
			else
				attRect_.x = pos.getX() + size / 2 - Game::camera_.x;

			attRect_.y = pos.getY() - Game::camera_.y;

			//Comprobamos si colisiona con alguno de los enemigos que tiene delante

			//A�adimos a los combos
			bool finCombo = entity_->getComponent<Combos>()->checkCombo(1);

			//Si se colisiona..
			if (CheckCollisions(attRect_, finCombo))
				//Suena el hit y le pega
				hitSound_.play();
			//Si no colisiona..
			else
				//Suena el attackSound
				attackSound_.play();

			//this.anims.play(pegarse)

			time_ = sdlutils().currRealTime();
			entity_->getComponent<Stroke>()->increaseChance(10, this);
		}
		else if (sdlutils().currRealTime() > time_ + cooldown_ / 2) {
			state = HamStates::IDLE;
		}
	}
}

bool StrongAttack::CheckCollisions(const SDL_Rect& rectPlayer, bool finCombo) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEnteties();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un enemigo...
		if (ents[i]->hasGroup<Enemy>()) {
			//Cogemos el transform del enemigo
			auto eTR = ents[i]->getComponent<Transform>();

			//Creamos su Rect
			SDL_Rect rectEnemy;
			rectEnemy.h = eTR->getH();
			rectEnemy.w = eTR->getW();
			rectEnemy.x = eTR->getPos().getX() - Game::camera_.x;
			rectEnemy.y = eTR->getPos().getY() - Game::camera_.y;

			//Y comprobamos si colisiona
			if (SDL_HasIntersection(&rectPlayer, &rectEnemy)) {
				int dmg = entity_->getComponent<EntityAttribs>()->getDmg();
				if (finCombo) {
					if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.02); //Aumentar probabilidad critico
					//Empujar y stunn al enemigo 
				}
				canHit = true;
				//Le restamos la vida al enemigo
				ents[i]->getComponent<EntityAttribs>()->recieveDmg(dmg * 1.5);
			}
		}
	}
	return canHit;
}

void StrongAttack::render() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 0, 0, 255);

	SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
}