#pragma once

#include "../ecs/Component.h"

#include "../ecs/Entity.h"

class Life: public Component {
public:
	Life();

	Life(int life);

	virtual ~Life() {
	}

	bool recieveDmg(int dmg);

	void heal(int hp);


	void update() override {
	}

	inline void setLife(int life) { health_ = life; };

	//Getters auxiliares
	inline int getLife() const {
		return health_;
	}

private:
	int health_;

};

