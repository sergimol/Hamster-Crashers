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


//Comprueba que la tecla sea pulsada y la keyGame esté chocando con el marcador
void PossesionGame::update() {
	if (state_->getState() == GameStates::RUNNING) {
		if (keyGame != nullptr)
			keyGame->update();

		bool success = false;

		// Si el fantasma se está controlando con mando
		if (ih().playerHasController(playerNumber_)) {
			if (ih().isButtonDownEvent()) {
				success = ih().isButtonDown(playerNumber_, actualButton) && keyGame->getComponent<KeyGame>()->hitSkillCheck();

				if (success)
					succesfulHit();
				else
					failedHit();
			}
		}
		// Si se está controlando con teclado
		else if (ih().keyDownEvent()) {
			success = ih().isKeyDown(actualKey) && keyGame->getComponent<KeyGame>()->hitSkillCheck();

			if (success)
				succesfulHit();
			else
				failedHit();
		}
		//Si se muere o infarta el poseido, se acaba la posesion
		if (possesedState->cantBeTargeted()) {
			endPossesion();
		}

		updateGamePos();
	}
}

void PossesionGame::onEnable() {
	start();
}

void PossesionGame::onDisable() {
	mistakes = 0;
	roundPassed = false;
	failed = false;
	possesed = nullptr;

	deleteTextures();
}

void PossesionGame::start() {
	assert(possesed != nullptr);
	//Tomamos el estado del poseído para comprobar que sigue vivo y no infartado mientras le ayudamos
	possesedState = possesed->getComponent<HamsterStateMachine>();

	playerNumber_ = entity_->getComponent<EntityAttribs>()->getNumber();

	updateGamePos();

	auto tr = possesed->getComponent<Transform>();
	auto pos = tr->getPos();

	//Horizontal
	if (lineH == nullptr) {
		lineH = new Entity(entity_->getMngr());
		lineH->addComponent<Transform>(Vector2D(pos.getX() + H_LINE_OFFSET_X, pos.getY() + H_LINE_OFFSET_Y),
			Vector2D(0, 0),
			H_LINE_SIZE_X, H_LINE_SIZE_Y, 0, 1, 1)->setZ(tr->getZ());
		lineH->addComponent<Image>(&sdlutils().images().at("linea"));
		entity_->getMngr()->getUIObjects().push_back(lineH);
	}
	//Vertical
	if (lineV == nullptr) {
		lineV = new Entity(entity_->getMngr());
		lineV->addComponent<Transform>(Vector2D(pos.getX() + V_LINE_OFFSET_X, pos.getY() + V_LINE_OFFSET_Y),
			Vector2D(0, 0),
			V_LINE_SIZE_X, V_LINE_SIZE_Y, 0, 1, 1)->setZ(tr->getZ());
		lineV->addComponent<Image>(&sdlutils().images().at("lineaV"));
		entity_->getMngr()->getUIObjects().push_back(lineV);
	}
	//Crea la entidad del QuickTimeEvent
	if (keyGame == nullptr) {
		keyGame = new Entity(entity_->getMngr());
		keyGame->addComponent<Transform>(Vector2D(lineHPos.x - BOX_SIZE_X / 2, lineHPos.y - BOX_SIZE_Y / 2), Vector2D(0, 0), BOX_SIZE_X, BOX_SIZE_Y, 0, 1, 1);
		keyGame->addComponent<KeyGame>(lineHPos, lineVPos, this, possesed->getComponent<EntityAttribs>()->getVel().getX());
		entity_->getMngr()->getUIObjects().push_back(keyGame);
	}
	

	randomiseKey();
}

void PossesionGame::updateGamePos() {
	if (possesed != nullptr) {
		auto tr = possesed->getComponent<Transform>();
		auto pos = tr->getPos();

		float x = pos.getX() + tr->getW() / 2,
			y = pos.getY() - tr->getZ();

		if (lineH != nullptr)
			lineH->getComponent<Transform>()->setPos(Vector2D(x + H_LINE_OFFSET_X, y + H_LINE_OFFSET_Y));
		if (lineV != nullptr)
			lineV->getComponent<Transform>()->setPos(Vector2D(x + V_LINE_OFFSET_X, y + V_LINE_OFFSET_Y));

		auto cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
		x -= cam.x;
		y -= cam.y;

		pos.set(x + H_LINE_OFFSET_X, y + H_LINE_OFFSET_Y);
		lineHPos = build_sdlrect(pos, H_LINE_SIZE_X, H_LINE_SIZE_Y);

		pos.set(x + V_LINE_OFFSET_X, y + V_LINE_OFFSET_Y);
		lineVPos = build_sdlrect(pos, V_LINE_SIZE_X, V_LINE_SIZE_Y);

		if (keyGame != nullptr) {
			//Dir = 0, 1, -1 en funcio de si va palante, patras o esta quieto
			float dir = tr->getVel().getX() > 0 ? 1 : tr->getVel().getX() < 0 ? -1 : 0;
			keyGame->getComponent<KeyGame>()->updateGamePos(lineVPos, lineHPos,  dir);
		}
	}
}

void PossesionGame::reachedEnd() {
	if (!roundPassed)
		mistakes++;
	
	roundPassed = false;
	failed = false;

	if (mistakes >= maxMistakes) {
		endPossesion();
	}
	else {
		randomiseKey();
	}
}

void PossesionGame::succesfulHit() {
	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("rightNote");

	//Si no hemos fallado la prueba antes, se da por pasada
	if(!failed) roundPassed = true;
	
	//Se decrementa la probabilidad de infarto
	auto* str = possesed->getComponent<Stroke>();
	assert(str != nullptr);

	str->decreaseChance();
}

void PossesionGame::failedHit() {
	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("wrongNote");
	failed = true;
}

//Se elimina la key y se desactiva el componente al acabar
void PossesionGame::endPossesion() {
	if (keyGame != nullptr && lineH != nullptr && lineV != nullptr) {
		keyGame->setActive(false);
		lineH->setActive(false);
		lineV->setActive(false);

		entity_->getMngr()->refreshUIObjects();
		
		deleteTextures();
	}
	this->setActive(false);
}

//Coge una key y su respectiva imagen aleatorias
void PossesionGame::randomiseKey() {
	auto rand = sdlutils().rand().nextInt(0, numKeys);
	if (ih().playerHasController(playerNumber_)) {
		actualButton = buttonCodes[rand];
		keyGame->getComponent<KeyGame>()->setTexture(buttonTextures[rand]);
		keyGame->getComponent<KeyGame>()->setTextureDown(buttonDownTextures[rand]);
	}
	else{
		actualKey = keyCodes[rand];
		keyGame->getComponent<KeyGame>()->setTexture(keyTextures[rand]);
		keyGame->getComponent<KeyGame>()->setTextureDown(keyDownTextures[rand]);
	}
}

void PossesionGame::deleteTextures() {
	if (keyGame != nullptr) {
		delete keyGame;
		keyGame = nullptr;
	}

	if (lineH != nullptr) {
		delete lineH;
		lineH = nullptr;
	}

	if (lineV != nullptr) {
		delete lineV;
		lineV = nullptr;
	}
}