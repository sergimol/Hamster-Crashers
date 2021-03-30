// This file is part of the course TPV2@UCM - Samir Genaim

#include "../game/Game.h"

#include "../components/Transform.h"

//bool Entity::operator< ( Entity* a) {
//	std::cout << "MENOR QUE" << std::endl;
//	if (a->hasComponent<Transform>() && this->hasComponent<Transform>())
//		return (a->getComponent<Transform>()->getPos().getY() <= this->getComponent<Transform>()->getPos().getY());
//	return false;
//}


//bool operator< (Entity* a, Entity* b) {
//	std::cout << "MENOR QUE" << std::endl;
//	if (a->hasComponent<Transform>() && b->hasComponent<Transform>())
//		return (a->getComponent<Transform>()->getPos().getY() <= b->getComponent<Transform>()->getPos().getY());
//	return false;
//}

//bool Entity::comparador (Entity* a, Entity* b) {
//	std::cout << "MENOR QUE" << std::endl;
//	if (a->hasComponent<Transform>() && b->hasComponent<Transform>())
//		return (a->getComponent<Transform>()->getPos().getY() <= b->getComponent<Transform>()->getPos().getY());
//	return false;
//}

//bool operator< (Entity& a, Entity& b) {
//	std::cout << "MENOR QUE" << std::endl;
//		if (a.hasComponent<Transform>() && b.hasComponent<Transform>())
//			return (a.getComponent<Transform>()->getPos().getY() <= b.getComponent<Transform>()->getPos().getY());
//		return false;
//}