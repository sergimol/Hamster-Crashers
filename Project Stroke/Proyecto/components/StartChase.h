#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

using namespace std;

class StartChase : public Component {
public:
	StartChase() {
	};
	
	virtual ~StartChase() {};

	virtual void init() override;

	virtual void update() override;
	virtual void render() override;

	void start();


private:
	Transform* tr_;
};