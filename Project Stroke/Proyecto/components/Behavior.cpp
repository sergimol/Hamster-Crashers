#include "Behavior.h"

 void Behavior::setOwner(EnemyBehaviour* ow) {
	owner_ = ow;
	//conseguimos del owner todos los datos principales que necesitamos para hacer funcionar cuialquier behavior
	mov_ = ow->getMov();
	tr_ = ow->getTr();
	setObjetive();
}
 void Behavior::setObjetive() {
	lockedHamster_ = owner_->getLockedHamster();
	hamsterTr_ = lockedHamster_->getComponent<Transform>();
	lockedHamState_ = lockedHamster_->getComponent<HamsterStateMachine>();
}
