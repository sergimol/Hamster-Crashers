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
}

void Stroke::update() {
	int t = sdlutils().currRealTime();
	// Comprobación de la reducción de la probabilidad
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
		// Número aleatorio para ver si infarta o no
		int i = r_.nextInt(1, 100);
		// Si i es menor que la probabilidad, infarta
		if (i <= chance_ + chanceFromAb_ && hms_->getState() != HamStates::INFARCTED) {
			//TODO madremia que no lo podemos desactivar porque hay que quitarlo de la lsita de player y noseque algo habra que ahcer para que la camara no explote
			//entity_->setActive(false);
			infarctHamster();
			//TODO by Samuel necesito que por algún lugar llameis al método de Increase Latency de HeartUI para que se actualice la interfaz de la palpitaçao
		}
			

		timeLastUpdate_ = t;
	}

	//std::cout << chance_ << " " << chanceFromAb_ << std::endl;
}

void Stroke::increaseChance(int n, bool fromAbility) {
	if (!fromAbility) {
		chance_ += n;
		if(chance_ > MAXCHANCE)
			chance_ = MAXCHANCE;
	}
	else {
		chanceFromAb_ += n;
		if(chanceFromAb_ > MAXAB)
			chanceFromAb_ = MAXAB;
	}
	
	timeLastIncrease_ = sdlutils().currRealTime();
	//std::cout << chance_ + " " + chanceFromAb_ << std::endl;
}


void Stroke::decreaseChance() {
	if (chance_ > 0) {
		chance_ -= (chance_ * DECREASEPERCENTAGE) / 100;
	}
}

void Stroke::infarctHamster() {
	//El personaje principal pasa a estar infartado
	auto name = entity_->getComponent<EntityAttribs>()->getId();

	hms_->getState() = HamStates::INFARCTED;
	ab_->deactiveAbility();
	entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::STROKE, true);
	entity_->getComponent<GhostCtrl>()->setActive(true);
	//GENERAR PERSONAJE INFARTADO ()

	auto* deadBody = entity_->getMngr()->addEntity();
	deadBody->addComponent<Transform>(tr_->getPos(), Vector2D(0,0), tr_->getW(), tr_->getH(), 0, tr_->getZ(), tr_->getFlip());
	deadBody->addComponent<Animator>(&sdlutils().images().at("sardinillaSheet"),
		86,
		86,
		3,
		3,
		220,
		Vector2D(0, 0),
		3)->play(sdlutils().anims().at(name + "_stroke"));
	deadBody->addComponent<Gravity>();
	deadBody->addComponent<InfarctedBody>(entity_);
	deadBody->addComponent<ReanimationGame>();

	entity_->getMngr()->getDeadBodies().push_back(deadBody);

	std::cout << "INFARTADO" << std::endl;
}
