
#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "GameStates.h"

class DisableOnExit : public Component {

public:

	DisableOnExit();

	virtual ~DisableOnExit();

	void init() override;

	void update() override;

private:
	Transform* tr_;
	GameStates* state_;
};

