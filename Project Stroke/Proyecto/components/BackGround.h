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

	bool trainMode_;
	int trainVel_;

public:
	BackGround(Texture* im, float vel, bool train);
	virtual ~BackGround() {};
	virtual void update();
};