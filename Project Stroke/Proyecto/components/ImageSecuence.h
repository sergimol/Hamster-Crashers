#pragma once
// This file is part of the course TPV2@UCM - Alberto Muñoz

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include <stack>
#include <string>

using namespace std;

class ImageSecuence : public Component {
public:
	ImageSecuence(string newScene);
	
	virtual ~ImageSecuence() {}

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

private:
	stack<Entity*> keyAnimations;

	const string level1 = "Level1",
		level2 = "Level2",
		level3 = "Level3",
		level3Micro = "Level3Boss",
		final = "final",
		controls = "controls",
		hasMuerto = "hasMuerto",
		hasGanado = "hasGanado",
		level1Boss = "Level1Boss";

	string newScene_;

	bool next = false;

	bool controles = false;

	bool gameOver = false;

	Transition* trans_;
};