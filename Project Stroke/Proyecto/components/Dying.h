#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
//#include "../ecs/Manager.h"
//#include "../ecs/Entity.h"
#include "Animator.h"


class Dying : public Component {
public:
	Dying(){};

	virtual ~Dying() {};

	void init() override;
	void update() override;
	
	void blink() ;

private:
	Animator* anim_;

	bool animActive_ =false;
	bool blinkActive_ = false;
	int timer_;
	int blinksToDie_ = 0;

	//Constantes
	const int BLINK = 200,
		TIMEBEFOREBLINK = 3000,
		DEADCOUNT = 8;
};

