#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"

using namespace std;

class TriggerMusic : public Component {
public:
	TriggerMusic(string musicName):play(false),musicName_(musicName),tr_(nullptr) {
	};
	
	virtual ~TriggerMusic() {};

	virtual void init() override;

	virtual void update() override;
	virtual void render() override;


private:
	Transform* tr_;
	bool play;
	string musicName_;

};