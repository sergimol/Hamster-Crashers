#pragma once
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class Parallax : public Component
{
private:
	//porcentaje de velocidad a la que va el parallax, respectivo a la camara
	float pxVel_;
	//Textura del fondo
	Texture* tex_;

	//Posicion de la camara
	Vector2D camPos_;

	//Comprueba que el parallax se ha movido hasta alguna
	//actualiza las posiciones en ese caso
	void checkRelativePos();

	//Accesos a Transforms de los 3 fondos
	Transform* leftTr_;
	Transform* centerTr_;
	Transform* rightTr_;

	//Tamaño textura
	Vector2D texSize_;

	//Posicion relativa de los backgrounds
	Vector2D texPos_;

	//Para que se rendericen por delante
	bool front_ = false;

public:
	Parallax(Texture* im, float vel, Vector2D size, Vector2D pos, bool front);
	virtual ~Parallax() {};
	virtual void update();
	virtual void init();

};