#pragma once
class Manager;

class System {
	friend Manager;
public:
	virtual ~System() { }
	void setMngr(Manager* manager) {
		manager_ = manager;
	}
	virtual void init() { }
	virtual void update() { }
protected:
	Manager* manager_;
};