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

const enum State { Players, GoingTo, Static, BossCat };
class Camera : public Component {
private:
	const float upOffset = -205;
	SDL_Rect camera_;
	Vector2D camPos;
	int players;
	float heightMap_= 0;
	float minH_ = 0;

	void followPlayer();
	void followBossCat();
	void Goto();
	void StaticCamera();
	bool followPlayers;		//Controla si quiero que la camara siga a los jugadores o a otro punto
	Vector2D newObjetivo();
	State cameraState;
	bool GoToTracker;
	void checkBounds();
	MapMngr* map_;

public:

	Camera(SDL_Rect cam) : camera_(cam), cameraFollowPos_(Vector2D()), cameraState(State::Players), map_(nullptr) {}

	virtual ~Camera() {}
	void init() override;
	void update() override;
	inline SDL_Rect getCam() const{ return camera_; };
	void changeCamFollowPos(int objetive);
	inline void changeCamState(State estado) { cameraState = estado; };
	inline State getCamState() const {return cameraState;};
	inline Vector2D getCamPos() const { return camPos; };
	inline float getUpOffset() const { return upOffset; };
	inline float getHeightMap() const { return heightMap_; };
	Vector2D cameraFollowPos_;	//Guarda el punto de la posición de la camara cuando lo lea

	void setGoToTracker(bool objetivo) {GoToTracker = objetivo;};
	
	inline void setMap(MapMngr* m) { map_ = m; };
};

/*
Como se supone que se van a leer capas de objetos por cada zona (o por sus propiedades), no hace falta
guardar un array de posiciones de la camara, puesto que cuando se entre en una nueva zona, solo habrá una nueva
posición de la camara a la que esta tendra que ir
*/

