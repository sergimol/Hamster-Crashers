#include "PossesionGame.h"
#include "UI.h"
#include "Stroke.h"
#include "../sdlutils/InputHandler.h"
#include "KeyGame.h"
#include "SoundManager.h"
#include "Image.h"

#include "../ecs/Manager.h"

void PossesionGame::init() {
	active_ = false;

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);

}


//Comprueba que la tecla sea pulsada y la keyGame est� chocando con el marcador
void PossesionGame::update() {
	if (state_->getState() == GameStates::RUNNING) {
		if (keyGame_ != nullptr)
			keyGame_->update();

		bool success = false;

		// Si el fantasma se est� controlando con mando
		if (ih().playerHasController(playerNumber_)) {
			if (ih().isButtonDownEvent() && ih().isAnyResurrectButtonDown(playerNumber_)) {
				success = ih().isButtonDown(playerNumber_, actualButton_) && keyGame_->getComponent<KeyGame>()->hitSkillCheck();

				if (success)
					succesfulHit();
				else
					failedHit();

				keyGame_->getComponent<KeyGame>()->goBack();
			}
		}
		// Si se est� controlando con teclado
		else if (ih().keyDownEvent()) {
			success = ih().isKeyDown(actualKey_) && keyGame_->getComponent<KeyGame>()->hitSkillCheck();

			if (success)
				succesfulHit();
			else
				failedHit();

			keyGame_->getComponent<KeyGame>()->goBack();
		}
		//Si se muere o infarta el poseido, se acaba la posesion
		if (possesedState_->cantBeTargeted()) {
			endPossesion();
		}

		updateGamePos();
	}
}

void PossesionGame::onEnable() {
	start();
}

void PossesionGame::onDisable() {
	mistakes_ = 0;
	roundPassed_ = false;
	failed_ = false;
	possesed_ = nullptr;

	deleteTextures();
}

void PossesionGame::start() {
	assert(possesed_ != nullptr);
	//Tomamos el estado del pose�do para comprobar que sigue vivo y no infartado mientras le ayudamos
	possesedState_ = possesed_->getComponent<HamsterStateMachine>();

	playerNumber_ = entity_->getComponent<EntityAttribs>()->getNumber();

	updateGamePos();

	auto tr = possesed_->getComponent<Transform>();
	auto pos = tr->getPos();

	//Horizontal
	if (lineH_ == nullptr) {
		lineH_ = new Entity(entity_->getMngr());
		lineH_->addComponent<Transform>(Vector2D(pos.getX() + H_LINE_OFFSET_X, pos.getY() + H_LINE_OFFSET_Y),
			Vector2D(0, 0),
			H_LINE_SIZE_X, H_LINE_SIZE_Y, 0, 1, 1)->setFloor(tr->getFloor());
		lineH_->addComponent<Image>(&sdlutils().images().at("linea"));
		entity_->getMngr()->getUIObjects().push_back(lineH_);
	}
	//Vertical
	if (lineV_ == nullptr) {
		lineV_ = new Entity(entity_->getMngr());
		lineV_->addComponent<Transform>(Vector2D(pos.getX() + V_LINE_OFFSET_X, pos.getY() + V_LINE_OFFSET_Y),
			Vector2D(0, 0),
			V_LINE_SIZE_X, V_LINE_SIZE_Y, 0, 1, 1)->setFloor(tr->getFloor());
		lineV_->addComponent<Image>(&sdlutils().images().at("lineaV"));
		entity_->getMngr()->getUIObjects().push_back(lineV_);
	}
	//Crea la entidad del QuickTimeEvent
	if (keyGame_ == nullptr) {
		keyGame_ = new Entity(entity_->getMngr());
		keyGame_->addComponent<Transform>(Vector2D(lineHPos_.x - BOX_SIZE_X / 2, lineHPos_.y - BOX_SIZE_Y / 2), Vector2D(0, 0), BOX_SIZE_X, BOX_SIZE_Y, 0, 1, 1)->setFloor(tr->getFloor());
		keyGame_->addComponent<KeyGame>(lineHPos_, lineVPos_, this, possesed_->getComponent<EntityAttribs>()->getVel().getX());
		entity_->getMngr()->getUIObjects().push_back(keyGame_);
	}
	

	randomiseKey();
}

void PossesionGame::updateGamePos() {
	if (possesed_ != nullptr) {
		auto tr = possesed_->getComponent<Transform>();
		auto pos = tr->getPos();

		float x = pos.getX() + tr->getW() / 2,
			y = pos.getY() - tr->getZ();

		if (lineH_ != nullptr) {
			lineH_->getComponent<Transform>()->setPos(Vector2D(x + H_LINE_OFFSET_X, y + H_LINE_OFFSET_Y));
			lineH_->getComponent<Transform>()->setFloor(tr->getFloor());
		}
		if (lineV_ != nullptr) {
			lineV_->getComponent<Transform>()->setPos(Vector2D(x + V_LINE_OFFSET_X, y + V_LINE_OFFSET_Y));
			lineV_->getComponent<Transform>()->setFloor(tr->getFloor());
		}
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
			keyGame_->getComponent<KeyGame>()->updateGamePos(lineVPos_, lineHPos_,  dir);
		}
	}
}

void PossesionGame::reachedEnd() {
	if (!roundPassed_) {
		mistakes_++;
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("wrongNote");
	}
	roundPassed_ = false;
	failed_ = false;

	if (mistakes_ >= maxMistakes_) {
		endPossesion();
	}
	else {
		randomiseKey();
	}
}

void PossesionGame::succesfulHit() {
	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("rightNote");

	//Si no hemos fallado la prueba antes, se da por pasada
	roundPassed_ = true;
	
	//Se decrementa la probabilidad de infarto
	auto* str = possesed_->getComponent<Stroke>();
	assert(str != nullptr);

	str->decreaseChance();
}

void PossesionGame::failedHit() {
	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("wrongNote");
	failed_ = true;
}

//Se elimina la key y se desactiva el componente al acabar
void PossesionGame::endPossesion() {
	if (active_) {
		if (keyGame_ != nullptr && lineH_ != nullptr && lineV_ != nullptr) {
			keyGame_->setActive(false);
			lineH_->setActive(false);
			lineV_->setActive(false);

			entity_->getMngr()->refreshUIObjects();
		}
		possesed_->getComponent<Animator>()->setTexture(&sdlutils().images().at(possesed_->getComponent<EntityAttribs>()->getId() + "Sheet"));
		this->setActive(false);
	}
}

//Coge una key y su respectiva imagen aleatorias
void PossesionGame::randomiseKey() {
	auto rand = sdlutils().rand().nextInt(0, numKeys_);
	if (ih().playerHasController(playerNumber_)) {
		actualButton_ = buttonCodes_[rand];
		keyGame_->getComponent<KeyGame>()->setTexture(buttonTextures_[rand]);
		keyGame_->getComponent<KeyGame>()->setTextureDown(buttonDownTextures_[rand]);
	}
	else{
		actualKey_ = keyCodes_[rand];
		keyGame_->getComponent<KeyGame>()->setTexture(keyTextures_[rand]);
		keyGame_->getComponent<KeyGame>()->setTextureDown(keyDownTextures_[rand]);
	}
}

void PossesionGame::deleteTextures() {
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