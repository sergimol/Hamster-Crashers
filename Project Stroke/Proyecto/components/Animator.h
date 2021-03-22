// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../game/Game.h"

#include "Transform.h"

class Animator : public Component {
public:
	Animator(Texture* tex, int w, int h, int c, int r, Uint32 f, Vector2D sf, Vector2D ef) :
		tr_(nullptr), //
		tex_(tex), //
		widthFrame(w), //
		heightFrame(h), //
		startFrame(sf), //
		endFrame(ef), //
		textureFrame(sf), //
		cols(c), //
		rows(r), //
		frameUpdate(f), //
		lastTime(sdlutils().currRealTime()) //
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
		Vector2D renderPos = Vector2D(tr_->getPos().getX() - Game::camera_.x, tr_->getPos().getY() - tr_->getZ() - Game::camera_.y);
		SDL_Rect dest = build_sdlrect(renderPos, tr_->getW(), tr_->getH());

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

			//si llegamos al final de una fila
			if (textureFrame.getX() >= 2) //habia puesto textureFrame.getX() >= cols-1
			{
				//si estamos en la ultima fila
				if (textureFrame.getY() >= endFrame.getY()) //habia puesto textureFrame.getY() >= rows-1
				{
					//reseteamos
					//textureFrame.setX(0);
					//textureFrame.setY(0);
					textureFrame.setX(startFrame.getX());
					textureFrame.setY(startFrame.getY());
				}
				//Si no lo estamos
				else
				{
					//Empezamos a recorrer la siguiente fila
					textureFrame.setX(0);
					textureFrame.setY(textureFrame.getY() + 1);
				}
			}
			//Si no llegamos al final de una fila, seguimos avanzando por la fila
			else
				textureFrame.setX(textureFrame.getX() + 1);

		}
	}

	//Metodo que cambia de animacion sobre la spritesheet actual
	void play(Vector2D sFrame, Vector2D eFrame, Uint32 fU) 
	{
		frameUpdate = fU;
		startFrame = sFrame;
		endFrame = eFrame;
		textureFrame = startFrame;
	}

private:
	Transform* tr_;
	Texture* tex_;

	Uint32 lastTime;
	Uint32 frameUpdate;

	Vector2D textureFrame;

	Vector2D startFrame;
	Vector2D endFrame;

	int widthFrame;
	int heightFrame;
	int cols;
	int rows;
};

