#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "GameStates.h"
#include <vector>

class Cloud : public Component {

public:

	Cloud(int dmg) : dmg_(dmg), tr_(nullptr), state_(nullptr) {};

	virtual ~Cloud();

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;
private:
	void refreshAffectedEnemies();
	int dmg_;
	Transform* tr_;
	SDL_Rect cam_;
	GameStates* state_;
	std::vector<Entity*> affectedEnemies_;
};

