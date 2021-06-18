#include "FairStrokeStrategy.h"
#include "iostream"


void FairStrokeStrategy::increaseChanceAB(int n, int& chanceAB) {
	chanceAB += n * EXTRAPERCENTAGE * 2;
}

void FairStrokeStrategy::increaseChanceNORMAL(int n, int& chanceNORMAL) {
	chanceNORMAL += n * EXTRAPERCENTAGE * 1.5f;
}
//void FairStrokeStrategy::decreaseChance() {
//
//}
bool FairStrokeStrategy::checkChance(int chanceNORMAL, int chanceAB) {
	//std::cout << " -- " << chanceAB + chanceNORMAL << std::endl;

	return  chanceAB + chanceNORMAL >= MAXCHANCE;
}