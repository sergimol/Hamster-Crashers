#pragma once

class StrokeStrategy {
public:
	virtual void increaseChanceAB(int n, int& chanceAB) = 0;
	virtual void increaseChanceNORMAL(int n, int& chanceNORMAL) = 0;
	//virtual void decreaseChance() = 0;
	virtual bool checkChance(int chanceNORMAL, int chanceAB) = 0;

protected:
	const int MAXCHANCE = 100;
};