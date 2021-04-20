#pragma once
#include "StrokeStrategy.h"


class FairStrokeStrategy: public StrokeStrategy {
public:
	virtual void increaseChanceAB(int n, int& chanceAB);
	virtual void increaseChanceNORMAL(int n, int& chanceNORMAL);

	//virtual void decreaseChance();
	virtual bool checkChance(int chanceNORMAL, int chanceAB);
private:

};