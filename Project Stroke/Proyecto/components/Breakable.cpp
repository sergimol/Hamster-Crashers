#include "Breakable.h"
#include "../ecs/Manager.h"

void Breakable::init() {
	//Incluye a su entidad directamente en obst�culos
	entity_->getMngr()->getObstacles().push_back(entity_);
}

void Breakable::hit() {

}
