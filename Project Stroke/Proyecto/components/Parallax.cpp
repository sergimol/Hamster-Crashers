#include "Parallax.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../ecs/Camera.h"
#include "BackGround.h"



Parallax::Parallax(Texture* im, float vel, Vector2D size, Vector2D pos, bool front, bool trainMod)
{
	tex_ = im;
	pxVel_ = vel;
	texSize_ = size;
	texPos_ = pos;
	front_ = front;
	trainMod_ = trainMod;
}

//CREA LOS 3 BACKGROUNDS
void Parallax::init()
{
	//izquierda
	Entity* backLeft = nullptr;
	if (front_) backLeft = entity_->getMngr()->addFrontGround();
	else backLeft = entity_->getMngr()->addBackGround();
	backLeft->addComponent<Transform>(texPos_, Vector2D(0, 0), texSize_.getX(), texSize_.getY(),
		0.0, 1, 1);
	backLeft->addComponent<BackGround>(tex_, pxVel_, trainMod_);
	leftTr_ = backLeft->getComponent<Transform>();
	assert(leftTr_ != nullptr);

	//central
	Entity* backCenter = nullptr;
	if (front_) backCenter = entity_->getMngr()->addFrontGround();
	else backCenter = entity_->getMngr()->addBackGround();
	backCenter->addComponent<Transform>(Vector2D(texPos_.getX() + texSize_.getX(), texPos_.getY()), Vector2D(0, 0), texSize_.getX(), texSize_.getY()
		, 0.0, 1, 1);
	backCenter->addComponent<BackGround>(tex_, pxVel_, trainMod_);
	centerTr_ = backCenter->getComponent<Transform>();
	assert(centerTr_ != nullptr);

	//derecha
	Entity* backRight = nullptr;
	if (front_) backRight = entity_->getMngr()->addFrontGround();
	else backRight = entity_->getMngr()->addBackGround();
	backRight->addComponent<Transform>(Vector2D(texPos_.getX() + texSize_.getX() * 2, texPos_.getY()), Vector2D(0, 0), texSize_.getX(), texSize_.getY(),
		0.0, 1, 1);
	backRight->addComponent<BackGround>(tex_, pxVel_, trainMod_);
	rightTr_ = backRight->getComponent<Transform>();
	assert(rightTr_ != nullptr);

	camOffset_ = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getUpOffset();
}

void Parallax::update()
{
	//Comprobamos si ha llegado a alguna de las posiciones relativas y actualizamos
	checkRelativePos();
}

void Parallax::checkRelativePos()
{
	camPos_ = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

	//Calcula la futura y
	float y = entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>()->getMaxH() - camPos_.h + camOffset_ - 380;

	//Si se llega al principio o al final se rotan llas tres imágenes
	if (camPos_.x >= rightTr_->getPos().getX())
	{
		leftTr_->getPos().setX(leftTr_->getPos().getX() + leftTr_->getW());
		centerTr_->getPos().setX(centerTr_->getPos().getX() + centerTr_->getW());
		rightTr_->getPos().setX(rightTr_->getPos().getX() + rightTr_->getW());
	}
	else if (camPos_.x <= centerTr_->getPos().getX())
	{
		leftTr_->getPos().setX(leftTr_->getPos().getX() - leftTr_->getW());
		centerTr_->getPos().setX(centerTr_->getPos().getX() - centerTr_->getW());
		rightTr_->getPos().setX(rightTr_->getPos().getX() - rightTr_->getW());
	}

	//Actualizamos la y
	if (!front_) {
		leftTr_->getPos().setY(sdlutils().lerp(y, leftTr_->getPos().getY(), 0.98));
		centerTr_->getPos().setY(sdlutils().lerp(y, leftTr_->getPos().getY(), 0.98));
		rightTr_->getPos().setY(sdlutils().lerp(y, leftTr_->getPos().getY(), 0.98));
	}
}