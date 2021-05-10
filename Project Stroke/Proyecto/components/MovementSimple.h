#pragma once

#include "../ecs/Component.h"
#include <map>
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "Animator.h"
#include "EntityAttribs.h"
#include "EnemyStateMachine.h"
#include "CollisionDetec.h"
#include "../utils/checkML.h"

class MovementSimple : public Component {
public:

	const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	MovementSimple() :
		tr_(nullptr), speed_(), enmState_(nullptr), goalVel_(0, 0), lastDir_(1,0), timer(sdlutils().currRealTime()), colDetec_(nullptr),
		grav_(nullptr)
	{
	}

	virtual ~MovementSimple() {
	}

	void init() override;

	void update() override;

	void updateKeymap(KEYS x, bool is);

	float lerp(float a, float b, float f);

	virtual void onEnable() override;
	virtual void onDisable() override;
	void onResume() override;
	inline Vector2D getLastDir() { return lastDir_; };

	inline Vector2D getSpeed() const { return speed_; };
	inline void setSpeed(Vector2D s) { speed_ = s; };

protected:
private:

	const float jump_ = 45.0f, gravity_ = 4.8f, jumpTimer_ = 10.0f;
	long unsigned int timer;

	Gravity* grav_;
	Transform* tr_;
	EnemyStateMachine* enmState_;
	//Animator* anim_;
	Vector2D speed_, goalVel_, lastDir_;
	
	std::map<KEYS, bool> keymapSimple_;

	CollisionDetec* colDetec_;

	GameStates* state_;
};

