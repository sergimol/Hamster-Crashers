// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <initializer_list>
#include <vector>
#include <list>

#include "ecs.h"
#include "Entity.h"
#include "System.h"

class Manager {
public:

	Manager();
	virtual ~Manager();

	// entities
	Entity* addEntity() {
		Entity *e = new Entity(this);
		if (e != nullptr) {
			e->resetGroups();
			entities_.emplace_back(e);
		}
		return e;
	}

	Entity* addTile() {
		Entity* e = new Entity(this);
		if (e != nullptr) {
			e->resetGroups();
			tiles_.emplace_back(e);
		}
		return e;
	}
	
	Entity* addBackGround() {
		Entity* e = new Entity(this);
		if (e != nullptr) {
			e->resetGroups();
			bgs_.emplace_back(e);
		}
		return e;
	}

	Entity* addFrontGround() {
		Entity* e = new Entity(this);
		if (e != nullptr) {
			e->resetGroups();
			fgs_.emplace_back(e);
		}
		return e;
	}

	Entity* addMenu() {
		Entity* e = new Entity(this);
		if (e != nullptr) {
			e->resetGroups();
			menus_.emplace_back(e);
		}
		return e;
	}

	Entity* addMapHeight() {
		Entity* e = new Entity(this);
		if (e != nullptr) {
			e->resetGroups();
			mapHeights_.emplace_back(e);
		}
		return e;
	}

	// handlers
	template<typename T>
	inline void setHandler(Entity *e) {
		hdlrs_[ecs::hdlrIdx<T>] = e;
	}

	template<typename T>
	inline Entity* getHandler() {
		return hdlrs_[ecs::hdlrIdx<T>];
	}

	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&...args) {
		T* s = new T(std::forward<Ts>(args)...);
		sys_[ecs::sysIdx<T>] = std::unique_ptr<System>(s);
		s->setMngr(this);
		s->init();
		return s;
	}

	template<typename T>
	inline T* getSystem() {
		return static_cast<T*>(sys_[ecs::sysIdx<T>].get());
	}

	inline std::vector<Entity*>& getEntities() {
		return entities_;
	}

	template<typename T>
	inline void setActive(Entity* e, bool state) {
		e->active_ = state;
	}
	
	template<typename T>
	inline bool isActive(Entity* e) {
		return e->active_;
	}

	void resetGroups(Entity* e) {
		e->groups_.reset();
	}
	
	template<typename GT>
	inline void setGroup(Entity* e, bool state) {
		assert(e != nullptr);
		e->groups_[ecs::grpIdx<GT>] = state;
	}
	
	template<typename GT>
	inline bool hasGroup(Entity* e) {
		assert(e != nullptr);
		return e->groups_[ecs::grpIdx<GT>];
	}

	template<typename T, typename ...Ts>
	inline T* addComponent(Entity* e, Ts &&...args) {
		T* c = new T(std::forward<Ts>(args)...);
		e->cmpArray_[ecs::cmpIdx<T>] = std::unique_ptr<Component>(c);
		return c;
	}
	
	template<typename T>
	inline T* getComponent(Entity* e) {
		return static_cast<T*>(e->cmpArray_[ecs::cmpIdx<T>].get());
	}
	
	template<typename T>
	inline bool hasComponent(Entity* e) {
		return e->cmpArray_[ecs::cmpIdx<T>].get() != nullptr;
	}
	
	template<typename T>
	inline void removeComponent(Entity* e) {
		e->cmpArray_[ecs::cmpIdx<T>] = nullptr;
	}

	//PARA LAS AGRUPACIONES
	inline std::vector<Entity*>& getPlayers() {
		return players_;
	}

	inline std::vector<Entity*>& getEnemies() {
		return enemies_;
	}

	inline std::vector<Entity*>& getObstacles() {
		return obstacles_;
	}
	
	inline std::vector<Entity*>& getTraps() {
		return traps_;
	}

	inline std::vector<Entity*>& getTiles() {
		return tiles_;
	}
	
	inline std::vector<Entity*>& getBgs() {
		return bgs_;
	}

	inline std::vector<Entity*>& getFgs() {
		return fgs_;
	}
	
	inline std::vector<Entity*>& getMapH() {
		return mapHeights_;
	}

	inline std::vector<Entity*>& getDeadBodies() {
		return deadBodies_;
	}

	inline std::vector<Entity*>& getItems() {
		return items_;
	}

	void update();
	void render();
	void refresh();
	void resume();

	void refreshDeadBodies() {
		deadBodies_.erase( //
			std::remove_if( //
				deadBodies_.begin(), //
				deadBodies_.end(), //
				[](const Entity* e) { //
					return !e->isActive();
				}), //
			deadBodies_.end());
	}

	void refreshEnemies() {
		enemies_.erase( //
			std::remove_if( //
				enemies_.begin(), //
				enemies_.end(), //
				[](const Entity* e) { //
					return !e->isActive();
				}), //
			enemies_.end());
	}

	void refreshPlayers() {
		players_.erase( //
			std::remove_if( //
				players_.begin(), //
				players_.end(), //
				[](const Entity* e) { //
					return !e->isActive();
				}), //
			players_.end());
	}

	void refreshObstacles() {
		obstacles_.erase( //
			std::remove_if( //
				obstacles_.begin(), //
				obstacles_.end(), //
				[](const Entity* e) { //
					return !e->isActive();
				}), //
			obstacles_.end());
	}

	void refreshItems() {
		items_.erase( //
			std::remove_if( //
				items_.begin(), //
				items_.end(), //
				[](const Entity* e) { //
					return !e->isActive();
				}), //
			items_.end());
	}

	void refreshTraps() {
		traps_.erase( //
			std::remove_if( //
				traps_.begin(), //
				traps_.end(), //
				[](const Entity* e) { //
					return !e->isActive();
				}), //
			traps_.end());
	}

private:
	std::vector<Entity*> entities_;
	std::vector<Entity*> tiles_;
	std::vector<Entity*> mapHeights_;
	std::vector<Entity*> bgs_;
	std::vector<Entity*> fgs_;
	std::vector<Entity*> menus_;

	std::array<Entity*, ecs::maxHdlr> hdlrs_;
	std::array<std::unique_ptr<System>, ecs::maxSystem> sys_;

	//AGRUPACIONES DE ENTIDADES
	std::vector<Entity*> players_; // vector de jugadores
	std::vector<Entity*> enemies_; // EJEMPLO
	std::vector<Entity*> obstacles_; // EJEMPLO
	std::vector<Entity*> traps_; // EJEMPLO
	std::vector<Entity*> deadBodies_;
	std::vector<Entity*> items_;
};

