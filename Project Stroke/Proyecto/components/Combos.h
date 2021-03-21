#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include <map>
#include <cmath>
#include <queue>

const int CADENCE=1000;

class Combos : public Component {
public:
	Combos() : lastAttack_(0) {};
	~Combos() {};			//L L L L     //F F F F     //L F    //J + L...		//J + F...
	virtual void update();
	bool checkCombo(int accion);
private:
	std::queue<int> cola_;
	int lastAttack_;
	void lightStrong();
	void fourConsecutives();
};