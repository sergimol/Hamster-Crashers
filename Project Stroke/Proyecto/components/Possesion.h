#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include <vector>

using namespace std;

class Possesion :public Component {
	Possesion() : possesed(nullptr) {};
	~Possesion() {};

	virtual void update() override;

	virtual void render() override;

	inline void setPossesed(Entity* e) { possesed = e; };

private:
	Entity* possesed;
	vector<Texture*> keys;
	Texture* linea;
	int mistakes = 0;
};