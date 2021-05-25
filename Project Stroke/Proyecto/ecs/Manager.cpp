// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"
#include "../components/EnemyMother.h"

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
	for (auto mB : menuBgs_) {
		delete mB; mB = nullptr;
	}
	for (auto mT : traps_) {
		delete mT; mT = nullptr;
	}
	for (auto mN : menus_) {
		delete mN; mN = nullptr;
	}
}

void Manager::refresh() {
	if(getHandler<Mother>()->getComponent<EnemyMother>() != nullptr)
		getHandler<Mother>()->getComponent<EnemyMother>()->refreshLists();

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

	//TODO lo ahgo aqui porque no las estoy poniendo en entidades
	refreshWavesObjects();
}

void Manager::update() {
	auto n = entities_.size();
	for (auto i = 0u; i < n; i++)
		entities_[i]->update();


	auto t = traps_.size();
	for (auto i = 0u; i < t; i++)
		traps_[i]->update();

	auto b = bgs_.size();
	for (auto i = 0u; i < b; i++)
		bgs_[i]->update();

	auto f = fgs_.size();
	for (auto i = 0u; i < f; i++)
		fgs_[i]->update();

	auto m = menus_.size();
	for (auto i = 0u; i < m; i++)
		menus_[i]->update();


	auto w = wavesObjects_.size();
	for (auto i = 0u; i < w; i++)
		wavesObjects_[i]->update();
}

void Manager::render() {
	//RENDERIZA FONDOS
	auto s = bgs_.size();
	for (auto i = 0u; i < s; i++)
		bgs_[i]->render();

	//RENDERIZA FONDOS
	s = menuBgs_.size();
	for (auto i = 0u; i < s; i++) {
		if (menuBgs_[i]->isActive())
			menuBgs_[i]->render();
	}

	//RENDERIZA TILES
	s = tiles_.size();
	for (auto i = 0u; i < s; i++)
		tiles_[i]->render();

	//RENDERIZA TRAMPAS (EN EL SUELO)
	s = traps_.size();
	for (auto i = 0u; i < s; i++)
		traps_[i]->render();


	//RENDERIZA ENTIDADES
	s = entities_.size();
	for (auto i = 0u; i < s; i++)
		entities_[i]->render();

	//RENDERIZA POR DELANTE
	s = fgs_.size();
	for (auto i = 0u; i < s; i++)
		fgs_[i]->render();

	//RENDER DE UI (MINIJUEGO DE INFARTO)
	s = uiObjects_.size();
	for (auto i = 0u; i < s; i++) {
		if(uiObjects_[i]->isActive())
			uiObjects_[i]->render();
	}

	s = menus_.size();
	for (auto i = 0u; i < s; i++)
		menus_[i]->render();

	s = wavesObjects_.size();
	for (auto i = 0u; i < s; i++)
		wavesObjects_[i]->render();
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


	auto wo = wavesObjects_.size();
	for (auto i = 0u; i < wo; i++)
		wavesObjects_[i]->resume();
}
