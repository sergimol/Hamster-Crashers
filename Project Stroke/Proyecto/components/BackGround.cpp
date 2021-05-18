#include "BackGround.h"

BackGround::BackGround(Texture* im, float vel) : Image(im)
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

	//Cogemos la posicion actual de la camara
	camPos_ = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCamPos();

	//Movemos el background en sentido contrario en funcion de la camara
	tr_->setPos(Vector2D(tr_->getPos().getX() - (camPos_.getX() - antPos.getX())*pxVel_/100, tr_->getPos().getY()));
	



}
