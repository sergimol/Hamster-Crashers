#include "Animator.h"
#include "../ecs/Camera.h"
#include "../game/Game.h"

#include "Transform.h"
#include "EntityAttribs.h"
#include "GameStates.h"

void Animator::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	state_ = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(state_ != nullptr);
}

void Animator::render() {
	if (state_->getState() != GameStates::MAINMENU && state_->getState() != GameStates::CONTROLS && state_->getState() != GameStates::OPTIONS) {
		SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

		//recurso
		Vector2D auxTextFrame = Vector2D();
		auxTextFrame.setX(widthFrame * textureFrame.getX());
		auxTextFrame.setY(heightFrame * textureFrame.getY());

		//Multiplicamos por el 'Scale' para que cada uno tenga su tamanyo
		SDL_Rect src = build_sdlrect(auxTextFrame, widthFrame, heightFrame);

		//destino
		Vector2D renderPos = Vector2D(tr_->getPos().getX() - cam.x, tr_->getPos().getY() - tr_->getZ() - cam.y);
		SDL_Rect dest = build_sdlrect(renderPos, tr_->getW(), tr_->getH());


		EntityAttribs* attribs = entity_->getComponent<EntityAttribs>();
		//Color verdoso cuando esta envenenado
		if (attribs != nullptr && attribs->getPoisoned())
			SDL_SetTextureColorMod(tex_->getSDLText(), 179, 0, 255);
		else
			SDL_SetTextureColorMod(tex_->getSDLText(), 255, 255, 255);

		if (debug) {
			SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);

			SDL_RenderDrawRect(sdlutils().renderer(), &dest);
		}

		//Renderizado
		if (tr_->getFlip())
			tex_->render(src, dest, tr_->getRot(), nullptr, SDL_FLIP_HORIZONTAL);
		else
			tex_->render(src, dest, 0);


		//tex_->render(dest, tr_->getRot());
	}
}

//para actualizar la textura
void Animator::update() {
	if (state_->getState() != GameStates::PAUSE && state_->getState() != GameStates::MAINMENU) {
		if (sdlutils().currRealTime() >= lastTime + frameUpdate)
		{

			lastTime = sdlutils().currRealTime();

			//SI NO SE HA ACABADO LA ANIMACION
			if (animCont < animDuration - 1)
			{
				//Si no hemos llegado al final de una fila seguimos avanzando
				if (textureFrame.getX() < cols - 1)
				{
					textureFrame.setX(textureFrame.getX() + 1);
				}
				//Si llegamos al final de la fila cambiamos
				else
				{
					textureFrame.setX(0);
					textureFrame.setY(textureFrame.getY() + 1);
				}
				animCont++;
			}
			//SI SE HA ACABADO Y HAY QUE LOOPEAR
			else if (looped)
			{
				animCont = 0;
				textureFrame.setX(startFrame.getX());
				textureFrame.setY(startFrame.getY());
			}
			//SI HAY QUE ENCADENAR OTRA ANIMACION
			else if (idChain != "")
				play(sdlutils().anims().at(idChain));

		}
	}
}

void Animator::onResume() {
	lastTime += sdlutils().currRealTime() - lastTime;
}

//Metodo que cambia de animacion sobre la spritesheet actual
void Animator::play(Animation actualAnim)
{
	frameUpdate = actualAnim.frameUpdate();
	startFrame = actualAnim.startFrame();
	animDuration = actualAnim.duration();
	textureFrame = startFrame;
	cols = actualAnim.cols();
	rows = actualAnim.rows();
	animCont = 0;
	looped = actualAnim.loop();
	idChain = actualAnim.chain();
	attackFrame = actualAnim.attackFrame();
}



//Devuelve true o false en funcion si la animacion ha llegado al ultimo frame o no
bool Animator::OnAnimationFrameEnd()
{
	return animCont == animDuration - 1;
}

//Devuelve true o false en funcion de si la animacion ha llegado al frame del parametro
bool Animator::OnAnimationFrame(int targetFrame)
{
	return animCont == targetFrame;
}

//Devuelve true o false en funcion de si la animacion ha llegado al frame en el que
//se activa el collider
bool Animator::OnFinalAttackFrame()
{
	return animCont == attackFrame - 1;
}

void Animator::setTexture(Texture* t) {
	tex_ = t;
}