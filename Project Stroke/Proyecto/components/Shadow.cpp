#include "Shadow.h"

void Shadow::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	gState_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(gState_ != nullptr);

	shadow_ = new Entity(entity_->getMngr());

	if (isHamster_)
		hamS_ = entity_->getComponent<HamsterStateMachine>()->getState();
	else
		enemyS_ = entity_->getComponent<EnemyStateMachine>()->getState();


	//INICIALIZA SOMBRA CON VALORES DEL PADRE
	shadow_->addComponent<Transform>(Vector2D(tr_->getPos().getX(), tr_->getPos().getY()),
		Vector2D(), tr_->getW(), tr_->getH() / 3, 0.0f, 0, 1);
	shadow_->addComponent<Image>(&sdlutils().images().at("shadow"));
	shadow_->addComponent<ShadowFollow>(tr_, useCollision_);
}

//SIMPLEMENTE SE LLAMA A SU RENDER Y UPDATE
void Shadow::render() {
	if (gState_->getState() != GameStates::MAINMENU)
		shadow_->render();
}

void Shadow::update() {
	if (gState_->getState() == GameStates::RUNNING) {
		if (isHamster_ && hamS_ != HamStates::INFARCTED)
			shadow_->update();
		else if (!isHamster_)
			shadow_->update();
	}
}