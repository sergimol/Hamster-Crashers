// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
//Daño por bala
const int DMG = 2;

class Cloud : public Component {

public:

	Cloud(int dmg) : dmg_(dmg), tr_(nullptr) {};

	virtual ~Cloud() {};

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;
private:
	int dmg_;
	Transform* tr_;
};

