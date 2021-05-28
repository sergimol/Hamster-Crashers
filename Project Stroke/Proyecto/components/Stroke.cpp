#include "../components/Stroke.h"
#include "../components/dialogos.h"
#include "../components/Transition.h"
#include "../components/Roll.h"
#include "../components/Poison.h"
#include "../components/Pray.h"
#include "../components/Turret.h"
#include "../components/WarCry.h"
#include "../components/Gravity.h"
#include "../components/Image.h"
#include "../components/GhostCtrl.h"
#include "../components/AnimHamsterStateMachine.h"
#include "../components/ReanimationGame.h"
#include "../components/CollisionDetec.h"
#include "../components/ReanimationAlone.h"
#include "Shadow.h"
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
	if (ab_ == nullptr) ab_ = entity_->getComponent<WarCry>();

	assert(ab_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void Stroke::update() {
	if (state_->getState() == GameStates::RUNNING) {
		if (ih().isKeyDown(SDLK_z) && entity_->getComponent<EntityAttribs>()->getId() == "keta")
			INFARCT();
		checkChance();
	}
	//std::cout << chance_ << " " << chanceFromAb_ << std::endl;
}

void Stroke::increaseChance(int n, bool fromAbility) {
	//Si no se ha activado no hace nada
	if (!entity_->getMngr()->getStrokeActive())
		return;

	if (hms_->getState() != HamStates::INFARCTED) {
		if (!fromAbility) {
			ss_->increaseChanceNORMAL(n, chance_);
		}
		else {
			ss_->increaseChanceAB(n, chanceFromAb_);
		}

		entity_->getComponent<HeartUI>()->increaseLatency(chanceFromAb_ + chance_);

		if (chance_ + chanceFromAb_ > CHANGECOLORVALUE )
			entity_->getComponent<Animator>()->setTexture(&sdlutils().images().at(entity_->getComponent<EntityAttribs>()->getId() + "Sheet2"));

		timeLastIncrease_ = sdlutils().currRealTime();
	}
	//std::cout << chance_ + " " + chanceFromAb_ << std::endl;
}

//Decrementa DECREASEPERCENTAGE en el minijuego de infarto
void Stroke::decreaseChance() {
	if (chance_ > 0) {
		chance_ -= (chance_ * DECREASEPERCENTAGE) / 100;

		//Llamamos a la UI para que el corazon palpite más rapido
		entity_->getComponent<HeartUI>()->increaseLatency((chanceFromAb_ + chance_) / 10);
	}
	if (chance_ <= MINVALUE) entity_->getComponent<Animator>()->setTexture(&sdlutils().images().at(entity_->getComponent<EntityAttribs>()->getId() + "Sheet3"));
}

void Stroke::checkChance() {
	int t = sdlutils().currRealTime();
	// Comprobaci�n de la reducci�n de la probabilidad
	if (t >= timeLastDecrease_ + TIMEBETWEENDECREASES && t >= timeLastIncrease_ + TIMETODECREASE) {
		chance_ -= NORMALDECREASE;
		chanceFromAb_ -= NORMALDECREASE;

		if (chance_ < MINVALUE)
			chance_ = MINVALUE;
		if (chanceFromAb_ < 0)
			chanceFromAb_ = 0;

		entity_->getComponent<HeartUI>()->increaseLatency(chanceFromAb_ + chance_);

		if (chance_ + chanceFromAb_ < CHANGECOLORVALUE && chance_ + chanceFromAb_ > MINVALUE)
			entity_->getComponent<Animator>()->setTexture(&sdlutils().images().at(entity_->getComponent<EntityAttribs>()->getId() + "Sheet"));

		timeLastDecrease_ = t;
	}

	// Comprobamos que haya pasado el tiempo suficiente entre actualizaciones
	if (t >= timeLastUpdate_ + UPDATETIME) {
		if (hms_->getState() != HamStates::INFARCTED && hms_->getState() != HamStates::DEAD && ss_->checkChance(chance_, chanceFromAb_)) {
			//TODO madremia que no lo podemos desactivar porque hay que quitarlo de la lsita de player y noseque algo habra que ahcer para que la camara no explote
			infarctHamster();
		}
		timeLastUpdate_ = t;
	}
}

void Stroke::infarctHamster() {

	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("heartattack");
	auto hams_ = entity_->getMngr()->getPlayers();
	bool allDead = true;
	for (Entity* e : hams_) {
		auto sta = e->getComponent<HamsterStateMachine>()->getState();
		if (sta != HamStates::DEAD && sta != HamStates::INFARCTED) {
			allDead = false;
		}
	}
	if (allDead) {
		entity_->getMngr()->getHandler<LevelHandlr>()->getComponent<Transition>()->changeScene("hasMuerto", true, 0);
	}

	bool& strokeTutorial = entity_->getMngr()->getStrokeTuto();
	if (strokeTutorial) {
		strokeTutorial = false;
		if (sdlutils().hamstersChosen() != 1)
			entity_->getMngr()->getHandler<dialogosMngr>()->getComponent<dialogos>()->showStrokeTutorial("dialogo3");
		else
			entity_->getMngr()->getHandler<dialogosMngr>()->getComponent<dialogos>()->showStrokeTutorial("dialogo3singleplayer");
	}
	//Los enemigos que le seguian dejan de hacerlo
	auto& ents = entity_->getMngr()->getPlayers();
	if (ents.size() > 1) {
		//El personaje principal pasa a estar infartado
		auto name = entity_->getComponent<EntityAttribs>()->getId();
		auto name2 = name;
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
		auto& state = hms_->getState();
		state = HamStates::INFARCTED;

		//Y cambiamos la interfaz
		entity_->getComponent<HeartUI>()->dep();
		entity_->getComponent<UI>()->dep("3");

		//hms_->getState() = HamStates::INFARCTED;
		this->setActive(false);

		//Animacion del fantasma
		entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::STROKE, true);
		//Activamos el control del fantasma
		entity_->getComponent<GhostCtrl>()->setActive(true);

		//GENERAR PERSONAJE INFARTADO ()
		auto* deadBody = entity_->getMngr()->addEntity();
		auto* tr = deadBody->addComponent<Transform>(tr_->getPos(), Vector2D(0, 0), tr_->getW(), tr_->getH(), 0, tr_->getZ(), tr_->getFlip(), tr_->getScaleW(), tr_->getScaleH());

		int tam = 0;

		if (name == "sardinilla" || name == "monchi") {
			tam = 86;
		}
		else if (name == "canelon" || name == "canelonDemon") {
			tam = 128;
			name2 = "canelon";
		}
		else {
			tam = 100;
		}
		deadBody->addComponent<Shadow>(true, true);
		deadBody->addComponent<Animator>(&sdlutils().images().at(name + "Sheet"),
			tam,
			tam,
			3,
			3,
			220,
			Vector2D(0, 0),
			3)->play(sdlutils().anims().at(name2 + "_stroke"));
		tr->setVelZ(tr_->getVelZ());
		deadBody->addComponent<CollisionDetec>();

		tr->setFloor(tr_->getFloor());
		tr->setZ(tr_->getZ());
		tr->setGravity(deadBody->addComponent<Gravity>());

		deadBody->addComponent<Movement>();
		deadBody->addComponent<InfarctedBody>(entity_);
		deadBody->addComponent<ReanimationGame>();
		entity_->getMngr()->getDeadBodies().push_back(deadBody);

		//Reseteamos chances
		restartChance();

		std::cout << "INFARTADO" << std::endl;
	}
	else {
		//entity_->getComponent<EntityAttribs>()->recieveDmg(2000);
		//Evitamos el uso de la habilidad
		ab_->deactiveAbility();
		auto& state = hms_->getState();
		state = HamStates::INFARCTED_ALONE;

		//Y cambiamos la interfaz
		entity_->getComponent<HeartUI>()->dep();
		//entity_->getComponent<UI>()->dep("3");

		//hms_->getState() = HamStates::INFARCTED;
		this->setActive(false);

		//Animacion del fantasma
		entity_->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::STROKE_ALONE, true);

		entity_->getComponent<Movement>()->setActive(false);

		entity_->addComponent<ReanimationAlone>();

		restartChance();
		std::cout << "MUERTO" << std::endl;
	}
}

void Stroke::onResume() {
	timeLastUpdate_ += sdlutils().currRealTime() - timeLastUpdate_;
	timeLastIncrease_ += sdlutils().currRealTime() - timeLastIncrease_;
	timeLastDecrease_ += sdlutils().currRealTime() - timeLastDecrease_;
}

void Stroke::onEnable() {
	restartChance();
}

void Stroke::setStrategy(StrokeStrategy* ss) {
	if (ss_ != nullptr) delete ss_;
	ss_ = ss;
};