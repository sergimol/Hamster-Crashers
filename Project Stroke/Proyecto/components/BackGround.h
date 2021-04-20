#pragma once
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "Image.h"

class BackGround : public Image
{
private:
	//porcentaje de velocidad a la que va el parallax, respectivo a la camara
	float pxVel_;
	//Posicion de la camara
	Vector2D camPos_;
	//Textura del fondo
	Texture* tex_;


public:
	BackGround(Texture* im, float vel);
	virtual ~BackGround() {};
	virtual void update();
};