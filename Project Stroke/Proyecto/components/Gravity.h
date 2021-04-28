#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Transform;

class Gravity : public Component
{
public:
	Gravity() : floor_(0), tr_(nullptr) {};

	virtual ~Gravity() {};

	void init() override;

	void checkHeight(SDL_Rect& playerPos);
	void onDisable() override;
	inline int getFloor() const { return floor_; };
	inline bool getStuck() const { return stuck_; };
private:
	Transform* tr_;
	float floor_;
	const float gravity_ = 4.9;
	float timer = 0;
	const float jumpTimer_ = 0.15;
	bool stuck_ = false;
};

