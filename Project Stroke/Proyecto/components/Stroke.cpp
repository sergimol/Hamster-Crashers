#include "../components/Stroke.h"
#include "../components/Roll.h"
#include "../components/Poison.h"
#include "../components/Pray.h"
#include "../components/Turret.h"
#include "../components/Gravity.h"
#include "../components/Image.h"
#include "../components/GhostCtrl.h"
#include "../components/AnimHamsterStateMachine.h"
#include "../components/ReanimationGame.h"
#include "../components/CollisionDetec.h"
#include "EnemyMother.h"

void Stroke::init() {
		hms_ = entity_->getComponent<HamsterStateMachine>();
		assert(hms_ != nullptr);

		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
		
		ab_ = entity_->getComponent<Roll>();

		if (ab_ == nullptr) ab_ = entity_->getComponent<Pray>();
		if (ab_ == nullptr) ab_ = entity_->getComponent<Poison>();
		if (ab_ == nullptr) ab_ = entity_->getComponent<Turret>();

		assert(ab_ != nullptr);

		state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
		assert(state_ != nullptr);
}

void Stroke::update() {
	if(state_->getState() == GameStates::RUNNING)
		checkChance();
	//std::cout << chance_ << " " << chanceFromAb_ << std::endl;
}

void Stroke::increaseChance(int n, bool fromAbility) {
	if (hms_->getState() != HamStates::INFARCTED) {
		if (!fromAbility) {
			ss_->increaseChanceNORMAL(n, chance_);
		}
		else {
			ss_->increaseChanceAB(n, chanceFromAb_);
		}
	    entity_->getComponent<HeartUI>()->increaseLatency(chanceFromAb_ + chance_);

		timeLastIncrease_ = sdlutils().currRealTime();
	}
	//std::cout << chance_ + " " + chanceFromAb_ << std::endl;
}


void Stroke::decreaseChance() {
	if (chance_ > 0) {
		chance_ -= (chance_ * DECREASEPERCENTAGE) / 100;

		//Llamamos a la UI para que el corazon palpite más rapido
		entity_->getComponent<HeartUI>()->increaseLatency(chanceFromAb_ + chance_);
	}
}

void Stroke::checkChance() {
	int t = sdlutils().currRealTime();
	// Comprobaci�n de la reducci�n de la probabilidad
	if (t >= timeLastIncrease_ + TIMETODECREASE && t >= timeLastDecrease_ + TIMEBETWEENDECREASES) {
		chance_--;
		chanceFromAb_--;
		if (chance_ < 1)
			chance_ = 1;
		if (chanceFromAb_ < 0)
			chanceFromAb_ = 0;

		timeLastDecrease_ = t;
	}

	// Comprobamos que haya pasado el tiempo suficiente entre actualizaciones
	if (t >= timeLastUpdate_ + UPDATETIME) {
		// N�mero aleatorio para ver si infarta o no
		//int i = r_.nextInt(1, 100);
		// Si i es menor que la probabilidad, infarta
		if (hms_->getState() != HamStates::INFARCTED && ss_->checkChance(chance_, chanceFromAb_) ) {
			//TODO madremia que no lo podemos desactivar porque hay que quitarlo de la lsita de player y noseque algo habra que ahcer para que la camara no explote
			//entity_->setActive(false);
			infarctHamster();
			//TODO by Samuel necesito que por alg�n lugar llameis al m�todo de Increase Latency de HeartUI para que se actualice la interfaz de la palpita�ao
		}


		timeLastUpdate_ = t;
	}
}

void Stroke::infarctHamster() {
	//El personaje principal pasa a estar infartado
	auto name = entity_->getComponent<EntityAttribs>()->getId();
	//Los enemigos que le seguian dejan de hacerlo
	auto& ents = entity_->getMngr()->getPlayers();

	
	int i = 0;
	while (i < ents.size()) {
		if (entity_ == ents[i]) {
			entity_->getMngr()->getHandler<Mother>()->getComponent<EnemyMother>()->cleanListHam(i);
			i = ents.size();
		}
		++i;
	}
	

	//TODO si alguien se le ocurre manera mejor para comprobar la id (posicion en el array de players, que la comente o que la ponga en todos los bucles que he ido haciendo de este tipo, son las 6 de la mañana y no quiero seguir viviendo)


	
	//Evitamos el uso de la habilidad
	ab_->deactiveAbility();
	
	//Y cambiamos la interfaz
	entity_->getComponent<HeartUI>()->dep();

	//hms_->getState() = HamStates::INFARCTED;

	//Animacion del fantasma
	entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::STROKE, true);
	//Activamos el control del fantasma
	entity_->getComponent<GhostCtrl>()->setActive(true);
	
	//GENERAR PERSONAJE INFARTADO ()
	auto* deadBody = entity_->getMngr()->addEntity();
	auto* tr = deadBody->addComponent<Transform>(tr_->getPos(), Vector2D(0,0), tr_->getW(), tr_->getH(), 0, tr_->getZ(), tr_->getFlip(),tr_->getScaleW(),tr_->getScaleH());
	deadBody->addComponent<Animator>(&sdlutils().images().at(name + "Sheet"),
		86,
		86,
		3,
		3,
		220,
		Vector2D(0, 0),
		3)->play(sdlutils().anims().at(name + "_stroke"));
	tr->setVelZ(tr_->getVelZ());
	deadBody->addComponent<CollisionDetec>();
	deadBody->addComponent<Gravity>();
	deadBody->addComponent<Movement>();
	deadBody->addComponent<InfarctedBody>(entity_);
	deadBody->addComponent<ReanimationGame>();

	entity_->getMngr()->getDeadBodies().push_back(deadBody);

	//Reseteamos chances
	chance_ = 0;
	chanceFromAb_ = 0;

	std::cout << "INFARTADO" << std::endl;
}

void Stroke::onResume() {
	timeLastUpdate_ += sdlutils().currRealTime() - timeLastUpdate_;
	timeLastIncrease_ += sdlutils().currRealTime() - timeLastIncrease_;
	timeLastDecrease_ += sdlutils().currRealTime() - timeLastDecrease_;
}

void Stroke::setStrategy(StrokeStrategy* ss) { 
	if(ss_ != nullptr) delete ss_;
	ss_ = ss; 
};