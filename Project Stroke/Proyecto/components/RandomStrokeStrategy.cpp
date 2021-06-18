#include "RandomStrokeStrategy.h"


void RandomStrokeStrategy::increaseChanceAB(int n, int& chanceAB) {
	/*chanceAB += n;
	if (chanceAB > MAXCHANCEAB)
		chanceAB = MAXCHANCEAB;*/

	chanceAB += n * EXTRAPERCENTAGE * 2;
}

void RandomStrokeStrategy::increaseChanceNORMAL(int n, int& chanceNORMAL) {
	/*chanceNORMAL += n;
	if (chanceNORMAL > MAXCHANCENORMAL)
		chanceNORMAL = MAXCHANCENORMAL;*/

	chanceNORMAL += n * EXTRAPERCENTAGE * 1.7f;
}
//void RandomStrokeStrategy::decreaseChance() {
//
// }
bool RandomStrokeStrategy::checkChance(int chanceNORMAL, int chanceAB) {
	//int i = 0;
	//i += r_.nextInt(1, MAXCHANCE);
	//i += r_.nextInt(1, MAXCHANCE);


	////std::cout << i << " -- " << chanceAB + chanceNORMAL << std::endl;
	//return i/2 < chanceAB + chanceNORMAL;
	return  chanceAB + chanceNORMAL >= MAXCHANCE;
}