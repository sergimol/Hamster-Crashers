#include "Shadow.h"

void Shadow::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	state_ = entity_->getComponent<HamsterStateMachine>()->getState();

	shadow_ = new Entity(entity_->getMngr());

	//INICIALIZA SOMBRA CON VALORES DEL PADRE
	shadow_->addComponent<Transform>(Vector2D(tr_->getPos().getX(), tr_->getPos().getY()),
		Vector2D(), tr_->getW(), tr_->getH() / 3, 0.0f, 0, 1);
	shadow_->addComponent<Image>(&sdlutils().images().at("shadow"));
	shadow_->addComponent<ShadowFollow>(tr_);
}

//SIMPLEMENTE SE LLAMA A SU RENDER Y UPDATE
void Shadow::render() {
	shadow_->render();
}

void Shadow::update(){
	if(state_ != HamStates::INFARCTED)
		shadow_->update();
}