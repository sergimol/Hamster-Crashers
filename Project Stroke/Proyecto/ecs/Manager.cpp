// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"

#include <algorithm>

Manager::Manager() {
}

Manager::~Manager() {
	for (auto e : entities_) {
		delete e; e = nullptr;
	}
	for (auto t : tiles_) {
		delete t; t = nullptr;
	}
	for (auto tC : tileCollider_) {
		delete tC; tC = nullptr;
	}
	for (auto mH : mapHeights_) {
		delete mH; mH = nullptr;
	}
}

void Manager::refresh() {
	// remove dead entities from the list of entities
	entities_.erase( //
		std::remove_if( //
			entities_.begin(), //
			entities_.end(), //
			[](const Entity* e) { //
				if (e->isActive()) {
					return false;
				}
				else {
					delete e;
					return true;
				}
			}), //
		entities_.end());
}

void Manager::update() {
	auto n = entities_.size();
	for (auto i = 0u; i < n; i++)
		entities_[i]->update();
}

void Manager::render() {
	//RENDERIZA TILES
	auto w = tiles_.size();
	for (auto i = 0u; i < w; i++)
		tiles_[i]->render();

	//RENDERIZA ENTIDADES
	auto n = entities_.size();
	for (auto i = 0u; i < n; i++)
		entities_[i]->render();
}
