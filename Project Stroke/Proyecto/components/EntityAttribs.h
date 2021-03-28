#pragma once

#include "../ecs/Component.h"

#include "../ecs/Entity.h"
#include "UI.h"
#include "HamsterStateMachine.h"
#include "EnemyStateMachine.h"


class EntityAttribs: public Component {
public:
	EntityAttribs();

	EntityAttribs(int life);

	EntityAttribs(int life, float range, Vector2D speed);

	virtual ~EntityAttribs() {
	}

	void init() override;

	bool recieveDmg(int dmg);

	void heal(int hp);

	void addCritProbability(float probability);

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
	inline int getAttackRange() const {
		return attackRange_;
	}
	inline int getDmg() const {
		return damage_;
	}
	inline Vector2D getVel() const {
		return velocity_;
	}

private:
	HamsterStateMachine* hms_;
	EnemyStateMachine*  enmState_;
	int health_;
	int maxHealth_;
	int damage_;

	float critProbability_;
	float maxCrit_;
	float critDamage_;
	float strokeResist_;
	float attackRange_;

	Vector2D velocity_;
};

