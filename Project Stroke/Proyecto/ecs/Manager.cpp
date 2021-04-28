// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"

#include <algorithm>
#include "../utils/checkML.h"

Manager::Manager() {
}

Manager::~Manager() {
	for (auto e : entities_) {
		delete e; e = nullptr;
	}
	for (auto t : tiles_) {
		delete t; t = nullptr;
	}
	for (auto mH : mapHeights_) {
		delete mH; mH = nullptr;
	}
	for (auto bG : bgs_) {
		delete bG; bG = nullptr;
	}
	for (auto fG : fgs_) {
		delete fG; fG = nullptr;
	}
	for (auto mN : menus_) {
		delete mN; mN = nullptr;
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
	
	auto b = bgs_.size();
	for (auto i = 0u; i < b; i++)
		bgs_[i]->update();

	auto f = fgs_.size();
	for (auto i = 0u; i < f; i++)
		fgs_[i]->update();

	auto m = menus_.size();
	for (auto i = 0u; i < m; i++)
		menus_[i]->update();
}

void Manager::render() {
	//RENDERIZA FONDOS
	auto b = bgs_.size();
	for (auto i = 0u; i < b; i++)
		bgs_[i]->render();

	//RENDERIZA TILES
	auto w = tiles_.size();
	for (auto i = 0u; i < w; i++)
		tiles_[i]->render();

	//RENDERIZA ENTIDADES
	auto n = entities_.size();
	for (auto i = 0u; i < n; i++)
		entities_[i]->render();

	//RENDERIZA POR DELANTE
	auto f = fgs_.size();
	for (auto i = 0u; i < f; i++)
		fgs_[i]->render();

	auto m = menus_.size();
	for (auto i = 0u; i < m; i++)
		menus_[i]->render();
}

void Manager::resume() {
	auto n = entities_.size();
	for (auto i = 0u; i < n; i++)
		entities_[i]->resume();

	auto b = bgs_.size();
	for (auto i = 0u; i < b; i++)
		bgs_[i]->resume();

	auto f = fgs_.size();
	for (auto i = 0u; i < f; i++)
		fgs_[i]->resume();
}
