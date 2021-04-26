#include "EnemyMother.h"
#include "FollowPLayer.h"
#include "AmbushPlayer.h"
#include "iddleEnemy.h"

EnemyMother::EnemyMother() : numPlayers(0), numEnemies(0) {}

void EnemyMother::init() { 
	hamsters_ = entity_->getMngr()->getPlayers();
	enemys_ = entity_->getMngr()->getEnemies();

}

void EnemyMother::addObjetive(Entity* hamster) {
	auto a = new Objetivo;
	objetivesList.insert({numPlayers++, a});
	//establecer los valores de objetivo
	a->hamster = hamster;
	//es popsible que sean prescindibles
	a->hmTR_ = hamster->getComponent<Transform>();
	a->hmSt_ = hamster->getComponent<HamsterStateMachine>();
}

//los anyade a las listas ambush
void EnemyMother::asingEnemies() {
	auto n = waiting.size();
	
	for (auto i = 0u; i < n; i++) {
		// encontrar player alive
		int objetive = i % numPlayers;
		while (objetive < numPlayers && objetivesList.at(objetive)->hmSt_->cantBeTargeted()) {
			objetive++;
		}
		if (objetive < numPlayers) {

			//no hay players alive no hace falta reasignar
			//
			//
			objetivesList.at(objetive)->ambushing.push_back(waiting.front());
			waiting.pop_front();
			// poner las entitades en behavior ambush
			objetivesList.at(objetive)->ambushing.back()->getComponent<EnemyBehaviour>()->SetBehavior(new AmbushPlayer());
			//darle el iterador y el hamster id a behavior porque lo va a necesitar
			objetivesList.at(objetive)->ambushing.back()->getComponent<EnemyBehaviour>()->setHamId
				(objetive, --objetivesList.at(objetive)->ambushing.end(), 'b');
		}

	}
}

//recoge ambush en waiting y los reparte
void EnemyMother::reOrderEnemies() {

	for (int i = 0u; i < numPlayers; i++) {
		cleanListHamAmbush(i);
	}
	asingEnemies();
}

//ordena en cada update que quien pueda atacar ataque
void EnemyMother::orderAttack() {

	for (int i = 0u; i < numPlayers; i++) {

		auto z = objetivesList.at(i)->atacking.size();
		for (int y = z; y < 2; y++) {
			//se puede añadir
			auto n = objetivesList.at(i)->ambushing.size();
			if (n != 0) { // hay enemigos disponibles
				objetivesList.at(i)->atacking.push_back(objetivesList.at(i)->ambushing.front());
				objetivesList.at(i)->ambushing.pop_front();
				//TODO poner las entitades en behavior attack correspondiente
				objetivesList.at(i)->atacking.back()->getComponent<EnemyBehaviour>()->SetBehavior(new FollowPlayer());
				//darle el iterador y el hamster id a behavior porque lo va a necesitar
				objetivesList.at(i)->atacking.back()->getComponent<EnemyBehaviour>()->setHamId
					(i, --objetivesList.at(i)->atacking.end(), 'a');
			}
		}
		
		//objetivesList.at(i)->atacking.erase(objetivesList.at(i)->atacking.begin());
		//std::list<Entity*>::iterator y
	}
}

void EnemyMother::cleanListToWaiting() {
	for (int i = 0u; i < numPlayers; i++) {
		cleanListHam(i);
	}
}

//pone a lso enemigos en las listas de este hamster en la de waiting (iddle)
void EnemyMother::cleanListHam(int i) {
	cleanListHamAmbush(i);
	cleanListHamAttacking(i);
}
void EnemyMother::cleanListHamAmbush(int i) {
	auto n = objetivesList.at(i)->ambushing.size();
	for (auto y = 0u; y < n; y++) {
		waiting.push_back(objetivesList.at(i)->ambushing.back());
		objetivesList.at(i)->ambushing.pop_back();
		//Tponer las entitades en behavior iddle
		waiting.back()->getComponent<EnemyBehaviour>()->SetBehavior(new IddleEnemy());
	}
}
void EnemyMother::cleanListHamAttacking(int i) {
	auto n = objetivesList.at(i)->atacking.size();
	for (auto y = 0u; y < n; y++) {
		waiting.push_back(objetivesList.at(i)->atacking.back());
		objetivesList.at(i)->atacking.pop_back();
		//poner las entitades en behavior iddle
		waiting.back()->getComponent<EnemyBehaviour>()->SetBehavior(new IddleEnemy());
	}
}

/*Cambia a un eneigo en concreto de attack to ambush*/
void EnemyMother::changeFromAttackToAmbush(int hamid, std::list<Entity*>::iterator it) {
	
	
	//coloca el bicho en ambush al final
	objetivesList.at(hamid)->ambushing.push_back(*it);
	//lo saca de la lista attacking
	removeFromAttackList(hamid, it);

	//poner las entitades en behavior attack correspondiente
	objetivesList.at(hamid)->ambushing.back()->getComponent<EnemyBehaviour>()->SetBehavior(new AmbushPlayer());
	//darle el iterador y el hamster id a behavior porque lo va a necesitar
	objetivesList.at(hamid)->ambushing.back()->getComponent<EnemyBehaviour>()->setHamId
	(hamid, --objetivesList.at(hamid)->ambushing.end(), 'b');
	//yasta

}


void EnemyMother::removeFromAttackList(int hamid, std::list<Entity*>::iterator it) {
	
	it = objetivesList.at(hamid)->atacking.erase(it); //si se ha morido se quita, no se cambia ni nada, la lista se actualiza sola
}

void EnemyMother::removeFromAmbushList(int hamid, std::list<Entity*>::iterator it) {
	it = objetivesList.at(hamid)->ambushing.erase(it); //si se ha morido se quita, no se cambia ni nada, la lista se actualiza sola
}

void EnemyMother::update() {
	asingEnemies();
	orderAttack();

	//no queria hacerlo asi pero es para salir del truyo, (no localizo la parte exacta en al que un hamster muere y poder identificarlo), oi si coño que coño
}


void EnemyMother::onEnable() {
}

void EnemyMother::onDisable() {
}