#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"

const enum class ItemType
{
	Apple,
	WaterMelon,
	Nut
};

class Item : public Component {
public:
	Item(ItemType t) : type_(t) {};

	virtual ~Item() {};

	inline ItemType getItem() { return type_; };
private:
	ItemType type_;
};

