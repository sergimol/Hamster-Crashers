#include "MenuAnim.h"

MenuAnim::MenuAnim()
{
	lastTime = sdlutils().currRealTime();
	dest = build_sdlrect(0, 0, 1920, 1080);
}

void  MenuAnim::init() {
	for (int i = 0; i <= 30; i++) {
		auto thisText = &sdlutils().images().at("ma" + to_string(i));
		textures_[i] = thisText;
	}
}

void MenuAnim::render()
{
	if (sdlutils().currRealTime() >= lastTime + frameUpdate)
	{
		textNum++;



		if (textNum == 22 && repetitions == 0) {
			repetitions = 3;
		}
		else if (textNum == 22 && repetitions != 0) {
			repetitions--;
			textNum = 19;
		}

		if (textNum == 27 && repetitions == 0) {
			repetitions = 20;
		}
		else if (textNum == 27 && repetitions != 0) {
			repetitions--;
			textNum = 25;
		}
		

		//loop normal
		if (textNum > 30)
			textNum = 19;
		lastTime = sdlutils().currRealTime();
	}

	textures_[textNum]->render(dest);

}
