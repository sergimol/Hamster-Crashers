#include "Shadow.h"

void Shadow::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	if(isHamster_)
		hamS_ = entity_->getComponent<HamsterStateMachine>()->getState();
	else
		enemyS_ = entity_->getComponent<EnemyStateMachine>()->getState();

	shadow_ = new Entity(entity_->getMngr());

	//INICIALIZA SOMBRA CON VALORES DEL PADRE
	shadow_->addComponent<Transform>(Vector2D(tr_->getPos().getX(), tr_->getPos().getY()),
		Vector2D(), tr_->getW(), tr_->getH() / 3, 0.0f, 0, 1);
	shadow_->addComponent<Image>(&sdlutils().images().at("shadow"));
	shadow_->addComponent<ShadowFollow>(tr_, useCollision_);
}

//SIMPLEMENTE SE LLAMA A SU RENDER Y UPDATE
void Shadow::render() {
	shadow_->render();
}

void Shadow::update(){
	if(isHamster_ && hamS_ != HamStates::INFARCTED)
		shadow_->update();
	else if (!isHamster_)
		shadow_->update();
}