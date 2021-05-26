#include "Creditos.h"
#include "GameStates.h"
#include "MapMngr.h"
#include "MenuButtonManager.h"
#include "MenuButton.h"
#include "MenuIndicator.h"
#include "../ecs/Camera.h"

void Creditos::init() {
	imRect_.w = tex_->width();
	imRect_.h = tex_->height();
	imRect_.x = 0;
	imRect_.y = 0;
	timer = sdlutils().currRealTime();
}

void Creditos::update() {
	if (sdlutils().currRealTime() > timer + UPDATE && scrolling) {
		imRect_.y -= 1;
		timer = sdlutils().currRealTime();
	}
	else if (!scrolling && sdlutils().currRealTime() > timer + ENDWAIT) {
		backToMenu();
		entity_->removeComponent<Creditos>();
	}
	if (imRect_.y == -imRect_.w + 1080 && scrolling) {
		scrolling = false;
		timer = sdlutils().currRealTime();
	}
}

void Creditos::backToMenu() {
	entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->resetCamera();
	//Vuelve a renderizar el menu
	entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>()->setState(GameStates::MAINMENU);

	//Eliminamos a todos los hamsters
	entity_->getMngr()->getHandler<Map>()->getComponent<MapMngr>()->clearHamstersVector();

	sdlutils().setHamstersChosen(0);
	sdlutils().setHamstersToChoose(0);

	auto* hsm = entity_->getMngr()->getHandler<HamsterSelectionMenu>()->getComponent<MenuButtonManager>();

	auto& i = hsm->getIndicators();
	auto& but = hsm->getButtons();
	for (int h = 1; h < i.size(); h++) {
		i[h]->setActive(false);
	}

	for (int j = 0; j < but.size(); ++j) {
		auto mb = but[j][0]->getComponent<MenuButton>();
		if (mb->getName() != "angel" || sdlutils().angelUnlocked())
			mb->setSelectable(true);
	}

	i[0]->getComponent<MenuIndicator>()->reset();

	entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->changeCamState(State::Players);
}

void Creditos::render() {
	tex_->render(imRect_);
}