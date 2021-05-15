#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Transform;

class Gravity : public Component
{
public:
	Gravity() : floor_(0), tr_(nullptr), gravityLocked_(false), lockTimer_(sdlutils().currRealTime()), lockCooldown_(500) {};

	virtual ~Gravity() {};

	void init() override;

	void checkHeight(SDL_Rect& playerPos);
	void onDisable() override;
	inline int getFloor() const { return floor_; };
	inline bool getStuck() const { return stuck_; };
	inline bool GetHeighCh() const { return inHeighChange_; };
	void lockGrav(bool b) { gravityLocked_ = b; };
	bool gravLocked() { return gravityLocked_; };
	void resetLockTimer() { lockTimer_ = sdlutils().currRealTime(); };
private:
	Transform* tr_;
	float floor_,
		gravity_ = 4.9,
		timer_ = 0,
		lockTimer_,
		lockCooldown_;
	const float jumpTimer_ = 0.15;
	bool stuck_ = false,
		 inHeighChange_=false,
		 gravityLocked_;
};

