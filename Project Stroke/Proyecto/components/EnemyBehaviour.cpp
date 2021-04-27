#include "EnemyBehaviour.h"
#include "Stroke.h"
#include "EnemyMother.h"

EnemyBehaviour::EnemyBehaviour(Behavior* auxbh) :
	mov_(nullptr), tr_(nullptr), rangeOffsetX_(250), rangeOffsetY_(100), lockedHamState_(nullptr), lockedHamster_(nullptr),
	hamsterTr_(nullptr), bh_(auxbh), bossAtk_(nullptr), enStrongAtk_(nullptr), hamId_(NULL), list(NULL), state_(nullptr) {
}

void EnemyBehaviour::init() {
	mov_ = entity_->getComponent<MovementSimple>();
	assert(mov_ != nullptr);

	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);

	enAtk_ = entity_->getComponent<EnemyAttack>();
	bossAtk_ = entity_->getComponent<FirstBossAttack>();
	enStrongAtk_ = entity_->getComponent<EnemyStrongAttack>();

	assert(bossAtk_ != nullptr || enAtk_ != nullptr || enStrongAtk_ != nullptr);

	hamsters_ = entity_->getMngr()->getPlayers();

	//le pregunta a madre a quien debe fijar //le va a pasar la id del hamster y listo
	int id = 0;
	//ya debe de saber cual es la id
	lockHamster(id); // De momento un hamster concreto para manejar mejor

	bh_->setOwner(this);
	bh_->init();
}

void EnemyBehaviour::SetBehavior(Behavior* bs) {
	
	if (bh_ != nullptr)
	delete bh_;
	bh_ = bs;
	bh_->setOwner(this);
	bh_->init();
}

//Fija a un hamster concreto
void EnemyBehaviour::lockHamster(int id) {
	lockedHamster_ = hamsters_[id];
	hamsterTr_ = lockedHamster_->getComponent<Transform>();
	lockedHamState_ = lockedHamster_->getComponent<HamsterStateMachine>();
}

//Esta a rango de ataque
bool EnemyBehaviour::isWithinAttackRange() {
	auto width = tr_->getW();
	auto hamWidth = hamsterTr_->getW();

	auto& hamPos = hamsterTr_->getPos();
	auto& pos = tr_->getPos();
	int hamX = hamPos.getX(),
		hamY = hamPos.getY() + hamsterTr_->getH(),
		x = pos.getX(),
		y = pos.getY() + tr_->getH();

	return((hamX /*+ rangeOffsetX_*/ + hamWidth * 2 >= x + width && hamX + hamWidth - rangeOffsetX_ <= x + width) &&
		(hamY + rangeOffsetY_ >= y && hamY - rangeOffsetY_ / 10 <= y));
}

void EnemyBehaviour::update() {
	//ejecuta el metodo de behavior que le dice como comportarse (atacar, como moverse, cuando, el hace las condiciones el resto nos olvidamos)
	if(state_->getState() != GameStates::PAUSE)
		bh_->behave();
	//tambien seria oportuno que esta misma clase hiciese los cambios de bh_, aunque suene y parezca raro que sea este objeto el que indique cual es
	//el siguiente comportamiento/Behavior no es algo tan descabezado.. <3
}


void EnemyBehaviour::onEnable() {
	//lockHamster();
}

void EnemyBehaviour::onDisable() {

	mov_->updateKeymap(MovementSimple::RIGHT, false);
	mov_->updateKeymap(MovementSimple::LEFT, false);
	mov_->updateKeymap(MovementSimple::DOWN, false);
	mov_->updateKeymap(MovementSimple::UP, false);

	lockedHamster_ = nullptr;
}

void EnemyBehaviour::setHamId(int hId, std::list<Entity*>::iterator it, char l) {
	hamId_ = hId;
	listIterator = it; //es para luego hacer el quitado de la lista que no es una pila, si no un vector del que s epueden quitar o meter entidades desde cualquier direccion
	lockHamster(hId);
	bh_->setObjetive();
	list = l;
}
void EnemyBehaviour::die() {
	if (list == 'a') {
		entity_->getMngr()->getHandler<Mother>()->getComponent<EnemyMother>()->removeFromAttackList(hamId_, listIterator);
	}
	else if (list == 'b') {
		entity_->getMngr()->getHandler<Mother>()->getComponent<EnemyMother>()->removeFromAmbushList(hamId_, listIterator);
	}
	//tiene que distinguir que tipo de behavior tiene,
	//madre de dios no hay manera de comprobarlo directamente esto es muy doloroso
	//if (bh_ == )
}
void EnemyBehaviour::changeToAmbush() {
	if (list == 'a')
	entity_->getMngr()->getHandler<Mother>()->getComponent<EnemyMother>()->changeFromAttackToAmbush(hamId_, listIterator);
}