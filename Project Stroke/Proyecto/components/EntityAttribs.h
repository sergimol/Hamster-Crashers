#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "UI.h"
#include "Dying.h"
#include "HeartUI.h"
#include "HamsterStateMachine.h"
#include "EnemyStateMachine.h"

const int INVINCIBLECD = 200;
const int MARGINTOATTACK = 70;

class EntityAttribs: public Component {
public:
	EntityAttribs();
	EntityAttribs(int life, float range, std::string id, Vector2D speed, int number, float poisonProb, int dmg);
	EntityAttribs(int life, float range, std::string id, Vector2D speed, int number, float poisonProb, int dmg, bool igMargin, bool invincibilty);

	virtual ~EntityAttribs() {
	}

	void init() override;

	void update() override;

	bool recieveDmg(int dmg);

	void heal(int hp);

	void addCritProbability(float probability);

	void poison();

	void die();

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
	inline bool getCanPoison() {
		return canPoison_;
	}
	inline float getPoisonProb() {
		return poisonProbability_;
	}
	inline bool getPoisoned() {
		return poisoned_;
	}
	inline int getCriticProb() const {
		return critProbability_;
	}
	inline int getCriticDmg() const {
		return critDamage_;
	}
	inline bool checkInvulnerability() {
		return (afterDamageInvul_ || invincibility_);
	}
	inline bool ignoresMargin() {
		return ignoreMargin_;
	}

	//Setters
	inline void setPoisonProb(float prob) {
		poisonProbability_ = prob;
	}
	inline void activatePoison(bool b) {
		canPoison_ = b;
	}
	inline void resetCriticProb() {
		critProbability_ = 0.05;
	}
	inline void setInvincibility(bool i) {
		invincibility_ = i;
	}

private:
	HamsterStateMachine* hms_;
	EnemyStateMachine*  enmState_;
	Texture* hmsText_;
	Transform* tr_;
	
	int health_;
	int maxHealth_;
	int damage_;
	int poisonDamage_;
	int playerNumber_;

	float critProbability_;
	float poisonProbability_;
	float maxCrit_;
	float critDamage_;
	float strokeResist_;
	float attackRange_;
	bool ignoreMargin_;
	float cadence_;

	//Variables para tener invulnerabilidad tras una habilidad
	bool invincibility_;
	bool afterDamageInvul_;
	float damageInvulTime_;

	bool canPoison_;
	bool poisoned_;
	float poisonTime_;
	float timeLastUpdate_;
	int poisonCD_;
	int updateCD_;

	std::string id_;

	Vector2D velocity_;
};

