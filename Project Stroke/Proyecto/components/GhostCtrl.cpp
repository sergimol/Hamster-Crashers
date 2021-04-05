#include "GhostCtrl.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "../components/Possesion.h"
#include "../components/Animator.h"


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
		if (e != entity_) {
			auto* oTr = e->getComponent<Transform>();
			assert(oTr != nullptr);
			show = Collisions::collides(tr_->getPos(), tr_->getW(), tr_->getH(), oTr->getPos(), oTr->getW(), oTr->getH());
			if (show && ih().isKeyDown(key)) {
				startPossesion();
			}
		}
	}
}

void GhostCtrl::render() {
	if (show) {
		Vector2D renderPos = Vector2D(tr_->getPos().getX() - Game::camera_.x, tr_->getPos().getY() + tr_->getZ() - Game::camera_.y);
		SDL_Rect dest = build_sdlrect(renderPos, KEY_WIDHT, KEY_HEIGHT);
		tx_->render(dest);
	}
}

void GhostCtrl::startPossesion() {
	mv_->setActive(false);
	//animacion meterse dentro?
	show = false;
	active_ = false;
	entity_->getComponent<Possesion>()->setActive(true);
	entity_->getComponent<Animator>()->setActive(false);
}