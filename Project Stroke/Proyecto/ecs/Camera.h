// This file is part of the course TPV2@UCM - Samir Genaim
#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>


#include "Component.h"
#include "ecs.h"

#include "Entity.h"
#include "Manager.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include <SDL_rect.h>


class Camera : public Component {
public:

	Camera(SDL_Rect cam) : camera_(cam),CameraFollowPos(Vector2D(-10000,-200)){}

	virtual ~Camera() {}
	void update() override;
	SDL_Rect getCam() { return camera_; };
	void setFollow(bool follow) { followPlayers = follow; };
	//Para activar el setFollow
	//entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->setFollow(true);
	Vector2D CameraFollowPos;	//Guarda el punto de la posición de la camara cuando lo lea
private:
	SDL_Rect camera_;
	Vector2D camPos;
	int players;

	void followPlayer();
	void Goto(Vector2D);
	bool followPlayers;		//Controla si quiero que la camara siga a los jugadores o a otro punto
};

/*
Como se supone que se van a leer capas de objetos por cada zona (o por sus propiedades), no hace falta
guardar un array de posiciones de la camara, puesto que cuando se entre en una nueva zona, solo habrá una nueva
posición de la camara a la que esta tendra que ir
*/

