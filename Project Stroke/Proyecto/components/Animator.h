// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../game/Game.h"

#include "Transform.h"
#include "EntityAttribs.h"

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
		animDuration(dur) //
	{
	}
	virtual ~Animator() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);

	}

	void render() override {

		//recurso
		Vector2D auxTextFrame = Vector2D();
		auxTextFrame.setX(widthFrame * textureFrame.getX());
		auxTextFrame.setY(heightFrame * textureFrame.getY());
		SDL_Rect src = build_sdlrect(auxTextFrame, widthFrame, heightFrame);

		//destino
		Vector2D renderPos = Vector2D(tr_->getPos().getX() - Game::camera_->getComponent<Transform>()->getPos().getX() , tr_->getPos().getY() - tr_->getZ() - Game::camera_->getComponent<Transform>()->getPos().getY());
		SDL_Rect dest = build_sdlrect(renderPos, tr_->getW(), tr_->getH());


		SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &dest);

		//Renderizado
		if (tr_->getFlip())
			tex_->render(src, dest, tr_->getRot(), nullptr, SDL_FLIP_HORIZONTAL);
		else
			tex_->render(src, dest, 0);


		//tex_->render(dest, tr_->getRot());
	}

	//para actualizar la textura
	void update() override {

		if (sdlutils().currRealTime() >= lastTime + frameUpdate)
		{

			lastTime = sdlutils().currRealTime();

			//SI NO SE HA ACABADO LA ANIMACION
			if (animCont < animDuration - 1)
			{
				//Si no hemos llegado al final de una fila seguimos avanzando
				if (textureFrame.getX() < cols - 1)
				{
					textureFrame.setX(textureFrame.getX() + 1);
				}
				//Si llegamos al final de la fila cambiamos
				else
				{
					textureFrame.setX(0);
					textureFrame.setY(textureFrame.getY() + 1);
				}
				animCont++;
			}
			//SI SE HA ACABADO Y HAY QUE LOOPEAR
			else if (looped)
			{
				animCont = 0;
				textureFrame.setX(startFrame.getX());
				textureFrame.setY(startFrame.getY());
			}
			//SI HAY QUE ENCADENAR OTRA ANIMACION
			else if (idChain != "")
				play(sdlutils().anims().at(idChain));

		}
	}

	//Metodo que cambia de animacion sobre la spritesheet actual
	void play(Animation actualAnim) 
	{
		frameUpdate = actualAnim.frameUpdate();
		startFrame = actualAnim.startFrame();
		animDuration = actualAnim.duration();
		textureFrame = startFrame;
		cols = actualAnim.cols();
		rows = actualAnim.rows();
		animCont = 0;
		looped = actualAnim.loop();
		idChain = actualAnim.chain();
	}

	

	//Devuelve true o false en funcion si la animacion ha llegado al ultimo frame o no
	bool OnAnimationFrameEnd() 
	{
		return animCont == animDuration-1;
	}

	//Devuelve true o false en funcion de si la animacion ha llegado al frame del parametro
	bool OnAnimationFrame(int targetFrame)
	{
		return animCont == targetFrame;
	}

private:
	//Variables de recursos
	Transform* tr_;
	Texture* tex_;

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

};

