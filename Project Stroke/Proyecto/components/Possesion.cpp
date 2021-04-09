#include "Possesion.h"
#include "UI.h"
#include "Stroke.h"
#include "../sdlutils/InputHandler.h"
#include "KeyGame.h"
#include "../ecs/Manager.h"

void Possesion::init() {
	active_ = false;
}

void Possesion::render() {
	lineH->render(lineHPos);
	lineV->render(lineVPos);
}

//Comprueba que la tecla sea pulsada y la keyGame est� chocando con el marcador
void Possesion::update() {
	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(actualKey) && keyGame->getComponent<KeyGame>()->hitSkillCheck())
			succesfulHit();
		else
			failedHit();
	}
//Si se muere o infarta el poseido, se acaba la posesion
	if (possesedState->cantBeTargeted()) {
		endPossesion();
	}
}

void Possesion::onEnable() {
	start();
}

void Possesion::onDisable() {
	mistakes = 0;
	roundPassed = false;
	failed = false;
	possesed = nullptr;
	keyGame = nullptr;
}

void Possesion::start() {
	assert(possesed != nullptr);
	//Tomamos el estado del pose�do para comprobar que sigue vivo y no infartado mientras le ayudamos
	possesedState = possesed->getComponent<HamsterStateMachine>();
	
	//Calcula la posici�n del minijuego en funci�n del personahe poseido
	Vector2D aux = possesed->getComponent<UI>()->getBarPos();
	
	Vector2D pos = Vector2D(aux.getX() + LINE_OFFSET_X, aux.getY() + LINE_OFFSET_Y);
	lineHPos = build_sdlrect(pos, LINE_SIZE_X, LINE_SIZE_Y);

	pos = Vector2D(aux.getX() + V_LINE_OFFSET_X, aux.getY() + V_LINE_OFFSET_Y);
	lineVPos = build_sdlrect(pos, V_LINE_SIZE_X, V_LINE_SIZE_Y);

	//Crea la entidad del QuickTimeEvent
	keyGame = entity_->getMngr()->addEntity();																											
	keyGame->addComponent<Transform>(Vector2D(aux.getX() + LINE_OFFSET_X, aux.getY() + V_LINE_OFFSET_Y), Vector2D(BOX_INI_VEL_X, 0), BOX_SIZE_X, BOX_SIZE_Y, 0); 
	keyGame->addComponent<KeyGame>(lineHPos, lineVPos, this);
	randomiseKey();
}

void Possesion::reachedEnd() {
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

void Possesion::succesfulHit() {
	//Si no hemos fallado la prueba antes, se da por pasada
	if(!failed) roundPassed = true;
	
	//Se decrementa la probabilidad de infarto
	auto* str = possesed->getComponent<Stroke>();
	assert(str != nullptr);

	str->decreaseChance();
}

void Possesion::failedHit() {
	failed = true;
}

//Se elimina la key y se desactiva el componente al acabar
void Possesion::endPossesion() {
	keyGame->setActive(false);
	this->setActive(false);
}

//Coge una key y su respectiva imagen aleatorias
void Possesion::randomiseKey() {
	auto rand = sdlutils().rand().nextInt(0, numKeys);
	actualKey = keyCodes[rand];
	keyGame->getComponent<KeyGame>()->setTexture(keyTextures[rand]);
}