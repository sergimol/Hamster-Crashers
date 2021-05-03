#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Gravity.h"
#include "AnimHamsterStateMachine.h"
#include "EntityAttribs.h"
#include <map>
#include <cmath>
#include <queue>

const int CADENCE = 750;
const int AIRCADENCE = 425;

class Combos : public Component {
public:
	Combos() : lastAttack_(0), grv_(nullptr), anim_(nullptr), state_(nullptr) {};
	~Combos() {};			//L L L L     //F F F F     //L F    //J + L...		//J + F...
	void init() override;
	void update() override;
	void onResume() override;
	bool checkCombo(int accion);
	void popUntilEmpty();
private:
	Gravity* grv_;
	AnimHamsterStateMachine* anim_;
	GameStates* state_;
	EntityAttribs* attribs_;

	std::queue<int> cola_;
	int lastAttack_;
	void lightStrong();
	void fourConsecutives();
	void jumpStrong();
	void firstActionAnim(int action);

};