#include "NewScene.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../components/MapMngr.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../ecs/Camera.h"
#include "../sdlutils/SDLUtils.h"

void NewScene::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void NewScene::update() {
	for (Entity* hamsters : entity_->getMngr()->getPlayers()) {
		//Cogemos la posicion de cada hamster...
		auto hamsterTr = hamsters->getComponent<Transform>();

		//Cogemos la camara para hacer bien las colisiones
		SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

		if (!Collisions::collides(Vector2D(hamsterTr->getPos().getX()-cam.x , hamsterTr->getPos().getY()-cam.y), hamsterTr->getW(), hamsterTr->getH(),
			tr_->getPos(), tr_->getW(), tr_->getH())) {
			canChange = false;
		}
	}

	//Si todos los hamsters estan en el trigger
	if (canChange)
		//Cambio de escena
		ChangeScene();
	else
		canChange = true;
}

void NewScene::render() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);
}
void NewScene::ChangeScene() {

	//Desactivamos todas las entidades (Salvo la cámara)
	for (Entity* e : entity_->getMngr()->getEntities()) {
		//Si la entidad que voy a coger no es la camara...
		if (e->getMngr()->getHandler<Camera__>() != e)
			//La elimino
			e->setActive(false);
	}

	for (Entity* e : entity_->getMngr()->getTiles())
		e->setActive(false);

	for (Entity* e : entity_->getMngr()->getMapH())
		e->setActive(false);

	for (Entity* e : entity_->getMngr()->getBgs())
		e->setActive(false);

	entity_->getMngr()->refreshDeadBodies();
	entity_->getMngr()->refreshEnemies();
	//mngr_->refreshItems();
	entity_->getMngr()->refreshObstacles();
	entity_->getMngr()->refreshPlayers();

	//Y creamos uno nuevo
	auto* mapa = entity_->getMngr()->addEntity();
	mapa->addComponent<MapMngr>();
	mapa->getComponent<MapMngr>()->loadNewMap("resources/images/tiled/" + nameScene);

	//Metemos al mapa en el Handler de Map
	entity_->getMngr()->setHandler<Map>(mapa);
}