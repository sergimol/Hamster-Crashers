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
	lineH->render(lineHPos);
	lineV->render(lineVPos);
}

//Comprueba que la tecla sea pulsada y la keyGame esté chocando con el marcador
void PossesionGame::update() {
	if (state_->getState() == GameStates::RUNNING) {
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
	keyGame = nullptr;
}

void PossesionGame::start() {
	assert(possesed != nullptr);
	//Tomamos el estado del poseído para comprobar que sigue vivo y no infartado mientras le ayudamos
	possesedState = possesed->getComponent<HamsterStateMachine>();
	
	//Calcula la posición del minijuego en función del personahe poseido
	Vector2D aux = possesed->getComponent<UI>()->getBarPos();
	
	Vector2D pos = Vector2D(aux.getX() + LINE_OFFSET_X, aux.getY() + LINE_OFFSET_Y);
	lineHPos = build_sdlrect(pos, LINE_SIZE_X, LINE_SIZE_Y);

	pos = Vector2D(aux.getX() + V_LINE_OFFSET_X, aux.getY() + V_LINE_OFFSET_Y);
	lineVPos = build_sdlrect(pos, V_LINE_SIZE_X, V_LINE_SIZE_Y);

	//Crea la entidad del QuickTimeEvent
	keyGame = entity_->getMngr()->addEntity();																											
	keyGame->addComponent<Transform>(Vector2D(aux.getX() + LINE_OFFSET_X, aux.getY() + V_LINE_OFFSET_Y), Vector2D(BOX_INI_VEL_X, 0), BOX_SIZE_X, BOX_SIZE_Y, 0,1,1); 
	keyGame->addComponent<KeyGame>(lineHPos, lineVPos, this);
	randomiseKey();
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
		keyGame->setActive(false);
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
	}
	else
	{
		actualKey = keyCodes[rand];
		keyGame->getComponent<KeyGame>()->setTexture(keyTextures[rand]);
	}
}