// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "EntityAttribs.h"
#include "Transform.h"

class Image : public Component {
public:
	Image(Texture* tex) :
		tr_(nullptr), //
		tex_(tex) //
	{
	}
	virtual ~Image() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void render() override {
		Vector2D renderPos = Vector2D(tr_->getPos().getX() - Game::camera_.x, tr_->getPos().getY() + tr_->getZ() - Game::camera_.y);
		SDL_Rect dest = build_sdlrect(renderPos, tr_->getW(), tr_->getH());

		SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &dest);


		EntityAttribs* attribs = entity_->getComponent<EntityAttribs>();

		//Color verdoso cuando está envenenado
		if(attribs != nullptr && attribs->getPoisoned())
			SDL_SetTextureColorMod(tex_->getSDLText(), 148, 236, 130);
		else
			SDL_SetTextureColorMod(tex_->getSDLText(), 255, 255, 255);

		if (tr_->getFlip())
			tex_->render(dest, tr_->getRot(), SDL_FLIP_HORIZONTAL);
		else
			tex_->render(dest, tr_->getRot());

		//std::cout << renderPos.getX() << " " << renderPos.getY() << "\n";
	}

private:
	Transform* tr_;
	Texture* tex_;
};

