// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

#include "Transform.h"

class Image: public Component {
public:
	Image(Texture *tex) :
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
		Vector2D renderPos = Vector2D(tr_->getPos().getX(), tr_->getPos().getY() - tr_->getZ());
		SDL_Rect dest = build_sdlrect(renderPos, tr_->getW(), tr_->getH());
		if(tr_->getFlip())
			tex_->render(dest, tr_->getRot(), SDL_FLIP_HORIZONTAL);
		else 
			tex_->render(dest, tr_->getRot());
		
	}

private:
	Transform *tr_;
	Texture *tex_;
};

