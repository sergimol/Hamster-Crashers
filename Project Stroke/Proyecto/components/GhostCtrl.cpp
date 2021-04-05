#include "GhostCtrl.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"


void GhostCtrl::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	mv_ = entity_->getComponent<Movement>();
	assert(mv_ != nullptr);
	st_ = entity_->getComponent<HamsterStateMachine>()->getState();
}


void GhostCtrl::onEnable() {
	//Animacion
}

void GhostCtrl::update() {
	auto& hamsters = entity_->getMngr()->getPlayers();
	for (Entity* e : hamsters) {
		auto* oTr = e->getComponent<Transform>();
		assert(oTr != nullptr);
		if (Collisions::collides(tr_->getPos(), tr_->getW(), tr_->getH(), oTr->getPos(), oTr->getW(), oTr->getH())) {
			actShow(true, tr_->getPos());
			if (ih().isKeyDown(key)) {
				startPossesion();
			}
		}
		else actShow(false,Vector2D(0, 0));
	}
}

void GhostCtrl::render() {
	if (show) {
		SDL_Rect rect = build_sdlrect(showPos, KEY_WIDHT, KEY_HEIGHT);
		tx_->render(rect);
	}
}

void GhostCtrl::actShow(bool s, const Vector2D& p) {
	show = s;
	showPos = p;
}

void GhostCtrl::startPossesion() {
	mv_->setActive(false);
	//animacion meterse dentro?
	actShow(false, Vector2D(0, 0));
	active_ = false;
	//activarMinijuego
}