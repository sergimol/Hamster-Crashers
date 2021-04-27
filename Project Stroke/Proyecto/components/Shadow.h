#pragma once

#include "ShadowFollow.h"
#include "HamsterStateMachine.h"
#include "GameStates.h"

/*
*	Crea y controla la sombra del jugador de manera independiente al Manager, para lograr
*	que se renderice y actualice fuera del vector de entidades, pero ordenada con el jugador
* 
*	Es en un "hijo" de la entidad que la lleve
*/

class Shadow : public Component {
public:
	Shadow() :shadow_(nullptr), tr_(nullptr), gState_(nullptr) {};
	virtual ~Shadow() { delete shadow_; shadow_ = nullptr; };
	virtual void init() override;
	virtual void render() override;
	virtual void update() override;
private:
	Entity* shadow_;
	Transform* tr_;
	HamStates state_;
	GameStates* gState_;
};