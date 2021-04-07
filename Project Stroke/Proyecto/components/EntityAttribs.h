#pragma once

#include "../ecs/Component.h"

#include "../ecs/Entity.h"
#include "UI.h"
#include "HeartUI.h"
#include "HamsterStateMachine.h"
#include "EnemyStateMachine.h"

const int INVENCIBLECD = 200;

class EntityAttribs: public Component {
public:
	EntityAttribs();

	EntityAttribs(int life, float range, std::string id, Vector2D speed, int number);

	virtual ~EntityAttribs() {
	}

	void init() override;

	bool recieveDmg(int dmg);

	void heal(int hp);

	void addCritProbability(float probability);

	void update() override;

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
	inline int getNumber() const {
		return playerNumber_;
	}
	inline Vector2D getVel() const {
		return velocity_;
	}
	inline std::string getId() const {
		return id_;
	}

private:
	HamsterStateMachine* hms_;
	EnemyStateMachine*  enmState_;
	
	int health_;
	int maxHealth_;
	int damage_;
	int playerNumber_;

	float critProbability_;
	float maxCrit_;
	float critDamage_;
	float strokeResist_;
	float attackRange_;
	float cadence_;

	//Variables para tener invulnerabilidad tras una habilidad
	bool invencible_;
	float time;

	std::string id_;

	Vector2D velocity_;
};

