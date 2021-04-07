#pragma once
#include "../ecs/Component.h"

class HeightObject : public Component
{
public:
	HeightObject():height(0) {}

	inline int getZ() { return height; }

	inline void setZ(int nZ) { height = nZ; }
private:
	int height;
};

