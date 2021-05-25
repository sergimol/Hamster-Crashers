#include "GetItem.h"
#include "Item.h"
#include "EntityAttribs.h"
#include "SoundManager.h"
#include "GameStates.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void GetItem::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void GetItem::update() {
	if (state_->getState() == GameStates::RUNNING) {
		auto& ents = entity_->getMngr()->getItems();

		cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
		for (Entity* e : ents) {
			//Si la entidad es un item...
				//Cogemos el transform del item
			auto eTR = e->getComponent<Transform>();

			//Creamos nuestroRect
			SDL_Rect rH = tr_->getRectCollide();

			SDL_Rect rI = eTR->getRectCollide();

			//Y comprobamos si colisiona
			if (Collisions::collides(Vector2D(rH.x, rH.y), rH.w, rH.h, Vector2D(rI.x, rI.y), rI.w, rI.h)) {
				//Comprobamos el tipo
				switch (e->getComponent<Item>()->getItem()) {
				case ItemType::Apple:
					entity_->getComponent<EntityAttribs>()->heal(APPLEHP);
					break;
				case ItemType::Cheese:
					this->entity_->getComponent<EntityAttribs>()->heal(CHEESE);
					break;
				default:
					break;
				}
				entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("eatItem");

				e->setActive(false);
				entity_->getMngr()->refreshItems();
			}
		}
	}
}