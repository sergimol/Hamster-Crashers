#include "BackGround.h"

BackGround::BackGround(Texture* im, float vel, bool train) : Image(im), trainVel_(85), trainMode_(train)
{
	//Asignamos la textura
	tex_ = im;

	//Asignamos la velocidad
	pxVel_ = vel;

}

void BackGround::update()
{
	//Cogemos la posicion anterior de la camara
	Vector2D antPos = camPos_;

	if (!trainMode_) {
		//Cogemos la posicion actual de la camara
		camPos_ = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCamPos();
	}
	else {
		camPos_ = camPos_ + Vector2D(trainVel_,0);
	}
	//Movemos el background en sentido contrario en funcion de la camara
	tr_->setPos(Vector2D(tr_->getPos().getX() - (camPos_.getX() - antPos.getX()) * pxVel_ / 100, tr_->getPos().getY()));
}
