#include "FinalBossManager.h"
#include "Stroke.h"

FinalBossManager::FinalBossManager(int hamN) :
	tr_(nullptr), rangeOffsetX_(250), rangeOffsetY_(100), lockedHamState_(nullptr),
	lockedHamster_(nullptr), hamsterTr_(nullptr), attackAvailable_(false),
	waitingTime_(sdlutils().currRealTime()), waitingCD_(4000), stunTime_(0), stunCD_(1500),
	hamsNum_(hamN), handAttribs_(nullptr), fistAttribs_(nullptr) {
}

void FinalBossManager::init() {

	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	hamsters_ = entity_->getMngr()->getPlayers();

	lockHamster(); // De momento un hamster concreto para manejar mejor
	assert(lockedHamster_ != nullptr);
	assert(lockedHamState_ != nullptr);
	assert(hamsterTr_ != nullptr);

	hand_ = entity_->getMngr()->addEntity();		//Referencia a la mano
	handTr_ = hand_->addComponent<Transform>(
		tr_->getPos(), Vector2D(), 256.0f, 5 * 256.0f, 0.0f, 0.8f, 0.8f);
	handTr_->getFlip() = true;

	hand_->addComponent<EnemyStateMachine>();
	hand_->setGroup<Enemy>(true);

	handAttribs_ = hand_->addComponent<EntityAttribs>(800 + (hamsNum_ * 100), 0.0, "enemy", Vector2D(4.5, 2), 0, 0, 20, true, true);
	hand_->addComponent<UI>("canelon", 4);

	hand_->addComponent<Image>(&sdlutils().images().at("firstBoss"));

	bossAtk_ = hand_->addComponent<FinalBossAttack>();
	movHand_ = hand_->addComponent<MovementSimple>();

	entity_->getMngr()->setHandler<FinalBoss>(hand_);
	entity_->getMngr()->getEnemies().push_back(hand_);


	fist_ = entity_->getMngr()->addEntity(); //Referencia al puño
	fistTr_ = fist_->addComponent<Transform>(
		tr_->getPos(), Vector2D(), 256.0f, 5 * 256.0f, 0.0f, 0.8f, 0.8f);
	fistTr_->getFlip() = true;

	fist_->addComponent<EnemyStateMachine>();
	fist_->setGroup<Enemy>(true);

	fistAttribs_ = fist_->addComponent<EntityAttribs>(800 + (hamsNum_ * 100), 0.0, "enemy", Vector2D(4.5, 2), 0, 0, 20, true, true);

	fist_->addComponent<Image>(&sdlutils().images().at("firstBoss"));

	bossPunch_ = fist_->addComponent<FinalBossPunch>();
	movPunch_ = fist_->addComponent<MovementSimple>();

	entity_->getMngr()->getEnemies().push_back(fist_);

	handTurn_ = sdlutils().rand().nextInt(0, 2) == 0;
}


//Fija a un hamster en orden desde el siguiente al último elegido
void FinalBossManager::lockHamster() {
	//Variable que contralará el recorrido de los hamsters
	std::vector<Entity*> posHams;
	for (Entity* ham : hamsters_)
	{
		if (!ham->getComponent<HamsterStateMachine>()->cantBeTargeted())
		{
			posHams.emplace_back(ham);
		}
	}

	if (!posHams.empty()) {

		int ham1 = sdlutils().rand().nextInt(0, posHams.size());
		int ham2 = sdlutils().rand().nextInt(0, posHams.size());

		lockedHamster_ = posHams[ham1];
		hamsterTr_ = lockedHamster_->getComponent<Transform>();
		lockedHamState_ = lockedHamster_->getComponent<HamsterStateMachine>();

		lockedHamsterPunch_ = posHams[ham2];
		hamsterTrPunch_ = lockedHamsterPunch_->getComponent<Transform>();
		lockedHamStatePunch_ = lockedHamsterPunch_->getComponent<HamsterStateMachine>();

		//Comienza el tiempo antes de ataque
		waitingTime_ = sdlutils().currRealTime();
	}
	else
	{
		//Si ninguno esta activo pone todo a null
		lockedHamster_ = nullptr;
		lockedHamState_ = nullptr;
		hamsterTr_ = nullptr;
		lockedHamsterPunch_ = nullptr;
		hamsterTr_ = nullptr;
	}
}

//Esta a rango de ataque
bool FinalBossManager::isWithinAttackRange(Transform* tr, bool fist) {
	auto width = tr->getW();
	auto height = tr->getH();
	auto hamWidth = hamsterTr_->getW();

	auto& hamPos = hamsterTr_->getPos();
	auto& pos = tr->getPos();
	int hamX = hamPos.getX(),
		x = pos.getX();
	if (fist) {
		int hamY = hamPos.getY(),
			y = pos.getY();
		return ((hamX + hamWidth >= x + 3 * width / 4 && hamX <= x + 1 * width / 4) &&
			(hamY >= y + 3 * height / 4 && hamY <= y + 3.5 * height / 4));
	}
	else
		return(hamX + hamWidth >= x + 3 * width / 4 && hamX <= x + 1 * width / 4);
}

void FinalBossManager::update() {
	if (lockedHamster_ != nullptr && lockedHamStatePunch_ != nullptr) {

		if (bossAtk_->checkAttackFinished() || bossPunch_->checkAttackFinished()) {
			handTurn_ = sdlutils().rand().nextInt(0, 100) < 65;
			bossAtk_->resetAttackFinished();
			bossPunch_->resetAttackFinished();
			waitingTime_ = sdlutils().currRealTime();
		}

		handTurn_ ? movement(fistTr_, hamsterTrPunch_, movPunch_) : movement(handTr_, hamsterTr_, movHand_);

		// Cambia el foco si el actual muere o le da un infarto
		if (lockedHamState_->cantBeTargeted() || lockedHamStatePunch_->cantBeTargeted()) {
			lockHamster();
		}
		else if (!bossAtk_->getAttackStarted() && !bossPunch_->getAttackStarted()) { // si no cambia de hamster marcado Y no está en medio de un ataque

			handTurn_ ? movement(handTr_, hamsterTr_, movHand_) : movement(fistTr_, hamsterTrPunch_, movPunch_);

			bool attRange = handTurn_ ? isWithinAttackRange(handTr_, false) : isWithinAttackRange(fistTr_, true);

			if (attRange && sdlutils().currRealTime() > waitingTime_ + waitingCD_) {
				if (handTurn_) bossAtk_->LaunchAttack();
				else bossPunch_->LaunchAttack();
				waitingTime_ = sdlutils().currRealTime();

				//lockHamster();
			}
		}
		else {
			float fistLife = fistAttribs_->getLife();
			float handLife = handAttribs_->getLife();
			if (fistLife > handLife)
				fistAttribs_->setLife(handLife);
			else if (handLife > fistLife)
				handAttribs_->setLife(fistLife);

			//waitingTime_ = sdlutils().currRealTime();
		}
	}
	else
		lockHamster();
}

void FinalBossManager::movement(Transform* tr, Transform* hamsterTr, MovementSimple* mov) {
	auto& hamPos = hamsterTr->getPos();
	auto& pos = tr->getPos();
	int hamX = hamPos.getX(),
		hamY = hamPos.getY(),
		x = pos.getX(),
		y = pos.getY();

	auto width = tr->getW();
	auto hamWidth = hamsterTr->getW();
	auto& flip = tr->getFlip();

	if (x + width / 2 < hamX + hamWidth / 2)
		flip = false;
	else
		flip = true;

	if (x > hamX + width / 4)
		mov->updateKeymap(MovementSimple::LEFT, true);
	else
		mov->updateKeymap(MovementSimple::LEFT, false);
	if (x < hamX - width / 4)
		mov->updateKeymap(MovementSimple::RIGHT, true);
	else
		mov->updateKeymap(MovementSimple::RIGHT, false);

	if (tr == fistTr_) {
		if (y > hamY - 3 * tr->getH() / 4)
			mov->updateKeymap(MovementSimple::UP, true);
		else
			mov->updateKeymap(MovementSimple::UP, false);
		if (y < hamY - 3.5 * tr->getH() / 4)
			mov->updateKeymap(MovementSimple::DOWN, true);
		else
			mov->updateKeymap(MovementSimple::DOWN, false);
	}
	else {
		mov->updateKeymap(MovementSimple::UP, false);
		mov->updateKeymap(MovementSimple::DOWN, false);
	}

	if (isWithinAttackRange(tr, tr == fistTr_)) { // Si est� a rango, no necesita moverse e intentara atacar si ha pasado cierto tiempo
		mov->updateKeymap(MovementSimple::RIGHT, false);
		mov->updateKeymap(MovementSimple::LEFT, false);
		mov->updateKeymap(MovementSimple::DOWN, false);
		mov->updateKeymap(MovementSimple::UP, false);
	}
}