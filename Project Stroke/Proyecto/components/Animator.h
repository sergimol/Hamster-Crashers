// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"


class Animator : public Component {
public:
	Animator(Texture* tex, int w, int h, int c, int r, Uint32 f, Vector2D sf, int dur) :
		tr_(nullptr), //
		tex_(tex), //
		widthFrame(w), //
		heightFrame(h), //
		startFrame(sf), //
		textureFrame(sf), //
		cols(c), //
		rows(r), //
		frameUpdate(f), //
		lastTime(sdlutils().currRealTime()), //
		animCont(0), //
		animDuration(dur), //
		state_(nullptr)
	{
	}
	virtual ~Animator() {
	}

	void init() override;

	void render() override;

	//para actualizar la textura
	void update() override;

	void onResume() override;

	//Metodo que cambia de animacion sobre la spritesheet actual
	void play(Animation actualAnim);



	//Devuelve true o false en funcion si la animacion ha llegado al ultimo frame o no
	bool OnAnimationFrameEnd();

	//Devuelve true o false en funcion de si la animacion ha llegado al frame del parametro
	bool OnAnimationFrame(int targetFrame);

	//Devuelve true o false en funcion de si la animacion ha llegado al frame en el que
	//se activa el collider
	bool OnFinalAttackFrame();

	void setTexture(Texture* t);

private:
	//Variables de recursos
	Transform* tr_;
	Texture* tex_;
	GameStates* state_;

	//Timers para actualizar la spritsheet
	Uint32 lastTime;
	Uint32 frameUpdate;

	//Frame actual de la animacion
	Vector2D textureFrame;
	int animCont;

	//Frame de entrada
	Vector2D startFrame;
	//Frames que dura la animacion
	int animDuration;

	//Tamaño de los frames de la spritesheet
	int widthFrame;
	int heightFrame;

	//Filas y Columnas totales de la spritesheet
	int cols;
	int rows;


	//Comprobacion del loop
	bool looped;

	//Animacion encadenada
	std::string idChain;

	//Frame de ataque en caso de que lo tenga configurado
	int attackFrame;

};

