#include "ReanimationGame.h"
#include "EntityAttribs.h"
#include "Image.h"
#include "SoundManager.h"

void ReanimationGame::init() {
	// No se habilita hasta que otro jugador lo inicia
	active_ = false;

	infarct_ = entity_->getComponent<InfarctedBody>();
	assert(infarct_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);

}

ReanimationGame::~ReanimationGame() {
	deleteTextures();
}

void ReanimationGame::update() {
	if (state_->getState() == GameStates::RUNNING) {
		if (ih().playerHasController(revPlNumber_))
			handleButton();
		else
			handleKey();

		if (sdlutils().currRealTime() > timer + TIME_BETWEEN_DROPS) {
			if (progress > 0)
				progress -= DROP;
			else
				progress = 0;

			timer = sdlutils().currRealTime();
		}

		if (progress >= MAX_PROGRESS) {
			endGame();
		}
	}

}

void ReanimationGame::handleKey() {
	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(key) && !down) {
			down = true;
			progress += BEAT;
			entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("rightNote");
		}
	}
	else if (ih().keyUpEvent()) {
		if (ih().isKeyUp(key) && down) {
			down = false;
		}
	}
}

void ReanimationGame::handleButton() {
	if (ih().isButtonDownEvent()) {
		if (ih().isButtonDown(revPlNumber_, button) && !down) {
			down = true;
			progress += BEAT;
			entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("rightNote");
		}
	}
	else if (ih().isButtonUpEvent()) {
		if (ih().isButtonUp(revPlNumber_, button) && down) {
			down = false;
		}
	}
}

void ReanimationGame::render() {
	if (txUp_ != nullptr && txDown_ != nullptr) {
		if (down) { txDown_->setActive(true);  txUp_->setActive(false);}
		else { txDown_->setActive(false);  txUp_->setActive(true); }
	}
}

void ReanimationGame::onDisable() {
	down = false;
	progress = 0;
	
	txUp_->setActive(false);
	txDown_->setActive(false);
	entity_->getMngr()->refreshUIObjects();
	
	deleteTextures();
}

void ReanimationGame::endGame() {
	//Reseteamos variables
	down = false;
	progress = 0;
	//Desactivamos el componente
	active_ = false;
	//Reanimamos al hamster
	infarct_->reanimate();

	deleteTextures();
}

void ReanimationGame::onResume() {
	timer += sdlutils().currRealTime() - timer;
}

void ReanimationGame::setRevPlayer(Entity* e)
{
	revPlNumber_ = e->getComponent<EntityAttribs>()->getNumber();
	revTrans_ = e->getComponent<Transform>();

	bool useController = ih().playerHasController(revPlNumber_);

	auto tr = entity_->getComponent<Transform>();
	auto pos = tr->getPos();

	float x = pos.getX(), y = pos.getY() + tr->getZ();

	auto cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
	x -= cam.x;
	y -= cam.y;

	pos.set(pos.getX() + OFFSET_X, pos.getY() + OFFSET_Y);
	if (txUp_ == nullptr) {
		txUp_ = new Entity(entity_->getMngr());
		txUp_->addComponent<Transform>(Vector2D(tr->getPos().getX() + tr->getW() / 2,
			tr->getPos().getY()),
			Vector2D(0, 0),
			WIDTH, HEIGHT, 0, 1, 1)->setZ(tr->getZ());
		txUp_->addComponent<Image>(&sdlutils().images().at(useController ? "a" : "a2"));
		entity_->getMngr()->getUIObjects().push_back(txUp_);
	}
	if (txDown_ == nullptr) {
		txDown_ = new Entity(entity_->getMngr());
		txDown_->addComponent<Transform>(Vector2D(tr->getPos().getX() + tr->getW() / 2,
			tr->getPos().getY()),
			Vector2D(0, 0),
			WIDTH, HEIGHT, 0, 1, 1)->setZ(tr->getZ());
		txDown_->addComponent<Image>(&sdlutils().images().at(useController ? "aPressed" : "a2Pressed"));
		entity_->getMngr()->getUIObjects().push_back(txDown_);
	}
}

void ReanimationGame::deleteTextures() {
	if (txUp_ != nullptr) { delete txUp_; txUp_ = nullptr; };
	if (txDown_ != nullptr) { delete txDown_; txDown_ = nullptr; };
}