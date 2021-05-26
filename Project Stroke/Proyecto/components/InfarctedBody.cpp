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
#include "../components/Shadow.h"
#include "Image.h"

#include "../utils/Collisions.h"

void InfarctedBody::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

	ab_ = hamster_->getComponent<Roll>();

	if (ab_ == nullptr) ab_ = hamster_->getComponent<Pray>();
	if (ab_ == nullptr) ab_ = hamster_->getComponent<Poison>();
	if (ab_ == nullptr) ab_ = hamster_->getComponent<Turret>();
	if (ab_ == nullptr) ab_ = hamster_->getComponent<WarCry>();

	assert(ab_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);

	reviving_ = false;

	
}

void InfarctedBody::update() {
	if (state_->getState() == GameStates::RUNNING) {
		if (!reviving_) {
			auto& hamsters = entity_->getMngr()->getPlayers();
			for (Entity* e : hamsters) {
				if (e != hamster_ && !e->getComponent<HamsterStateMachine>()->cantBeTargeted()) {
					auto* oTr = e->getComponent<Transform>();
					assert(oTr != nullptr);

					auto rect1 = tr_->getRectCollide(),
						 rect2 = oTr->getRectCollide();

					show_ = Collisions::collides(Vector2D(rect1.x, rect1.y), rect1.w, rect1.h, 
											    Vector2D(rect2.x, rect2.y), rect2.w, rect2.h);

					bool aux = false;
					if (show_) {
						int eNum = e->getComponent<EntityAttribs>()->getNumber();

						isCtrl = ih().playerHasController(eNum);

						if (isCtrl)
							aux = ih().isButtonDown(eNum, button);
						else
							aux = ih().isKeyDown(key);

						if (tx_ == nullptr) {
							tx_ = new Entity(entity_->getMngr());
							tx_->addComponent<Transform>(Vector2D(tr_->getPos().getX(), tr_->getPos().getY()),
								Vector2D(0, 0),
								KEY_WIDTH, KEY_HEIGHT, 0, 1, 1)->setZ(tr_->getZ());
							tx_->addComponent<Image>(isCtrl ? &sdlutils().images().at("b") : &sdlutils().images().at("p"));
							entity_->getMngr()->getUIObjects().push_back(tx_);
						}

						if (aux) {
							//Activamos el minijuego
							entity_->getComponent<ReanimationGame>()->setActive(true);
							entity_->getComponent<ReanimationGame>()->setRevPlayer(e);
							//Sonido
							entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("possesion");
							//Pasamos a estar siendo revividos
							reviving_ = true;
							//Y deshabilitamos al que revive
							disableOtherHamster(e);
							//Quitamos el botón
							deleteTexture();
						}
					}
					else {
						deleteTexture();
					}
				}
			}
		}
		//En caso de que el estado del hamster que nos revive cambie, se cancela el minijuego
		else{
			if (otherHamster->getComponent<HamsterStateMachine>()->getState() != HamStates::DEFAULT) {
				//Permitimos al otro moverse
				enableOtherHamster();
				//Se acaba el minijuego
				entity_->getComponent<ReanimationGame>()->setActive(false);
				//Dejamos de ser revividos
				reviving_ = false;

				deleteTexture();
			}
		}
	}
}

void InfarctedBody::render() {
	//Si estamos en contacto con un posible "host" que nos pueda revivir, muestra la imagen del botón
	if (show_ && !reviving_) {
		/*Vector2D renderPos = Vector2D(tr_->getPos().getX() + tr_->getW() - cam.x, tr_->getPos().getY() + tr_->getZ() - cam.y);
		SDL_Rect dest = build_sdlrect(renderPos, KEY_WIDTH, KEY_HEIGHT);*/
		tx_->setActive(true);
	}
}

// Reactivamos todo lo desactivado durante el infarto
void InfarctedBody::reanimate() {
	//Reactivamos el otro hamster
	enableOtherHamster();
	// Vuelve a tener disponible la habilidad
	ab_->activateAbility();
	// Animacion de desinfarto
	hamster_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::STROKE, false);
	// El personaje vuelve a DEFAULT
	hamster_->getComponent<HamsterStateMachine>()->getState() = HamStates::DEFAULT;
	// El hamster toma la posicion de su cadaver al revivir
	hamster_->getComponent<Transform>()->setPos(entity_->getComponent<Transform>()->getPos());
	// Recupera el movimiento
	hamster_->getComponent<Movement>()->setActive(true);
	// Recupera el renderizado
	hamster_->getComponent<Animator>()->setActive(true);
	// Desactivamos el GhostControl en caso de que no se hubiera llegado a activar
	hamster_->getComponent<GhostCtrl>()->setActive(false);
	// Deshacemos la posible posesión
	hamster_->getComponent<PossesionGame>()->endPossesion();;
	// Reactivamos el infarto
	hamster_->getComponent<Stroke>()->setActive(true);
	// Devolvemos la sombra
	hamster_->getComponent<Shadow>()->setActive(true);
	// Reactivamos la UI del corazón
	hamster_->getComponent<HeartUI>()->resurrection();
	hamster_->getComponent<UI>()->resurrection();

	entity_->setActive(false);
	entity_->getMngr()->refreshDeadBodies();

	reviving_ = false;

	deleteTexture();
}

void InfarctedBody::disableOtherHamster(Entity* e) {
	//Recogemos el estado del "salvador" si no es el anterior
	if (otherHamster != e && e != nullptr) {
		otherHamster = e;
		otherState = otherHamster->getComponent<HamsterStateMachine>()->getState();
	}
	
	//Y le inhabilitamos el movimiento y el ataque
	if (otherHamster != nullptr) {
		otherHamster->getComponent<Transform>()->setVel(Vector2D(0, 0));
		otherHamster->getComponent<Movement>()->setActive(false);
		otherHamster->getComponent<LightAttack>()->setActive(false);
		otherHamster->getComponent<StrongAttack>()->setActive(false);
	}
}

void InfarctedBody::enableOtherHamster() {
	if (otherHamster != nullptr) {
		otherHamster->getComponent<Movement>()->setActive(true);
		otherHamster->getComponent<LightAttack>()->setActive(true);
		otherHamster->getComponent<StrongAttack>()->setActive(true);

	}
}

void InfarctedBody::deleteTexture() {
	if (tx_ != nullptr) {
		tx_->setActive(false);
		entity_->getMngr()->refreshUIObjects();
		delete tx_; tx_ = nullptr;
	}
}