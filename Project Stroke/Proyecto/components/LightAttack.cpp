#include "LightAttack.h"
#include "Stroke.h"
#include "Combos.h"

LightAttack::LightAttack() :
	tr_(nullptr), cooldown_(350), time_(sdlutils().currRealTime()), attRect_(), DEBUG_isAttacking_(false),
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

			auto sizeW = tr_->getW();
			auto sizeH = tr_->getH();
			auto& pos = tr_->getPos();
			auto range = entity_->getComponent<EntityAttribs>()->getAttackRange(); // Cogemos el rango del ataque


			attRect_.w = sizeW / 2 + sizeW / 2 * range;
			attRect_.h = sizeH / 2 + sizeH / 2 * range;

			auto flip = tr_->getFlip();

			//Si esta flipeado...
			if (flip)
				//Le damos la vuelta al rect
				attRect_.x = pos.getX() - attRect_.w + sizeW / 4 - Game::camera_.x; //esto no funciona bien para el resto de entidades solo con sardinilla supongo, mas tarde investigamos
			else
				attRect_.x = pos.getX() + sizeW - sizeW / 4 - Game::camera_.x;

			attRect_.y = pos.getY() + sizeH / 4 - Game::camera_.y;

			//Comprobamos si colisiona con alguno de los enemigos que tiene delante
			//A�adimos a los combos
			bool finCombo = entity_->getComponent<Combos>()->checkCombo(0);

			//Si se colisiona..
			if (CheckCollisions(attRect_, finCombo))
				//Suena el hit y le pega
				hitSound_.play();
			//Si no colisiona..
			else
				//Suena el attackSound
				attackSound_.play();

			//this.anims.play(pegarse)

			DEBUG_isAttacking_ = true;
			time_ = sdlutils().currRealTime();
			entity_->getComponent<Stroke>()->increaseChance(5, this);
		}
		else if (sdlutils().currRealTime() > time_ + cooldown_ / 2) {
			state = HamStates::IDLE;
		}
	}
	//Deja de mostrar el collider
	if (sdlutils().currRealTime() > time_ + cooldown_ / 1.5) {
		DEBUG_isAttacking_ = false;
	}
}

bool LightAttack::CheckCollisions(const SDL_Rect& rectPlayer, bool finCombo) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEntities();

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
					if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
					//Empujar y stunn al enemigo 
				}
				canHit = true;
				//Le restamos la vida al enemigo
				ents[i]->getComponent<EntityAttribs>()->recieveDmg(dmg);
			}
		}
	}
	return canHit;
}

void LightAttack::render() {
	if (DEBUG_isAttacking_) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 212, 255, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
	}
}
