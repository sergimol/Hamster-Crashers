#include "StrongAttack.h"
#include "Stroke.h"
#include "Combos.h"
#include "FollowPlayer.h"
#include "Knockback.h"
#include "EnemyStun.h"

StrongAttack::StrongAttack() :
	hms_(nullptr), tr_(nullptr), cooldown_(500), time_(sdlutils().currRealTime()), attRect_(), DEBUG_isAttacking_(false),
	attackSound_(sdlutils().soundEffects().at("strong_attack")), hitSound_(sdlutils().soundEffects().at("hit")) {
}

void StrongAttack::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	hms_ = entity_->getComponent<HamsterStateMachine>();
	assert(hms_ != nullptr);

	player_ = entity_->getComponent<EntityAttribs>()->getNumber();
	cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
}

void StrongAttack::update() {
	if ((ih().playerHasController(player_) && ih().isButtonDown(player_, SDL_CONTROLLER_BUTTON_Y)) || ih().mouseButtonEvent()) {
	}
	//Deja de mostrar el collider
	if (sdlutils().currRealTime() > time_ + cooldown_ / 1.5) {
		DEBUG_isAttacking_ = false;
	}
}

bool StrongAttack::CheckCollisions(const SDL_Rect& rectPlayer, bool finCombo) {
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
			rectEnemy.x = eTR->getPos().getX() - cam.x;
			rectEnemy.y = eTR->getPos().getY() - cam.y;

			//Y comprobamos si colisiona
			if (SDL_HasIntersection(&rectPlayer, &rectEnemy)) {
				EntityAttribs* playerAttribs = entity_->getComponent<EntityAttribs>();
				int dmg = playerAttribs->getDmg();
				if (finCombo) {
					if (!canHit) playerAttribs->addCritProbability(0.02); //Aumentar probabilidad critico
					//Empujar y stunn al enemigo 
				}
				canHit = true;

				EntityAttribs* enmAttribs = ents[i]->getComponent<EntityAttribs>();
				//Le restamos la vida al enemigo
				enmAttribs->recieveDmg(dmg * 1.5);

				//Si puede envenenar
				if (playerAttribs->getCanPoison()) {
					// Número aleatorio para ver si envenena o no
					float i = sdlutils().rand().nextInt(1, 100);
					//Si i es menor que la probabilidad, envenena al enemigo
					if (i <= playerAttribs->getPoisonProb()) {
						enmAttribs->poison();
					}
				}

				auto& enmStateM = ents[i]->getComponent<EnemyStateMachine>()->getState();

				if (enmStateM != EnemyStates::ENM_DEAD) {
					//Si tiene stun, se aplica
					EnemyStun* enmStun = ents[i]->getComponent<EnemyStun>();
					if (enmStun != nullptr && enmStun->isActive()) {

						//Si no estaba aturdido ya
						if (enmStateM != EnemyStates::ENM_STUNNED) {
							//Aturdimos al enemigo
							enmStateM = EnemyStates::ENM_STUNNED;
							//Desactivamos componente de seguimiento de jugador
							FollowPlayer* flwPlayer = ents[i]->getComponent<FollowPlayer>();
							if (flwPlayer != nullptr)
								flwPlayer->setActive(false);
						}
						//Reiniciamos tiempo de stun
						enmStun->restartStunTime();
					}
				}

				//Si tiene Knockback, se aplica
				Knockback* enmKnockback = ents[i]->getComponent<Knockback>();
				if (enmKnockback != nullptr) {
					//Damos la vuelta si es atacado por detras
					auto& enmFlip = eTR->getFlip();
					if (enmFlip == tr_->getFlip())
						enmFlip = !enmFlip;

					if (finCombo) {
						enmKnockback->setKnockbackDistance(50);
						enmKnockback->knockback();
						enmKnockback->setKnockbackDistance(5);
					}
					else
						enmKnockback->knockback();
				}
			}
		}
	}
	return canHit;
}

void StrongAttack::render() {
	if (DEBUG_isAttacking_) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 0, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &attRect_);
	}
}

void StrongAttack::attack() {
	auto state = hms_->getState();
	if (hms_->canAttack() && sdlutils().currRealTime() > time_ + cooldown_) {

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
			attRect_.x = pos.getX() - attRect_.w + sizeW / 4 - cam.x; //esto no funciona bien para el resto de entidades solo con sardinilla supongo, mas tarde investigamos
		else
			attRect_.x = pos.getX() + sizeW - sizeW / 4 - cam.x;

		attRect_.y = pos.getY() + sizeH / 4 - cam.y;

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

		DEBUG_isAttacking_ = true;
		time_ = sdlutils().currRealTime();
		entity_->getComponent<Stroke>()->increaseChance(10, false);
	}
	else if (sdlutils().currRealTime() > time_ + cooldown_ / 2) {
		state = HamStates::IDLE;
	}
}