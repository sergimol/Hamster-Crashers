#pragma once

#include "StrokeStrategy.h"
#include "../sdlutils/SDLUtils.h"


class RandomStrokeStrategy: public StrokeStrategy {
public:
	virtual void increaseChanceAB(int n, int& chanceAB);
	virtual void increaseChanceNORMAL(int n, int& chanceNORMAL);
	//virtual void decreaseChance();
	virtual bool checkChance(int chanceNORMAL, int chanceAB);
private:
	// Generador de números aleatorios
	RandomNumberGenerator& r_ = sdlutils().rand();
	const int MAXCHANCENORMAL = 35;
	const int MAXCHANCEAB = 65;
	const float EXTRAPERCENTAGE = 9.0f;
};