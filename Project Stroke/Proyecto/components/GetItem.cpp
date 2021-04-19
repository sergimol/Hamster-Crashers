#include "GetItem.h"
#include "Item.h"
#include "EntityAttribs.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void GetItem::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void GetItem::update() {
	auto& ents = entity_->getMngr()->getItems();

	cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
	for (Entity* e : ents) {
		//Si la entidad es un item...
			//Cogemos el transform del item
		auto eTR = e->getComponent<Transform>();

		//Creamos nuestroRect
		Vector2D newPos = Vector2D(eTR->getPos().getX() - cam.x, eTR->getPos().getY() - cam.y);

		Vector2D otherPos = Vector2D(tr_->getPos().getX() - cam.x, tr_->getPos().getY() - cam.y);

		//Y comprobamos si colisiona
		if (Collisions::collides(otherPos, tr_->getW(), tr_->getH(), newPos, eTR->getW(), eTR->getH())) {
			//Comprobamos el tipo
			switch (e->getComponent<Item>()->getItem()) {
			case ItemType::Apple:
				this->entity_->getComponent<EntityAttribs>()->heal(APPLEHP);
				break;
			case ItemType::WaterMelon:
				this->entity_->getComponent<EntityAttribs>()->heal(WATERHP);
				break;
			case ItemType::Nut:
				this->entity_->getComponent<EntityAttribs>()->heal(NUTHP);
				break;
			default:
				break;
			}
			e->setActive(false);
			entity_->getMngr()->refreshItems();
		}
	}
}