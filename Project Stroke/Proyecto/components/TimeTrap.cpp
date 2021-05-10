#include "TimeTrap.h"
#include "Animator.h"
#include "SoundManager.h"
#include "../ecs/Manager.h"
#include "Dying.h"

TimeTrap::TimeTrap(Texture* tx) : latency(1000), tex_(tx)  {

}

void TimeTrap::init()  {

	tex_->setBlendMode(SDL_BLENDMODE_BLEND);
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

	//Color verdoso cuando está envenenado
	if (attribs != nullptr && attribs->getPoisoned())
		SDL_SetTextureColorMod(tex_->getSDLText(), 148, 236, 130);
	else
		SDL_SetTextureColorMod(tex_->getSDLText(), 255, 255, 255);

	if (tr_->getFlip())
		tex_->render(dest, tr_->getRot(), SDL_FLIP_HORIZONTAL);
	else
		tex_->render(dest, tr_->getRot());

	//std::cout << renderPos.getX() << " " << renderPos.getY() << "\n";
}

TimeTrap::~TimeTrap() {
	entity_->getMngr()->refreshObstacles();
}

void TimeTrap::update() {
	float currentState = sin((sdlutils().currRealTime() / latency));

	if (currentState > 0) {
		entity_->getComponent<ContactDamage>()->setActive(true);
		std::cout << "On\n";

		tex_->setAlpha(255);
	}
	else {
		entity_->getComponent<ContactDamage>()->setActive(false);
		cout << "Off\n";

		tex_->setAlpha(255.0f * (1.0f + currentState));

		//entity_->getComponent<Image>().
	}	
	
}


