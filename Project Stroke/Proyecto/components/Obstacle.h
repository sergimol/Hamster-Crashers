#include "../ecs/Entity.h"
using namespace std;
class Obstacle: public Component {
public:
	Obstacle(string id) : id_(id) {};
	Obstacle(string id, short int hits) : id_(id), hits_(hits) {};
	virtual ~Obstacle();
	virtual void init() override;
	void hit();
private:
	Transform* tr_;
	string id_;
	const string keyWord_ = "obstacle", hitWord_ = "Hit", breakWord_ = "Break";
	short int hits_ = -1;
	//Marca si el objeto está muerto o no
	bool canBeHit_ = true;

	void createItem();
};