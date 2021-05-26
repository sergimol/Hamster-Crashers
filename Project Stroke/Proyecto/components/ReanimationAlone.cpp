#include "ReanimationAlone.h"
#include "UI.h"
#include "Stroke.h"

#include "Roll.h"
#include "Pray.h"
#include "Poison.h"
#include "Turret.h"
#include "WarCry.h"

#include "KeyGame.h"
#include "SoundManager.h"
#include "Image.h"
#include "Movement.h"
#include "StrongAttack.h"
#include "LightAttack.h"

#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

void ReanimationAlone::init() {
	gameState_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(gameState_ != nullptr);

	ab_ = entity_->getComponent<Roll>();

	if (ab_ == nullptr) ab_ = entity_->getComponent<Pray>();
	if (ab_ == nullptr) ab_ = entity_->getComponent<Poison>();
	if (ab_ == nullptr) ab_ = entity_->getComponent<Turret>();
	if (ab_ == nullptr) ab_ = entity_->getComponent<WarCry>();

	assert(ab_ != nullptr);

	start();
}


//Comprueba que la tecla sea pulsada y la keyGame esté chocando con el marcador
void ReanimationAlone::update() {
	if (gameState_->getState() == GameStates::RUNNING) {
		if (keyGame_ != nullptr)
			keyGame_->update();

		bool success = false;

		// Si el fantasma se está controlando con mando
		if (ih().playerHasController(0)) {
			if (ih().isButtonDownEvent()) {
				success = ih().isButtonDown(0, actualButton_) && keyGame_->getComponent<KeyGame>()->hitSkillCheck();

				if (success)
					succesfulHit();
				else
					failedHit();
			}
		}
		// Si se está controlando con teclado
		else if (ih().keyDownEvent()) {
			success = ih().isKeyDown(actualKey_) && keyGame_->getComponent<KeyGame>()->hitSkillCheck();

			if (success)
				succesfulHit();
			else
				failedHit();
		}
		////Si se muere o infarta el poseido, se acaba la posesion
		//if (hamState_->cantBeTargeted()) {
		//	endPossesion();
		//}

		updateGamePos();
	}
}

void ReanimationAlone::onEnable() {
}

void ReanimationAlone::onDisable() {
	hits_ = 0;
	roundPassed_ = false;
	failed_ = false;

	//deleteTextures();
}

void ReanimationAlone::start() {
	hamState_ = entity_->getComponent<HamsterStateMachine>();

	updateGamePos();

	auto tr = entity_->getComponent<Transform>();
	auto pos = tr->getPos();

	//Horizontal
	if (lineH_ == nullptr) {
		lineH_ = new Entity(entity_->getMngr());
		lineH_->addComponent<Transform>(Vector2D(pos.getX() + H_LINE_OFFSET_X, pos.getY() + H_LINE_OFFSET_Y),
			Vector2D(0, 0),
			H_LINE_SIZE_X, H_LINE_SIZE_Y, 0, 1, 1)->setZ(tr->getZ());
		lineH_->addComponent<Image>(&sdlutils().images().at("linea"));
		entity_->getMngr()->getUIObjects().push_back(lineH_);
	}
	//Vertical
	if (lineV_ == nullptr) {
		lineV_ = new Entity(entity_->getMngr());
		lineV_->addComponent<Transform>(Vector2D(pos.getX() + V_LINE_OFFSET_X, pos.getY() + V_LINE_OFFSET_Y),
			Vector2D(0, 0),
			V_LINE_SIZE_X, V_LINE_SIZE_Y, 0, 1, 1)->setZ(tr->getZ());
		lineV_->addComponent<Image>(&sdlutils().images().at("lineaV"));
		entity_->getMngr()->getUIObjects().push_back(lineV_);
	}
	//Crea la entidad del QuickTimeEvent
	if (keyGame_ == nullptr) {
		keyGame_ = new Entity(entity_->getMngr());
		keyGame_->addComponent<Transform>(Vector2D(lineHPos_.x - BOX_SIZE_X / 2, lineHPos_.y - BOX_SIZE_Y / 2), Vector2D(0, 0), BOX_SIZE_X, BOX_SIZE_Y, 0, 1, 1);
		keyGame_->addComponent<KeyGame>(lineHPos_, lineVPos_, this, entity_->getComponent<EntityAttribs>()->getVel().getX());
		entity_->getMngr()->getUIObjects().push_back(keyGame_);
	}


	randomiseKey();
}

void ReanimationAlone::updateGamePos() {
	
	auto tr = entity_->getComponent<Transform>();
	auto pos = tr->getPos();

	float x = pos.getX() + tr->getW() / 2,
		y = pos.getY() - tr->getZ();

	if (lineH_ != nullptr)
		lineH_->getComponent<Transform>()->setPos(Vector2D(x + H_LINE_OFFSET_X, y + H_LINE_OFFSET_Y));
	if (lineV_ != nullptr)
		lineV_->getComponent<Transform>()->setPos(Vector2D(x + V_LINE_OFFSET_X, y + V_LINE_OFFSET_Y));

	auto cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
	x -= cam.x;
	y -= cam.y;

	pos.set(x + H_LINE_OFFSET_X, y + H_LINE_OFFSET_Y);
	lineHPos_ = build_sdlrect(pos, H_LINE_SIZE_X, H_LINE_SIZE_Y);

	pos.set(x + V_LINE_OFFSET_X, y + V_LINE_OFFSET_Y);
	lineVPos_ = build_sdlrect(pos, V_LINE_SIZE_X, V_LINE_SIZE_Y);

	if (keyGame_ != nullptr) {
		//Dir = 0, 1, -1 en funcio de si va palante, patras o esta quieto
		float dir = tr->getVel().getX() > 0 ? 1 : tr->getVel().getX() < 0 ? -1 : 0;
		keyGame_->getComponent<KeyGame>()->updateGamePos(lineVPos_, lineHPos_, dir);
	}
	
}

void ReanimationAlone::reachedEnd() {
	if (roundPassed_)
		hits_++;
	else if(!failed_)
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("wrongNote");

	roundPassed_ = false;
	failed_ = false;

	if (hits_ >= hitsToWin_) {
		endPossesion();
	}
	else {
		randomiseKey();
	}
}

void ReanimationAlone::succesfulHit() {
	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("rightNote");

	//Si no hemos fallado la prueba antes, se da por pasada
	if (!failed_) roundPassed_ = true;
}

void ReanimationAlone::failedHit() {
	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("wrongNote");
	failed_ = true;
}

//Se elimina la key y se desactiva el componente al acabar
void ReanimationAlone::endPossesion() {
	if (keyGame_ != nullptr && lineH_ != nullptr && lineV_ != nullptr) {
		keyGame_->setActive(false);
		lineH_->setActive(false);
		lineV_->setActive(false);

		entity_->getMngr()->refreshUIObjects();

		deleteTextures();
	}
	this->setActive(false);

	reanimate();
}

void ReanimationAlone::reanimate() {
	entity_->getComponent<Movement>()->setActive(true);
	entity_->getComponent<LightAttack>()->setActive(true);
	entity_->getComponent<StrongAttack>()->setActive(true);

	// Vuelve a tener disponible la habilidad
	ab_->activateAbility();
	// Animacion de desinfarto
	entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::STROKE_ALONE, false);
	// El personaje vuelve a DEFAULT
	entity_->getComponent<HamsterStateMachine>()->getState() = HamStates::DEFAULT;
	// Recupera el movimiento
	entity_->getComponent<Movement>()->setActive(true);
	// Recupera el renderizado
	entity_->getComponent<Animator>()->setActive(true);
	// Reactivamos el infarto
	entity_->getComponent<Stroke>()->setActive(true);
	//Devolvemos el movimiento
	entity_->getComponent<Movement>()->setActive(true);
	// Reactivamos la UI del corazón
	entity_->getComponent<HeartUI>()->resurrection();
	//entity_->getComponent<UI>()->resurrection();

}

//Coge una key y su respectiva imagen aleatorias
void ReanimationAlone::randomiseKey() {
	auto rand = sdlutils().rand().nextInt(0, numKeys_);
	if (ih().playerHasController(0)) {
		actualButton_ = buttonCodes_[rand];
		keyGame_->getComponent<KeyGame>()->setTexture(buttonTextures_[rand]);
		keyGame_->getComponent<KeyGame>()->setTextureDown(buttonDownTextures_[rand]);
	}
	else {
		actualKey_ = keyCodes_[rand];
		keyGame_->getComponent<KeyGame>()->setTexture(keyTextures_[rand]);
		keyGame_->getComponent<KeyGame>()->setTextureDown(keyDownTextures_[rand]);
	}
}

void ReanimationAlone::deleteTextures() {
	if (keyGame_ != nullptr) {
		delete keyGame_;
		keyGame_ = nullptr;
	}

	if (lineH_ != nullptr) {
		delete lineH_;
		lineH_ = nullptr;
	}

	if (lineV_ != nullptr) {
		delete lineV_;
		lineV_ = nullptr;
	}
}