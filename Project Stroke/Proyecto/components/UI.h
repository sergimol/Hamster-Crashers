#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include <map>
#include <cmath>

#include "Transform.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "Life.h"


class UI : public Component {
public:
	UI(Texture* face);
	virtual ~UI() {};

	void render() override;
	void changeText();
private:
	Texture* face_;
	Texture* hearth_;
	Texture* bar_;
};
