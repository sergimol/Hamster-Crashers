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
#include <SDL_rect.h>
#include "../components/MapMngr.h"

const enum State { Players, GoingTo, Static };
class Camera : public Component {
private:
	SDL_Rect camera_;
	Vector2D camPos;
	int players;

	void followPlayer();
	void Goto();
	void StaticCamera();
	bool followPlayers;		//Controla si quiero que la camara siga a los jugadores o a otro punto
	Vector2D newObjetivo();
	State cameraState;
	bool GoToTracker;
public:

	Camera(SDL_Rect cam) : camera_(cam), CameraFollowPos(Vector2D()), cameraState(Players) {}

	virtual ~Camera() {}
	void update() override;
	inline SDL_Rect getCam() const{ return camera_; };
	void changeCamState(State estado) { cameraState = estado; };
	void changeCamFollowPos(Vector2D objetive);
	inline State getCamState() {return cameraState;};
	inline Vector2D getCamPos() { return camPos; };
	//void changeState(enum state) { cameraState = state ; };
	Vector2D CameraFollowPos;	//Guarda el punto de la posición de la camara cuando lo lea

	void setGoToTracker(bool objetivo) {GoToTracker = objetivo;};

};

/*
Como se supone que se van a leer capas de objetos por cada zona (o por sus propiedades), no hace falta
guardar un array de posiciones de la camara, puesto que cuando se entre en una nueva zona, solo habrá una nueva
posición de la camara a la que esta tendra que ir
*/

