#pragma once
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "Image.h"

class MenuAnim : public Component
{
private:
	//variable textura
	int textNum = 0;
	//Variables timer
	int frameUpdate = 100;
	int lastTime;
	int repetitions = 0;

	//DestRects
	SDL_Rect dest;

	//Textura del fondo
	Texture* textures_[31];

	/*Texture* tex0_ = &sdlutils().images().at("ma0");
	Texture* tex1_ = &sdlutils().images().at("ma1");
	Texture* tex2_ = &sdlutils().images().at("ma2");
	Texture* tex3_ = &sdlutils().images().at("ma3");
	Texture* tex4_ = &sdlutils().images().at("ma4");
	Texture* tex5_ = &sdlutils().images().at("ma5");
	Texture* tex6_ = &sdlutils().images().at("ma6");
	Texture* tex7_ = &sdlutils().images().at("ma7");
	Texture* tex8_ = &sdlutils().images().at("ma8");
	Texture* tex9_ = &sdlutils().images().at("ma9");
	Texture* tex10_ = &sdlutils().images().at("ma10");
	Texture* tex11_ = &sdlutils().images().at("ma11");
	Texture* tex12_ = &sdlutils().images().at("ma12");
	Texture* tex13_ = &sdlutils().images().at("ma13");
	Texture* tex14_ = &sdlutils().images().at("ma14");
	Texture* tex15_ = &sdlutils().images().at("ma15");
	Texture* tex16_ = &sdlutils().images().at("ma16");
	Texture* tex17_ = &sdlutils().images().at("ma17");
	Texture* tex18_ = &sdlutils().images().at("ma18");
	Texture* tex19_ = &sdlutils().images().at("ma19");
	Texture* tex20_ = &sdlutils().images().at("ma20");
	Texture* tex21_ = &sdlutils().images().at("ma21");
	Texture* tex22_ = &sdlutils().images().at("ma22");
	Texture* tex23_ = &sdlutils().images().at("ma23");
	Texture* tex24_ = &sdlutils().images().at("ma24");
	Texture* tex25_ = &sdlutils().images().at("ma25");
	Texture* tex26_ = &sdlutils().images().at("ma26");
	Texture* tex27_ = &sdlutils().images().at("ma27");
	Texture* tex28_ = &sdlutils().images().at("ma28");
	Texture* tex29_ = &sdlutils().images().at("ma29");
	Texture* tex30_ = &sdlutils().images().at("ma30");*/


public:
	MenuAnim();
	virtual ~MenuAnim() {};
	void init() override;
	virtual void render();
};