#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>
#include <cmath>
#include "../utils/checkML.h"

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
//#include "../ecs/Behavior.h"

#include "Transform.h"
#include "HamsterStateMachine.h"
#include "Animator.h"
#include "EntityAttribs.h"
#include "MovementSimple.h"
#include "EnemyAttack.h"
#include "EnemyStrongAttack.h"
#include "FirstBossAttack.h"
#include "Behavior.h"

struct Objetivo {
	Entity* hamster;
	list<Entity*> atacking;
	list<Entity*> ambushing;
	list<Entity*> strongAtacking;
	list<Entity*> strongAmbushing;
	Transform* hmTR_;
	HamsterStateMachine* hmSt_;
};

class EnemyMother : public Component {
protected:
public:
	EnemyMother();
	virtual ~EnemyMother() {
		for (int i = 0; i < numPlayers_; i++) {
			objetivesList_.at(i)->ambushing.clear();
			objetivesList_.at(i)->atacking.clear();
			objetivesList_.at(i)->strongAmbushing.clear();
			objetivesList_.at(i)->strongAtacking.clear();
			 delete objetivesList_.at(i);
		}
		objetivesList_.clear();
		waiting_.clear();
		strongWaiting_.clear();
	};

	void init() override;
	void update() override;
	virtual void onEnable() override;
	virtual void onDisable() override;

	void addObjetive(Entity* hamster);

	void addEnemy(Entity* e) {
		if (e->hasComponent<EnemyStrongAttack>()) {
			strongWaiting_.push_back(e);
		}
		else waiting_.push_back(e);
		numEnemies_++;
	}
	/*
	Recoge a los enemigos de las listas ambush y los pone en waiting para luego volver a reorganizarlos a todos (nuevos y viejos),
	lo ideal serai llamarlo cuando un hamster muere o revive
	*/
	void reOrderEnemies(); 
	/*
	pone a los enemigos de waiting en las listas ambush de forma equitativa
	*/
	void asingEnemies();
	void orderAttack();
	/*Change de entiity from attacking list to ambush list when stunned or out of combat*/
	void changeFromAttackToAmbush(int hamid, Entity* e);
	//
	void removeFromAttackList(int hamid, Entity* e, bool strong);
	void removeFromAmbushList(int hamid, Entity* e, bool strong);
	
	//No hay removefromwaiting, porque en un principio eso no deberia de ser posible ya que cuando estan en ese estado los players estan muertos

	/*Vacia todas las listas y las pone en waiting (iddle)*/
	void cleanListToWaiting();
	void cleanListHam(int hamId);
	void cleanListHamAmbush(int hamId);
	void cleanListHamAttacking(int hamId);


	void refreshLists() {
		for (int i = 0; i < numPlayers_; i++) {

			// remove dead entities from the list of entities
			objetivesList_.at(i)->ambushing.erase( //
				std::remove_if( //
					objetivesList_.at(i)->ambushing.begin(), //
					objetivesList_.at(i)->ambushing.end(), //
					[](const Entity* e) { //
						return !e->isActive();
					}), //
				objetivesList_.at(i)->ambushing.end());

			// remove dead entities from the list of entities
			objetivesList_.at(i)->atacking.erase( //
				std::remove_if( //
					objetivesList_.at(i)->atacking.begin(), //
					objetivesList_.at(i)->atacking.end(), //
					[](const Entity* e) { //
						return !e->isActive();
					}), //
				objetivesList_.at(i)->atacking.end());

			// remove dead entities from the list of entities
			objetivesList_.at(i)->strongAmbushing.erase( //
				std::remove_if( //
					objetivesList_.at(i)->strongAmbushing.begin(), //
					objetivesList_.at(i)->strongAmbushing.end(), //
					[](const Entity* e) { //
						return !e->isActive();
					}), //
				objetivesList_.at(i)->strongAmbushing.end());

			// remove dead entities from the list of entities
			objetivesList_.at(i)->strongAtacking.erase( //
				std::remove_if( //
					objetivesList_.at(i)->strongAtacking.begin(), //
					objetivesList_.at(i)->strongAtacking.end(), //
					[](const Entity* e) { //
						return !e->isActive();
					}), //
				objetivesList_.at(i)->strongAtacking.end());

			//objetivesList_.at(i)->strongAtacking.clear();
			
		}
			// remove dead entities from the list of entities
			waiting_.erase( //
				std::remove_if( //
					waiting_.begin(), //
					waiting_.end(), //
					[](const Entity* e) { //
						return !e->isActive();
					}), //
				waiting_.end());

			// remove dead entities from the list of entities
			strongWaiting_.erase( //
				std::remove_if( //
					strongWaiting_.begin(), //
					strongWaiting_.end(), //
					[](const Entity* e) { //
						return !e->isActive();
					}), //
				strongWaiting_.end());

	}


	//este me soluciona los problemas rapido y me ahorra usar lso demas xd pero se van a quedar igual porque ya los escribí
	Entity* getEntity() {
		return entity_;
	}

protected: //ahora mismo solo funcionan como private
	//hamster al que va a perseguir* en verdad solo queremos la propiedad tranform ahora mismo pero
	// mas adelante es posible que nos interese conocer estados o componentes oportunos, por ahora no ahce daño verdad¿?¿
	std::vector<Entity*> hamsters_; //same as below
	std::vector<Entity*> enemys_; //realmente no lo necesitamos pero esta bien tenerlo por si acaso

	list<Entity*> waiting_; //es donde se vana  meter inicialmente a todos
	list<Entity*> strongWaiting_; //es donde se vana  meter inicialmente a todos
	std::map<int, Objetivo*> objetivesList_;
	int numPlayers_;
	int numEnemies_;

	GameStates* state_;
};