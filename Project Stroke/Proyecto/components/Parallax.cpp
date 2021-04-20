#include "Parallax.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../ecs/Camera.h"
#include "BackGround.h"



Parallax::Parallax(Texture* im, float vel) 
{
	//CREAMOS LOS 3 FONDOS
	//izquierda

	tex_ = im;
	pxVel_ = vel;
	
}

void Parallax::init()
{
	
	auto backLeft = entity_->getMngr()->addBackGround();
	backLeft->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 100, 1080, 0.0, 1, 1);
	backLeft->addComponent<BackGround>(tex_, pxVel_);
	leftTr_ = backLeft->getComponent<Transform>();
	//central
	auto backCenter = entity_->getMngr()->addBackGround();
	backCenter->addComponent<Transform>(Vector2D(100, 0), Vector2D(0, 0), 100, 1080, 0.0, 1, 1);
	backCenter->addComponent<BackGround>(tex_, pxVel_);
	centerTr_ = backCenter->getComponent<Transform>();
	//derecha
	auto backRight = entity_->getMngr()->addBackGround();
	backRight->addComponent<Transform>(Vector2D(200, 0), Vector2D(0, 0), 100, 1080, 0.0, 1, 1);
	backRight->addComponent<BackGround>(tex_, pxVel_);
	rightTr_ = backRight->getComponent<Transform>();
}

void Parallax::update()
{
	//Cogemos la posicion anterior de la camara
	Vector2D antPos = camPos_;

	//Cogemos la posicion actual de la camara
	camPos_ = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCamPos();


	//Comprobamos si ha llegado a alguna de las posiciones relativas y actualizamos
	if (checkRelativePos())
		updateRelativePos();

}

void Parallax::updateRelativePos()
{
	/*targetLeftPos = tr_->getPos().getX() - tr_->getW();
	targetRightPos = tr_->getPos().getX() + tr_->getW();
	actualLeftPos = targetLeftPos;
	actualRightPos = targetRightPos;*/
}

bool Parallax::checkRelativePos()
{
	/*float originPos = tr_->getPos().getX();
	if (originPos <= targetLeftPos || originPos >= targetRightPos)
		return true;
	else
		return false;*/
	return true;
}