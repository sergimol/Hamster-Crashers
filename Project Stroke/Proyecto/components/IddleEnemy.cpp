#include "IddleEnemy.h"
#include "Stroke.h"
#include "FleeFromPlayer.h"

IddleEnemy::IddleEnemy() {}

void IddleEnemy::init() {
	Entity* owEntity = owner_->getEntity();
	mov_ = owEntity->getComponent<MovementSimple>();
	assert(mov_ != nullptr);

	tr_ = owEntity->getComponent<Transform>();
	assert(tr_ != nullptr);

}

void IddleEnemy::behave() {
	//no hay nada esta iddle es un fideo
	//que se yo imagina que estamos en un solo jugador, si esta infartado no se le puede traquear pos los bichos se paran, y aqui lo que decimos es que intenten lockear a alguien ahsta que puedan, aka cuando se recupere de un infarto, danlles te lo he puesto todo en un linea porque vas a ser tu quien lo lea con carinyo el nene

	mov_->updateKeymap(MovementSimple::DOWN, false);
	mov_->updateKeymap(MovementSimple::UP, false);
	mov_->updateKeymap(MovementSimple::LEFT, false);
	mov_->updateKeymap(MovementSimple::RIGHT, false);
}