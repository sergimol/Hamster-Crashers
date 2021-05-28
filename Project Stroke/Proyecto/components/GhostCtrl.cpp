#include "GhostCtrl.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "../components/PossesionGame.h"
#include "../components/Animator.h"
#include "../components/Shadow.h"
#include "Image.h"


void GhostCtrl::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	mv_ = entity_->getComponent<Movement>();
	assert(mv_ != nullptr);

	st_ = entity_->getComponent<HamsterStateMachine>()->getState();

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void GhostCtrl::update() {
	if (state_->getState() == GameStates::RUNNING) {
		//Busca entre el resto de hamsters uno al que pueda poseer
		auto& hamsters = entity_->getMngr()->getPlayers();
		for (Entity* e : hamsters) {
			if (e != entity_ && !e->getComponent<HamsterStateMachine>()->cantBeTargeted()) {
				auto* oTr = e->getComponent<Transform>();
				assert(oTr != nullptr);

				auto rect1 = tr_->getRectCollide(),
					rect2 = oTr->getRectCollide();

				show_ = Collisions::collides(Vector2D(rect1.x, rect1.y), rect1.w, rect1.h,
					Vector2D(rect2.x, rect2.y), rect2.w, rect2.h);

				if (show_) {
					int n = entity_->getComponent<EntityAttribs>()->getNumber();
					isController_ = ih().playerHasController(n);

					generateKey();

					updateKey();

					if((isController_ && ih().isButtonDown(n, button_)) || (!isController_ && ih().isKeyDown(key_)))
						startPossesion(e);
				}
				else {
					if (keyTx_ != nullptr) keyTx_->getComponent<Image>()->setActive(false);
				}
			}
		}
	}
}

void GhostCtrl::render() {
	//Si estamos en contacto con un posible "host" para poseer, muestra la imagen del botón
	/*if (keyTx_ != nullptr) {
		if (show_) {

		}
		else {

		}
	}*/

}

void GhostCtrl::startPossesion(Entity* e) {
	deleteKey();
	//Quitamos el movimiento y la imagen al poseer
	mv_->setActive(false);
	entity_->getComponent<Animator>()->setActive(false);
	entity_->getComponent<Shadow>()->setActive(false);

	//Paramos el componente para que deje de buscar jugadores
	show_ = false;
	active_ = false;

	//Activamos el minijuego
	auto* poss = entity_->getComponent<PossesionGame>();

	poss->setPossesed(e);
	poss->setActive(true);

	//e->getComponent<Animator>()->setTexture(&sdlutils().images().at(e->getComponent<EntityAttribs>()->getId() + "Sheet3"));
	//keyTx_(&sdlutils().images().at("q")), buttonTx_(&sdlutils().images().at("b"))
}

void GhostCtrl::generateKey() {
	if (keyTx_ == nullptr) {
		keyTx_ = new Entity(entity_->getMngr());
		auto pos = tr_->getPos();
		keyTx_->addComponent<Transform>(Vector2D(pos.getX() + tr_->getW() / 2, pos.getY() - tr_->getZ()),
			Vector2D(0, 0),
			KEY_WIDTH, KEY_HEIGHT, 0, 1, 1)->setFloor(tr_->getFloor());
		keyTx_->addComponent<Image>(&sdlutils().images().at(isController_ ? "b" : "q"));
		entity_->getMngr()->getUIObjects().push_back(keyTx_);
	}
	else {
		keyTx_->getComponent<Image>()->setActive(true);
	}
}

void GhostCtrl::updateKey() {
	if (keyTx_ != nullptr) {
		auto pos = tr_->getPos();
		keyTx_->getComponent<Transform>()->setPos(Vector2D(pos.getX() + tr_->getW()/2, pos.getY() - tr_->getZ()));
		keyTx_->getComponent<Transform>()->setFloor(tr_->getFloor());
	}
}

void GhostCtrl::deleteKey() {
	if (keyTx_ != nullptr) {
		keyTx_->setActive(false);
		entity_->getMngr()->refreshUIObjects();
		delete keyTx_;
		keyTx_ = nullptr;
	}
}

void GhostCtrl::onDisable() {
	deleteKey();
}