#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "ContactDamage.h"
#include "Image.h"
using namespace std;
class TimeTrap: public Component {
public:
	TimeTrap(Texture* tx, Texture* txoff, float latencia);
	//TimeTrap(string id, short int hits) : id_(id), hits_(hits) {};
	virtual ~TimeTrap();
	
	virtual void init() override;

	void update() override;
	void render() override;

private:
	Transform* tr_;
	string id_;
	const string keyWord_ = "obstacle", hitWord_ = "Hit", breakWord_ = "Break";
	float latency;


	int alpha;
	Texture* texON_;
	Texture* texOFF_;
	float alphaCalc;


	GameStates* gamestate;
	float time_, lastTime_;
	bool  activado;

};