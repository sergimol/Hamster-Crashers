// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

class Entity;

class Component {
public:
	Component() :
			entity_(nullptr), active_(true) {
	}

	virtual ~Component() {
	}

	inline void setEntity(Entity *e) {
		entity_ = e;
	}

	inline Entity* getEntity() {
		return entity_;
	}

	inline void setActive(bool act) {
		active_ = act;
		if (!act) onDisable();
		else onEnable();
	}

	inline bool isActive() {
		return active_;
	}

	virtual void init() {
	}

	virtual void update() {
	}

	virtual void render() {
	}

	virtual void onDisable() {
	}

	virtual void onEnable() {
	}

	virtual void onResume() {
	}

protected:
	Entity *entity_;
	bool active_;
};

