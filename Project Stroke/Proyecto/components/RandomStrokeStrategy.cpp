#include "RandomStrokeStrategy.h"


void RandomStrokeStrategy::increaseChanceAB(int n, int& chanceAB) {
	chanceAB += n;
	if (chanceAB > MAXCHANCEAB)
		chanceAB = MAXCHANCEAB;
}

void RandomStrokeStrategy::increaseChanceNORMAL(int n, int& chanceNORMAL) {
	chanceNORMAL += n;
	if (chanceNORMAL > MAXCHANCENORMAL)
		chanceNORMAL = MAXCHANCENORMAL;
}
//void RandomStrokeStrategy::decreaseChance() {
//
// }
bool RandomStrokeStrategy::checkChance(int chanceNORMAL, int chanceAB) {
	int i = r_.nextInt(1, MAXCHANCE);
	//std::cout << i << " -- " << chanceAB + chanceNORMAL << std::endl;
	return i <= chanceAB + chanceNORMAL;
}