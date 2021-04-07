#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Gravity.h"
#include <map>
#include <cmath>
#include <queue>

const int CADENCE = 750;

class Combos : public Component {
public:
	Combos() : lastAttack_(0), grv_(nullptr) {};
	~Combos() {};			//L L L L     //F F F F     //L F    //J + L...		//J + F...
	void init() override;
	void update() override;
	bool checkCombo(int accion);
	void popUntilEmpty();
private:
	Gravity* grv_;
	std::queue<int> cola_;
	int lastAttack_;
	void lightStrong();
	void fourConsecutives();
	void jumpStrong();

};