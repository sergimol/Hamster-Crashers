#include "EnemyMother.h"
#include "FollowPLayer.h"
#include "AmbushPlayer.h"
#include "iddleEnemy.h"
#include "StrongFollowPLayer.h"

EnemyMother::EnemyMother() : numPlayers(0), numEnemies(0), state_(nullptr) {}

void EnemyMother::init() { 
	hamsters_ = entity_->getMngr()->getPlayers();
	enemys_ = entity_->getMngr()->getEnemies();

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
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
	
	//reparte los enemigos normales
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
	//repartir los enemigos strong
	n = strongWaiting.size();
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
			objetivesList.at(objetive)->strongAmbushing.push_back(strongWaiting.front());
			strongWaiting.pop_front();
			// poner las entitades en behavior ambush
			objetivesList.at(objetive)->strongAmbushing.back()->getComponent<EnemyBehaviour>()->SetBehavior(new AmbushPlayer());
			//darle el iterador y el hamster id a behavior porque lo va a necesitar
			objetivesList.at(objetive)->strongAmbushing.back()->getComponent<EnemyBehaviour>()->setHamId
			(objetive, --objetivesList.at(objetive)->strongAmbushing.end(), 'b');
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
		//enemigos normales
		auto z = objetivesList.at(i)->atacking.size();
		for (int y = z; y < 2; y++) {
			//se puede a�adir
			if (!objetivesList.at(i)->ambushing.empty()) { // hay enemigos disponibles
				objetivesList.at(i)->atacking.push_back(objetivesList.at(i)->ambushing.front());
				objetivesList.at(i)->ambushing.pop_front();
				//TODO poner las entitades en behavior attack correspondiente
				objetivesList.at(i)->atacking.back()->getComponent<EnemyBehaviour>()->SetBehavior(new FollowPlayer());
				//darle el iterador y el hamster id a behavior porque lo va a necesitar
				objetivesList.at(i)->atacking.back()->getComponent<EnemyBehaviour>()->setHamId
					(i, --objetivesList.at(i)->atacking.end(), 'a');
			}
		}
		//enemigos strong
		if (objetivesList.at(i)->strongAtacking.empty()) {
			//se puede a�adir
			if (!objetivesList.at(i)->strongAmbushing.empty()) { // hay enemigos disponibles
				objetivesList.at(i)->strongAtacking.push_back(objetivesList.at(i)->strongAmbushing.front());
				objetivesList.at(i)->strongAmbushing.pop_front();
				//TODO poner las entitades en behavior attack correspondiente
				objetivesList.at(i)->strongAtacking.back()->getComponent<EnemyBehaviour>()->SetBehavior(new StrongFollowPlayer());
				//darle el iterador y el hamster id a behavior porque lo va a necesitar
				objetivesList.at(i)->strongAtacking.back()->getComponent<EnemyBehaviour>()->setHamId
				(i, --objetivesList.at(i)->strongAtacking.end(), 'a');
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
	//enemigos normales
	auto n = objetivesList.at(i)->ambushing.size();
	for (auto y = 0u; y < n; y++) {
		waiting.push_back(objetivesList.at(i)->ambushing.back());
		objetivesList.at(i)->ambushing.pop_back();
		//Tponer las entitades en behavior iddle
		waiting.back()->getComponent<EnemyBehaviour>()->SetBehavior(new IddleEnemy());
	}
	//enemigos fuertes //TODO
	n = objetivesList.at(i)->strongAmbushing.size();
	for (auto y = 0u; y < n; y++) {
		waiting.push_back(objetivesList.at(i)->strongAmbushing.back());
		objetivesList.at(i)->strongAmbushing.pop_back();
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
	n = objetivesList.at(i)->strongAtacking.size();
	for (auto y = 0u; y < n; y++) {
		waiting.push_back(objetivesList.at(i)->strongAtacking.back());
		objetivesList.at(i)->strongAtacking.pop_back();
		//poner las entitades en behavior iddle
		waiting.back()->getComponent<EnemyBehaviour>()->SetBehavior(new IddleEnemy());
	}


	//TODO
	//esot es el apaño de mierda que tenemos que hacer porque resulta que estamos desintegrando de la relaidad al hamnster y no podemos comprobar su estado jijiji me caog end ios
	//ME CAGO EN DIOS QUE SI PONGO ESTO PARA HACER LA MEIRDA EL APAÑO NO PUEDO USAR ESTE METODO PARA CONTROLAR EL INFARTO PORQUE CLARO LEUGO NO QUEDAN HAMSTER AJAJAJ
	//TODO TODO TODO TODO PERO TODFO EL PUTO MUNDO TODO TODO TODO TODO TODO TODO TODO TOD O

	//objetivesList.erase(i);
	//numPlayers--;
}

/*Cambia a un eneigo en concreto de attack to ambush*/
void EnemyMother::changeFromAttackToAmbush(int hamid, std::list<Entity*>::iterator it) {
	
	if (!(*it)->hasComponent<StrongAttack>()) {

	
		//coloca el bicho en ambush al final
		objetivesList.at(hamid)->ambushing.push_back(*it);
		//lo saca de la lista attacking
		removeFromAttackList(hamid, it, false);

		//poner las entitades en behavior attack correspondiente
		objetivesList.at(hamid)->ambushing.back()->getComponent<EnemyBehaviour>()->SetBehavior(new AmbushPlayer());
		//darle el iterador y el hamster id a behavior porque lo va a necesitar
		objetivesList.at(hamid)->ambushing.back()->getComponent<EnemyBehaviour>()->setHamId
		(hamid, --objetivesList.at(hamid)->ambushing.end(), 'b');
		//yasta
	}
	else {

		//coloca el bicho en ambush al final
		objetivesList.at(hamid)->strongAmbushing.push_back(*it);
		//lo saca de la lista attacking
		removeFromAttackList(hamid, it, true);

		//poner las entitades en behavior attack correspondiente
		objetivesList.at(hamid)->strongAmbushing.back()->getComponent<EnemyBehaviour>()->SetBehavior(new AmbushPlayer());
		//darle el iterador y el hamster id a behavior porque lo va a necesitar
		objetivesList.at(hamid)->strongAmbushing.back()->getComponent<EnemyBehaviour>()->setHamId
		(hamid, --objetivesList.at(hamid)->strongAmbushing.end(), 'b');
		//yasta
	}

}


void EnemyMother::removeFromAttackList(int hamid, std::list<Entity*>::iterator it, bool strong) {
	if (!strong) 
		objetivesList.at(hamid)->atacking.erase(it); //si se ha morido se quita, no se cambia ni nada, la lista se actualiza sola
	else 
		objetivesList.at(hamid)->strongAtacking.erase(it);
}

void EnemyMother::removeFromAmbushList(int hamid, std::list<Entity*>::iterator it, bool strong) {
	if (!strong) 
		objetivesList.at(hamid)->ambushing.erase(it); //si se ha morido se quita, no se cambia ni nada, la lista se actualiza sola
	else 
		objetivesList.at(hamid)->strongAmbushing.erase(it);
}

void EnemyMother::update() {
	if (numPlayers > 0) {
		if (state_->getState() == GameStates::RUNNING) {
		
			asingEnemies();
			orderAttack();
		}
	}
	//no queria hacerlo asi pero es para salir del truyo, (no localizo la parte exacta en al que un hamster muere y poder identificarlo), oi si co�o que co�o
}


void EnemyMother::onEnable() {
}

void EnemyMother::onDisable() {
}