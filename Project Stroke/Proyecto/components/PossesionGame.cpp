#include "PossesionGame.h"
#include "UI.h"
#include "Stroke.h"
#include "../sdlutils/InputHandler.h"
#include "KeyGame.h"
#include "../ecs/Manager.h"

void PossesionGame::init() {
	active_ = false;

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void PossesionGame::render() {
	updateGamePos();

	lineH->render(lineHPos);
	lineV->render(lineVPos);
	if(keyGame != nullptr)
		keyGame->render();
}

//Comprueba que la tecla sea pulsada y la keyGame esté chocando con el marcador
void PossesionGame::update() {
	if (state_->getState() == GameStates::RUNNING) {

		/*std::cin >> H_LINE_OFFSET_X >> H_LINE_OFFSET_Y;
		std::cin >> V_LINE_OFFSET_X >> V_LINE_OFFSET_Y;*/

		if (keyGame != nullptr)
			keyGame->update();

		bool success = false;
		// Si el fantasma se está controlando con mando
		if (ih().playerHasController(playerNumber_)) {
			if (ih().isButtonDownEvent())
				success = ih().isButtonDown(playerNumber_, actualButton) && keyGame->getComponent<KeyGame>()->hitSkillCheck();
		}

		// Si se está controlando con teclado
		else if (ih().keyDownEvent()) {
			success = ih().isKeyDown(actualKey) && keyGame->getComponent<KeyGame>()->hitSkillCheck();
		}

		if (success)
			succesfulHit();
		else
			failedHit();

		//Si se muere o infarta el poseido, se acaba la posesion
		if (possesedState->cantBeTargeted()) {
			endPossesion();
		}
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

	delete keyGame;
	keyGame = nullptr;
}

void PossesionGame::start() {
	assert(possesed != nullptr);
	//Tomamos el estado del poseído para comprobar que sigue vivo y no infartado mientras le ayudamos
	possesedState = possesed->getComponent<HamsterStateMachine>();

	updateGamePos();

	//Crea la entidad del QuickTimeEvent
	keyGame = new Entity(entity_->getMngr());
	
	keyGame->addComponent<Transform>(Vector2D(lineHPos.x, lineHPos.y), Vector2D(BOX_INI_VEL_X, 0), BOX_SIZE_X, BOX_SIZE_Y, 0, 1, 1);
	keyGame->addComponent<KeyGame>(lineHPos, lineVPos, this);
	randomiseKey();
}

void PossesionGame::updateGamePos() {
	if (possesed != nullptr) {
		auto tr = possesed->getComponent<Transform>();
		auto pos = tr->getPos();
		float x = pos.getX() + tr->getW() / 2, y = pos.getY() + tr->getH() / 2;

		auto* cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>();
		x -= cam->getCamPos().getX() / 2.0f;
		y -= cam->getCamPos().getY() / 2.0f;

		pos.set(x + H_LINE_OFFSET_X, y + H_LINE_OFFSET_Y);
		lineHPos = build_sdlrect(pos, H_LINE_SIZE_X, H_LINE_SIZE_Y);

		pos.set(x + V_LINE_OFFSET_X, y + V_LINE_OFFSET_Y);
		lineVPos = build_sdlrect(pos, V_LINE_SIZE_X, V_LINE_SIZE_Y);
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
	//Si no hemos fallado la prueba antes, se da por pasada
	if(!failed) roundPassed = true;
	
	//Se decrementa la probabilidad de infarto
	auto* str = possesed->getComponent<Stroke>();
	assert(str != nullptr);

	str->decreaseChance();
}

void PossesionGame::failedHit() {
	failed = true;
}

//Se elimina la key y se desactiva el componente al acabar
void PossesionGame::endPossesion() {
	if (keyGame != nullptr) {
		delete keyGame;
		keyGame = nullptr;
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