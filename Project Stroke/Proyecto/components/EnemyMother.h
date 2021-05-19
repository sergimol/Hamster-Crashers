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
		for (int i = 0; i < numPlayers; i++) {
			objetivesList.at(i)->ambushing.clear();
			objetivesList.at(i)->atacking.clear();
			objetivesList.at(i)->strongAmbushing.clear();
			objetivesList.at(i)->strongAtacking.clear();
			 delete objetivesList.at(i);
		}
		objetivesList.clear();
		waiting.clear();
		strongWaiting.clear();
	};

	void init() override;
	void update() override;
	virtual void onEnable() override;
	virtual void onDisable() override;

	void addObjetive(Entity* hamster);

	void addEnemy(Entity* e) {
		if (e->hasComponent<EnemyStrongAttack>()) {
			strongWaiting.push_back(e);
		}
		else waiting.push_back(e);
		numEnemies++;
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
	void changeFromAttackToAmbush(int hamid, std::list<Entity*>::iterator it);
	//
	void removeFromAttackList(int hamid, std::list<Entity*>::iterator it, bool strong);
	void removeFromAmbushList(int hamid, std::list<Entity*>::iterator it, bool strong);
	
	//No hay removefromwaiting, porque en un principio eso no deberia de ser posible ya que cuando estan en ese estado los players estan muertos

	/*Vacia todas las listas y las pone en waiting (iddle)*/
	void cleanListToWaiting();
	void cleanListHam(int hamId);
	void cleanListHamAmbush(int hamId);
	void cleanListHamAttacking(int hamId);


	void refreshLists() {
		for (int i = 0; i < numPlayers; i++) {

			// remove dead entities from the list of entities
			objetivesList.at(i)->ambushing.erase( //
				std::remove_if( //
					objetivesList.at(i)->ambushing.begin(), //
					objetivesList.at(i)->ambushing.end(), //
					[](const Entity* e) { //
						if (e->isActive()) {
							return false;
						}
						else {
							delete e;
							return true;
						}
					}), //
				objetivesList.at(i)->ambushing.end());

			// remove dead entities from the list of entities
			objetivesList.at(i)->atacking.erase( //
				std::remove_if( //
					objetivesList.at(i)->atacking.begin(), //
					objetivesList.at(i)->atacking.end(), //
					[](const Entity* e) { //
						if (e->isActive()) {
							return false;
						}
						else {
							delete e;
							return true;
						}
					}), //
				objetivesList.at(i)->atacking.end());

			// remove dead entities from the list of entities
			objetivesList.at(i)->strongAmbushing.erase( //
				std::remove_if( //
					objetivesList.at(i)->strongAmbushing.begin(), //
					objetivesList.at(i)->strongAmbushing.end(), //
					[](const Entity* e) { //
						if (e->isActive()) {
							return false;
						}
						else {
							delete e;
							return true;
						}
					}), //
				objetivesList.at(i)->strongAmbushing.end());

			// remove dead entities from the list of entities
			objetivesList.at(i)->strongAtacking.erase( //
				std::remove_if( //
					objetivesList.at(i)->strongAtacking.begin(), //
					objetivesList.at(i)->strongAtacking.end(), //
					[](const Entity* e) { //
						if (e->isActive()) {
							return false;
						}
						else {
							delete e;
							return true;
						}
					}), //
				objetivesList.at(i)->strongAtacking.end());

			objetivesList.at(i)->strongAtacking.clear();
		}
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

	list<Entity*> waiting; //es donde se vana  meter inicialmente a todos
	list<Entity*> strongWaiting; //es donde se vana  meter inicialmente a todos
	std::map<int, Objetivo*> objetivesList;
	int numPlayers;
	int numEnemies;

	GameStates* state_;
};