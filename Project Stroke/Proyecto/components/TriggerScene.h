#pragma once

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