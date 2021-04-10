#include "Swallow.h"
#include "../sdlutils/SDLUtils.h"

bool Swallow::canSwallow() {
	float i = sdlutils().rand().nextInt(1, 100);
	return (i <= swallowProbabilty_);
}