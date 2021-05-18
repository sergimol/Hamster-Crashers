#include "../ecs/Entity.h"


#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
using namespace std;
class LifeTime: public Component {
public:
	LifeTime(float lifeTime) : lastTime_(0), lifeTime_(lifeTime), time_(0),
		gamestate(nullptr)
	{}
	virtual ~LifeTime() {};
	virtual void init() override;
	void update() override;
private:
	float
		time_,
		lastTime_,

		lifeTime_;

	GameStates* gamestate;
};