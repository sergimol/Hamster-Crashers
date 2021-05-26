#include "TimeTrap.h"
#include "Animator.h"
#include "SoundManager.h"
#include "../ecs/Manager.h"
#include "Dying.h"

TimeTrap::TimeTrap(Texture* tx, Texture* txoff, float latencia) : latency(latencia), texON_(tx), texOFF_(txoff), time_(0.0f), lastTime_(0.0f), gamestate(nullptr), activado(false)  {

}

void TimeTrap::init()  {

	gamestate = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(gamestate != nullptr);


	texON_->setBlendMode(SDL_BLENDMODE_BLEND);
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void TimeTrap::render() {
	SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

	Vector2D renderPos = Vector2D(tr_->getPos().getX() - cam.x, tr_->getPos().getY() + tr_->getZ() - cam.y);
	SDL_Rect dest = build_sdlrect(renderPos, tr_->getW(), tr_->getH());
	if (debug) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);

		SDL_RenderDrawRect(sdlutils().renderer(), &dest);
	}

	EntityAttribs* attribs = entity_->getComponent<EntityAttribs>();

	if (tr_->getFlip()) {
		texOFF_->render(dest, tr_->getRot(), SDL_FLIP_HORIZONTAL);
		texON_->render(dest, tr_->getRot(), SDL_FLIP_HORIZONTAL);
	}
	else {
		texOFF_->render(dest, tr_->getRot(), SDL_FLIP_HORIZONTAL);
		texON_->render(dest, tr_->getRot());
	}

	//std::cout << renderPos.getX() << " " << renderPos.getY() << "\n";
}

TimeTrap::~TimeTrap() {
	entity_->setActive(false);
	entity_->getMngr()->refreshObstacles();
}

void TimeTrap::update() {

	if (gamestate->getState() == GameStates::RUNNING) {

		time_ = sdlutils().currRealTime() - lastTime_;

		float currentState = sin(time_ / latency);

		if (currentState > 0) {
			entity_->getComponent<ContactDamage>()->setActive(true);

			texON_->setAlpha(255);

			if (!activado) {
				entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("trapKitchen");
			}
			activado = true;
		}
		else {
			activado = false;
			entity_->getComponent<ContactDamage>()->setActive(false);

			texON_->setAlpha(255.0f * (1.0f + currentState));

			//entity_->getComponent<Image>().
		}	
		//cout << time_ << "    y     " << lastTime_ << "   o    " << (time_ - lastTime_) << "           \n";
	}
	else lastTime_ = sdlutils().currRealTime() - time_;
	
}


