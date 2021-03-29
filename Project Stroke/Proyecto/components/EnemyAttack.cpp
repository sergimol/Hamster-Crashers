#include "EnemyAttack.h"
#include "Stroke.h"
#include "Combos.h"

EnemyAttack::EnemyAttack() :
	tr_(nullptr), cooldown_(1100), time_(sdlutils().currRealTime()), attRect_(),
	attackSound_(sdlutils().soundEffects().at("light_attack")), hitSound_(sdlutils().soundEffects().at("hit")) {}

void EnemyAttack::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void EnemyAttack::update() {
}

void EnemyAttack::LaunchAttack() {
	if (sdlutils().currRealTime() > time_ + cooldown_) {

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

		//Si se colisiona..
		if (CheckCollisions(attRect_, true))
			//Suena el hit y le pega
			hitSound_.play();
		//Si no colisiona..
		else
			//Suena el attackSound
			attackSound_.play();

		//this.anims.play(pegarse)

		time_ = sdlutils().currRealTime();
	}
	//else if (sdlutils().currRealTime() > time_ + cooldown_ / 2) {
	//}
}

bool EnemyAttack::CheckCollisions(const SDL_Rect& enemyRect, bool finCombo) {
	bool canHit = false;

	//Cogemos todas las entidades del juego
	auto& ents = entity_->getMngr()->getEntities();

	for (int i = 0; i < ents.size(); ++i) {
		//Si la entidad es un enemigo...
		if (ents[i]->hasGroup<Ally>()) {
			//Cogemos el transform del enemigo
			auto eTR = ents[i]->getComponent<Transform>();

			//Creamos su Rect
			SDL_Rect allyRect;
			allyRect.h = eTR->getH();
			allyRect.w = eTR->getW();
			allyRect.x = eTR->getPos().getX() - Game::camera_.x;
			allyRect.y = eTR->getPos().getY() - Game::camera_.y;


			//Y comprobamos si colisiona
			if (SDL_HasIntersection(&enemyRect, &allyRect)) {
				int dmg = entity_->getComponent<EntityAttribs>()->getDmg();
				//if (finCombo) {
				//	if (!canHit) entity_->getComponent<EntityAttribs>()->addCritProbability(0.01); //Aumentar probabilidad critico
				//	//Empujar y stun al aliado
				//}
				canHit = true;
				//Le restamos la vida al aliado
				ents[i]->getComponent<EntityAttribs>()->recieveDmg(dmg);
			}
		}
	}
	return canHit;
}

void EnemyAttack::render() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 170, 0, 255);

	SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
}