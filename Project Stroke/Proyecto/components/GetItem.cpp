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
	auto& ents = entity_->getMngr()->getEntities();

	for (Entity* e : ents) {
		//Si la entidad es un item...
		if (e->hasGroup<Item_group>()) {
			//Cogemos el transform del item
			auto eTR = e->getComponent<Transform>();

			//Creamos nuestroRect
			SDL_Rect rectPlayer;
			rectPlayer.h = tr_->getH();
			rectPlayer.w = tr_->getW();
			rectPlayer.x = tr_->getPos().getX() - Game::camera_.x;
			rectPlayer.y = tr_->getPos().getY() - Game::camera_.y;

			//Creamos su Rect
			SDL_Rect rectItem;
			rectItem.h = eTR->getH();
			rectItem.w = eTR->getW();
			rectItem.x = eTR->getPos().getX() - Game::camera_.x;
			rectItem.y = eTR->getPos().getY() - Game::camera_.y;

			//Y comprobamos si colisiona
			if (SDL_HasIntersection(&rectPlayer, &rectItem)) {
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
			}
		}
	}
}