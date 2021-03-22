// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class DisableOnExit : public Component {

public:

	DisableOnExit();

	virtual ~DisableOnExit();

	void init() override;

	void update() override;

private:
	Transform* tr_;
};

