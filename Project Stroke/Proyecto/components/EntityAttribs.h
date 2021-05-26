#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "UI.h"
#include "Dying.h"
#include "HeartUI.h"
#include "HamsterStateMachine.h"
#include "EnemyStateMachine.h"
#include "SoundManager.h"

const int INVINCIBLECD = 200;

class EntityAttribs: public Component {
public:
	EntityAttribs();
	EntityAttribs(int life, float range, std::string id, Vector2D speed, int number, float poisonProb, int dmg, int marg);
	EntityAttribs(int life, float range, std::string id, Vector2D speed, int number, float poisonProb, int dmg, bool igMargin, bool invincibilty, bool canBPois);

	virtual ~EntityAttribs();

	void init() override;

	void update() override;

	void onResume() override;

	bool recieveDmg(int dmg);

	void heal(int hp);

	void addCritProbability(float probability);

	void poison();

	void die();

	void setLife(int life);

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
	inline int getMarginToAttack() const {
		return marginToAttack;
	}
	inline bool getCanPoison() const {
		return canPoison_;
	}
	inline float getPoisonProb() const {
		return poisonProbability_;
	}
	inline bool getPoisoned() const {
		return poisoned_;
	}
	inline int getCriticProb() const {
		return critProbability_;
	}
	inline int getCriticDmg() const {
		return critDamage_;
	}
	inline bool checkInvulnerability() const {
		return (afterDamageInvul_ || invincibility_);
	}
	inline bool ignoresMargin() const{
		return ignoreMargin_;
	}


	//Setters
	inline void setId(std::string id) {
		id_ = id;
	}
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
	inline void setVel(Vector2D newVel) {
		velocity_ = newVel;
	}
	inline void resetVel() {
		velocity_ = maxVelocity_;
	}
	inline void setIgnoreMargin(bool i) {
		ignoreMargin_ = i;
	}
	inline void setDmg(int newDmg) {
		damage_ = newDmg;
	}

private:
	HamsterStateMachine* hms_;
	EnemyStateMachine*  enmState_;
	Texture* hmsText_;
	Transform* tr_;
	GameStates* state_;
	
	int playerNumber_;
	int health_;
	int maxHealth_;
	int damage_;
	int poisonDamage_;
	int marginToAttack;
	/*int lightAttCadence_;
	int strongAttCadence_;*/

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
	bool canBePoisoned_;
	bool poisoned_;
	float poisonTime_;
	float timeLastUpdate_;
	int poisonCD_;
	int updateCD_;

	bool allDead;

	std::string id_;

	Vector2D velocity_;
	Vector2D maxVelocity_;
};

