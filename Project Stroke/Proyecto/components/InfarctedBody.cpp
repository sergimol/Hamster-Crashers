#include "InfarctedBody.h"
#include "ReanimationGame.h"
#include "Animator.h"
#include "Movement.h"
#include "AnimHamsterStateMachine.h"
#include "Stroke.h"
#include "GhostCtrl.h"
#include "../components/Roll.h"
#include "../components/Poison.h"
#include "../components/Pray.h"
#include "../components/Turret.h"
#include "../components/WarCry.h"
#include "../components/PossesionGame.h"

#include "../utils/Collisions.h"

void InfarctedBody::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

	ab_ = hamster->getComponent<Roll>();

	if (ab_ == nullptr) ab_ = hamster->getComponent<Pray>();
	if (ab_ == nullptr) ab_ = hamster->getComponent<Poison>();
	if (ab_ == nullptr) ab_ = hamster->getComponent<Turret>();
	if (ab_ == nullptr) ab_ = hamster->getComponent<WarCry>();

	assert(ab_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void InfarctedBody::update() {
	if (state_->getState() == GameStates::RUNNING) {
		auto& hamsters = entity_->getMngr()->getPlayers();
		for (Entity* e : hamsters) {
			if (e != hamster && !e->getComponent<HamsterStateMachine>()->cantBeTargeted()) {
				auto* oTr = e->getComponent<Transform>();
				assert(oTr != nullptr);
				show = Collisions::collides(tr_->getPos(), tr_->getW(), tr_->getH(), oTr->getPos(), oTr->getW(), oTr->getH());
				int eNum = e->getComponent<EntityAttribs>()->getNumber();
				isCtrl = ih().playerHasController(eNum);
				bool aux = false;
				if (isCtrl)
					aux = ih().isButtonDown(eNum, button);
				else
					aux = ih().isKeyDown(key);
				if (show && aux) {
					//Activamos el minijuego
					entity_->getComponent<ReanimationGame>()->setActive(true);
					entity_->getComponent<ReanimationGame>()->setRevPlayer(e);
					//Pasamos a estar siendo revividos
					reviving = true;
					//Y deshabilitamos al que revive
					disableOtherHamster(e);
				}
			}
		}
		//En caso de que el estado del hamster que nos revive cambie, se cancela el minijuego
		if (reviving) {
			if (otherState != HamStates::DEFAULT) {
				//Permitimos al otro moverse
				enableOtherHamster();
				//Se acaba el minijuego
				entity_->getComponent<ReanimationGame>()->setActive(false);
				//Dejamos de ser revividos
				reviving = false;
			}
		}
	}
}

void InfarctedBody::render() {
	//Si estamos en contacto con un posible "host" que nos pueda revivir, muestra la imagen del botón
	if (show && !reviving) {
		Vector2D renderPos = Vector2D(tr_->getPos().getX() + tr_->getW() - cam.x, tr_->getPos().getY() + tr_->getZ() - cam.y);
		SDL_Rect dest = build_sdlrect(renderPos, KEY_WIDTH, KEY_HEIGHT);
		tx_->render(dest);
	}
}

// Reactivamos todo lo desactivado durante el infarto
void InfarctedBody::reanimate() {
	//Reactivamos el otro hamster
	enableOtherHamster();
	// Vuelve a tener disponible la habilidad
	ab_->activateAbility();
	// Animacion de desinfarto
	hamster->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::STROKE, false);
	// El personaje vuelve a DEFAULT
	hamster->getComponent<HamsterStateMachine>()->getState() = HamStates::DEFAULT;
	// El hamster toma la posicion de su cadaver al revivir
	hamster->getComponent<Transform>()->setPos(entity_->getComponent<Transform>()->getPos());
	// Recupera el movimiento
	hamster->getComponent<Movement>()->setActive(true);
	// Recupera el renderizado
	hamster->getComponent<Animator>()->setActive(true);
	// Desactivamos el GhostControl en caso de que no se hubiera llegado a activar
	hamster->getComponent<GhostCtrl>()->setActive(false);
	// Deshacemos la posible posesión
	hamster->getComponent<PossesionGame>()->endPossesion();
	// Reactivamos el infarto
	hamster->getComponent<Stroke>()->setActive(true);
	// Reactivamos la UI del corazón
	hamster->getComponent<HeartUI>()->resurrection();

	entity_->setActive(false);
	entity_->getMngr()->refreshDeadBodies();
}

void InfarctedBody::disableOtherHamster(Entity* e) {
	//Recogemos el estado del "salvador" si no es el anterior
	if (otherHamster != e && e != nullptr) {
		otherHamster = e;
		otherState = otherHamster->getComponent<HamsterStateMachine>()->getState();
	}
	
	//Y le inhabilitamos el movimiento y el ataque
	if(otherHamster != nullptr)
		otherHamster->getComponent<Movement>()->setActive(false);
}

void InfarctedBody::enableOtherHamster() {
	if(otherHamster != nullptr)
		otherHamster->getComponent<Movement>()->setActive(true);
}