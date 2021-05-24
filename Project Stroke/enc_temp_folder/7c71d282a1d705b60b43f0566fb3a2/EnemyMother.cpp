#include "EnemyMother.h"
#include "FollowPLayer.h"
#include "AmbushPlayer.h"
#include "iddleEnemy.h"
#include "StrongFollowPLayer.h"

EnemyMother::EnemyMother() : numPlayers_(0), numEnemies_(0), state_(nullptr) {}

void EnemyMother::init() { 
	hamsters_ = entity_->getMngr()->getPlayers();
	enemys_ = entity_->getMngr()->getEnemies();

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void EnemyMother::addObjetive(Entity* hamster) {
	auto a = new Objetivo;
	objetivesList_.insert({numPlayers_++, a});
	//establecer los valores de objetivo
	a->hamster = hamster;
	//es popsible que sean prescindibles
	a->hmTR_ = hamster->getComponent<Transform>();
	a->hmSt_ = hamster->getComponent<HamsterStateMachine>();
}

//los anyade a las listas ambush
void EnemyMother::asingEnemies() {
	auto n = waiting_.size();
	
	//reparte los enemigos normales
	for (auto i = 0u; i < n; i++) {
		// encontrar player alive
		int objetive = i % numPlayers_;
		while (objetive < numPlayers_ && objetivesList_.at(objetive)->hmSt_->cantBeTargeted()) {
			objetive++;
		}
		if (objetive < numPlayers_ && waiting_.front()->isActive()) {

			//no hay players alive no hace falta reasignar
			//
			//
			objetivesList_.at(objetive)->ambushing.push_back(waiting_.front());
			// poner las entitades en behavior ambush
			objetivesList_.at(objetive)->ambushing.back()->getComponent<EnemyBehaviour>()->SetBehavior(new AmbushPlayer());
			//darle el iterador y el hamster id a behavior porque lo va a necesitar
			objetivesList_.at(objetive)->ambushing.back()->getComponent<EnemyBehaviour>()->setHamId
				(objetive, --objetivesList_.at(objetive)->ambushing.end(), 'b');
			waiting_.pop_front();
		}
	}
	//repartir los enemigos strong
	n = strongWaiting_.size();
	for (auto i = 0u; i < n; i++) {
		// encontrar player alive
		int objetive = i % numPlayers_;
		while (objetive < numPlayers_ && objetivesList_.at(objetive)->hmSt_->cantBeTargeted()) {
			objetive++;
		}
		if (objetive < numPlayers_ && strongWaiting_.front()->isActive()) {

			//no hay players alive no hace falta reasignar
			//
			//
			objetivesList_.at(objetive)->strongAmbushing.push_back(strongWaiting_.front());
			// poner las entitades en behavior ambush
			objetivesList_.at(objetive)->strongAmbushing.back()->getComponent<EnemyBehaviour>()->SetBehavior(new AmbushPlayer());
			//darle el iterador y el hamster id a behavior porque lo va a necesitar
			objetivesList_.at(objetive)->strongAmbushing.back()->getComponent<EnemyBehaviour>()->setHamId
			(objetive, --objetivesList_.at(objetive)->strongAmbushing.end(), 'b');
			strongWaiting_.pop_front();
		}
	}
}

//recoge ambush en waiting y los reparte
void EnemyMother::reOrderEnemies() {

	for (int i = 0u; i < numPlayers_; i++) {
		cleanListHamAmbush(i);
	}
	asingEnemies();
}

//ordena en cada update que quien pueda atacar ataque
void EnemyMother::orderAttack() {

	for (int i = 0u; i < numPlayers_; i++) {
		//enemigos normales
		auto z = objetivesList_.at(i)->atacking.size();
		for (int y = z; y < 2; y++) {
			//se puede a�adir
			if (!objetivesList_.at(i)->ambushing.empty() && objetivesList_.at(i)->ambushing.front()->isActive()
				&& objetivesList_.at(i)->ambushing.front()->hasComponent<EnemyBehaviour>()) { // hay enemigos disponibles
				objetivesList_.at(i)->atacking.push_back(objetivesList_.at(i)->ambushing.front());
				//TODO poner las entitades en behavior attack correspondiente
				objetivesList_.at(i)->atacking.back()->getComponent<EnemyBehaviour>()->SetBehavior(new FollowPlayer());
				//darle el iterador y el hamster id a behavior porque lo va a necesitar
				objetivesList_.at(i)->atacking.back()->getComponent<EnemyBehaviour>()->setHamId
					(i, --objetivesList_.at(i)->atacking.end(), 'a');
				objetivesList_.at(i)->ambushing.pop_front();
			}
		}
		//enemigos strong
		if (objetivesList_.at(i)->strongAtacking.empty()) {
			//se puede a�adir
			if (!objetivesList_.at(i)->strongAmbushing.empty() && objetivesList_.at(i)->strongAmbushing.front()->isActive()
				&& objetivesList_.at(i)->strongAmbushing.front()->hasComponent<EnemyBehaviour>()) { // hay enemigos disponibles
				objetivesList_.at(i)->strongAtacking.push_back(objetivesList_.at(i)->strongAmbushing.front());
				//TODO poner las entitades en behavior attack correspondiente
				objetivesList_.at(i)->strongAtacking.back()->getComponent<EnemyBehaviour>()->SetBehavior(new StrongFollowPlayer());
				//darle el iterador y el hamster id a behavior porque lo va a necesitar
				objetivesList_.at(i)->strongAtacking.back()->getComponent<EnemyBehaviour>()->setHamId
				(i, --objetivesList_.at(i)->strongAtacking.end(), 'a');
				objetivesList_.at(i)->strongAmbushing.pop_front();
			}
		}
		
		//objetivesList.at(i)->atacking.erase(objetivesList.at(i)->atacking.begin());
		//std::list<Entity*>::iterator y
	}
}

void EnemyMother::cleanListToWaiting() {
	for (int i = 0u; i < numPlayers_; i++) {
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
	auto n = objetivesList_.at(i)->ambushing.size();
	for (auto y = 0u; y < n; y++) {
		waiting_.push_back(objetivesList_.at(i)->ambushing.back());
		objetivesList_.at(i)->ambushing.pop_back();
		//Tponer las entitades en behavior iddle
		if (waiting_.back()->isActive())
		waiting_.back()->getComponent<EnemyBehaviour>()->SetBehavior(new IddleEnemy());
	}
	//enemigos fuertes //TODO
	n = objetivesList_.at(i)->strongAmbushing.size();
	for (auto y = 0u; y < n; y++) {
		waiting_.push_back(objetivesList_.at(i)->strongAmbushing.back());
		objetivesList_.at(i)->strongAmbushing.pop_back();
		//Tponer las entitades en behavior iddle
		if (waiting_.back()->isActive())
		waiting_.back()->getComponent<EnemyBehaviour>()->SetBehavior(new IddleEnemy());
	}
}
void EnemyMother::cleanListHamAttacking(int i) {
	auto n = objetivesList_.at(i)->atacking.size();
	for (auto y = 0u; y < n; y++) {
		waiting_.push_back(objetivesList_.at(i)->atacking.back());
		objetivesList_.at(i)->atacking.pop_back();
		//poner las entitades en behavior iddle
		if (waiting_.back()->isActive())
		waiting_.back()->getComponent<EnemyBehaviour>()->SetBehavior(new IddleEnemy());
	}
	n = objetivesList_.at(i)->strongAtacking.size();
	for (auto y = 0u; y < n; y++) {
		waiting_.push_back(objetivesList_.at(i)->strongAtacking.back());
		objetivesList_.at(i)->strongAtacking.pop_back();
		//poner las entitades en behavior iddle
		if (waiting_.back()->isActive())
		waiting_.back()->getComponent<EnemyBehaviour>()->SetBehavior(new IddleEnemy());
	}


	//TODO
	//esot es el apaño de mierda que tenemos que hacer porque resulta que estamos desintegrando de la relaidad al hamnster y no podemos comprobar su estado jijiji me caog end ios
	//ME CAGO EN DIOS QUE SI PONGO ESTO PARA HACER LA MEIRDA EL APAÑO NO PUEDO USAR ESTE METODO PARA CONTROLAR EL INFARTO PORQUE CLARO LEUGO NO QUEDAN HAMSTER AJAJAJ
	//TODO TODO TODO TODO PERO TODFO EL PUTO MUNDO TODO TODO TODO TODO TODO TODO TODO TOD O

	//objetivesList.erase(i);
	//numPlayers--;
}

/*Cambia a un eneigo en concreto de attack to ambush*/
void EnemyMother::changeFromAttackToAmbush(int hamid, std::list<Entity*>::iterator &it) {
	/*if (it != objetivesList_.at(hamid)->atacking.end())
		if (it != objetivesList_.at(hamid)->ambushing.end())
			if ( it != objetivesList_.at(hamid)->strongAtacking.end()) 
				if (it != objetivesList_.at(hamid)->strongAmbushing.end())*/ //son todos los iteradores no validos y los que bajo ninguna circustancia quiero acceder a ellos
		//haog esot porque en algun momento que no estoy controlando el iterador pasa de estan en el ultimo-- a en end el no valido, presupongo que es por el refresh ya que es ahora el unico encargado de realizar tales operaciones
		//aunque eso implicaria que le ntidad se activando y desactivando entre instrucciones, lo cual tampoco me parece que sea correcto bajo ningunca circustancia.
		//como sea esta comprobacion impedira que todo esto explote en mil pedazos de ser asi el caso como s eha descrito anteriormente

	if (!(*it)->hasComponent<EnemyStrongAttack>()) {

		
		//coloca el bicho en ambush al final
		objetivesList_.at(hamid)->ambushing.push_back(*it);
		//lo saca de la lista attacking
		removeFromAttackList(hamid, it, false);

		//poner las entitades en behavior attack correspondiente
		objetivesList_.at(hamid)->ambushing.back()->getComponent<EnemyBehaviour>()->SetBehavior(new AmbushPlayer());
		//darle el iterador y el hamster id a behavior porque lo va a necesitar
		it = --objetivesList_.at(hamid)->ambushing.end();
		objetivesList_.at(hamid)->ambushing.back()->getComponent<EnemyBehaviour>()->setHamId
		(hamid, it, 'b');
		//yasta
	}
	else {

		//coloca el bicho en ambush al final
		objetivesList_.at(hamid)->strongAmbushing.push_back(*it);
		//lo saca de la lista attacking
		removeFromAttackList(hamid, it, true);

		//poner las entitades en behavior attack correspondiente
		objetivesList_.at(hamid)->strongAmbushing.back()->getComponent<EnemyBehaviour>()->SetBehavior(new AmbushPlayer());
		//darle el iterador y el hamster id a behavior porque lo va a necesitar
		it = --objetivesList_.at(hamid)->strongAmbushing.end();
		objetivesList_.at(hamid)->strongAmbushing.back()->getComponent<EnemyBehaviour>()->setHamId
		(hamid, it, 'b');
		//yasta
	}

}


void EnemyMother::removeFromAttackList(int hamid, std::list<Entity*>::iterator &it, bool strong) {
	if (!strong) 
		it = objetivesList_.at(hamid)->atacking.erase(it); //si se ha morido se quita, no se cambia ni nada, la lista se actualiza sola
	else 
		it = objetivesList_.at(hamid)->strongAtacking.erase(it);
}

void EnemyMother::removeFromAmbushList(int hamid, std::list<Entity*>::iterator &it, bool strong) {
	if (!strong) 
		it = objetivesList_.at(hamid)->ambushing.erase(it); //si se ha morido se quita, no se cambia ni nada, la lista se actualiza sola
	else 
		it = objetivesList_.at(hamid)->strongAmbushing.erase(it);
}

void EnemyMother::update() {
	//LE VOY A METER UN RESFRESH COMO UNA CASA A LAS LISTAS OWOWOWO
	//refreshLists();

	if (numPlayers_ > 0) {
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