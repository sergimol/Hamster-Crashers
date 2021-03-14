#pragma once

#include "../ecs/Component.h"

#include "../ecs/Entity.h"
#include "UI.h"
#include "HamsterStateMachine.h"

class Life: public Component {
public:
	Life();

	Life(int life);

	virtual ~Life() {
	}

	void init() override;

	bool recieveDmg(int dmg);

	void heal(int hp);


	void update() override {
	};

	inline void setLife(int life) { health_ = life; };

	//Getters auxiliares
	inline int getLife() const {
		return health_;
	}
	inline int getMaxLife() const {
		return maxHealth_;
	}

private:
	HamsterStateMachine* hms_;
	int health_;
	int maxHealth_;
};

