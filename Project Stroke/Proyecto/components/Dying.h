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

	bool animActive =false;
	bool blinkActive = false;
	int timer;
	int blinksToDie = 0;
	const int BLINK = 200,
		TIMEBEFOREBLINK = 3000,
		DEADCOUNT = 8;
};

