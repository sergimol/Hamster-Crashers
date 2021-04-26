#include "Parallax.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../ecs/Camera.h"
#include "BackGround.h"



Parallax::Parallax(Texture* im, float vel, Vector2D size, Vector2D pos)
{
	tex_ = im;
	pxVel_ = vel;
	texSize_ = size;
	texPos_ = pos;
}

//CREA LOS 3 BACKGROUNDS
void Parallax::init()
{
	auto backLeft = entity_->getMngr()->addBackGround();
	backLeft->addComponent<Transform>(texPos_, Vector2D(0, 0), texSize_.getX(), texSize_.getY(), 
											   0.0, 1, 1);
	backLeft->addComponent<BackGround>(tex_, pxVel_);
	leftTr_ = backLeft->getComponent<Transform>();
	assert(leftTr_ != nullptr);
	//central
	auto backCenter = entity_->getMngr()->addBackGround();
	backCenter->addComponent<Transform>(Vector2D(texPos_.getX() + texSize_.getX(), texPos_.getY()), Vector2D(0, 0), texSize_.getX(), texSize_.getY()
												 , 0.0, 1, 1);
	backCenter->addComponent<BackGround>(tex_, pxVel_);
	centerTr_ = backCenter->getComponent<Transform>();
	assert(centerTr_ != nullptr);
	//derecha
	auto backRight = entity_->getMngr()->addBackGround();
	backRight->addComponent<Transform>(Vector2D(texPos_.getX() + texSize_.getX()*2, texPos_.getY()), Vector2D(0, 0), texSize_.getX(), texSize_.getY(),
												0.0, 1, 1);
	backRight->addComponent<BackGround>(tex_, pxVel_);
	rightTr_ = backRight->getComponent<Transform>();
	assert(rightTr_ != nullptr);
}

void Parallax::update()
{
	//Comprobamos si ha llegado a alguna de las posiciones relativas y actualizamos
	checkRelativePos();
}

void Parallax::checkRelativePos()
{
	camPos_ = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCamPos();
	if (camPos_.getX() >= rightTr_->getPos().getX())
	{		
		leftTr_->setPos(Vector2D(leftTr_->getPos().getX() + leftTr_->getW(), leftTr_->getPos().getY()));
		centerTr_->setPos(Vector2D(centerTr_->getPos().getX() + centerTr_->getW(), leftTr_->getPos().getY()));
		rightTr_->setPos(Vector2D(rightTr_->getPos().getX() + rightTr_->getW(), leftTr_->getPos().getY()));
	}
	else if(camPos_.getX() <= centerTr_->getPos().getX())
	{
		leftTr_->setPos(Vector2D(leftTr_->getPos().getX() - leftTr_->getW(), leftTr_->getPos().getY()));
		centerTr_->setPos(Vector2D(centerTr_->getPos().getX() - centerTr_->getW(), leftTr_->getPos().getY()));
		rightTr_->setPos(Vector2D(rightTr_->getPos().getX() - rightTr_->getW(), leftTr_->getPos().getY()));
	}	
}