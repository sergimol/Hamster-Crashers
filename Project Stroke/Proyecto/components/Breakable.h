#include "../ecs/Entity.h"

class Breakable: public Component {
public:
	Breakable() {};
	virtual ~Breakable() {};

	virtual void init() override;

	void hit();
private:

};