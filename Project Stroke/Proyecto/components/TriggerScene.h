#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

using namespace std;

class TriggerScene : public Component {
public:
	TriggerScene(string newScene,int numTransition) :nameScene(newScene),  canChange(true), numT(numTransition) {
	};
	
	virtual ~TriggerScene() {};

	virtual void init() override;

	virtual void update() override;
	virtual void render() override;


private:
	string nameScene;
	Transform* tr_;
	bool canChange;
	int numT;
};