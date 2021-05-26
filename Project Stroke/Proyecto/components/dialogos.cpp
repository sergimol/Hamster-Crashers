#include "dialogos.h"
#include "../sdlutils/InputHandler.h"
#include "ControlHandler.h"
#include "SoundManager.h"

//ESTA CLASE ES LA DEL TUTORIAL QUE SALE ANGEL HABLANDO


dialogos::dialogos()
{
	//Texturas
	angelText_ = &sdlutils().images().at("dialogoAngel");
	barText_ = &sdlutils().images().at("dialogoBarra");
	dialogoText_ = &sdlutils().images().at("dialogo" + to_string(dialogueNum_));
	explicacionText_ = &sdlutils().images().at("explicacion" + to_string(dialogueNum_));

	//Positions
	angelRenderPos = Vector2D(0, sdlutils().height() - angelText_->height());
	barRenderPos = Vector2D(0, sdlutils().height() - barText_->height());
	dialogueRenderPos = Vector2D((sdlutils().width() / 2) - (dialogoText_->width() / 2) - 100, sdlutils().height() - dialogoText_->height() - 25);
	explicacionRenderPos = Vector2D(sdlutils().width() - explicacionText_->width() - 25, sdlutils().height() - explicacionText_->height());

	//DestRects
	angelDestI = build_sdlrect(angelRenderPos, angelText_->width(), angelText_->height());
	barDestI = build_sdlrect(barRenderPos, barText_->width(), barText_->height());
	dialogoDestI = build_sdlrect(dialogueRenderPos, dialogoText_->width(), dialogoText_->height());
	explicacionDestI = build_sdlrect(explicacionRenderPos, explicacionText_->width(), explicacionText_->height());

	angelDest = angelDestI;
	barDest = barDestI;
	dialogoDest = dialogoDestI;
	explicacionDest = explicacionDestI;

	altTime_ = sdlutils().currRealTime();
	altCD_ = 1750;
}

void dialogos::render() {
	//Controlamos que solo se renderice cuando se tenga que mostrar
	if (renderDialogues) {
		barText_->render(barDest);
		dialogoText_->render(dialogoDest);
		explicacionText_->render(explicacionDest);
		angelText_->render(angelDest);
	}
}

void dialogos::update() {
	if (showDialogue_) {
		renderDialogues = true;
		if (sdlutils().currRealTime() > altTime_ + altCD_) {
			if (isAlt_) {
				explicacionText_ = &sdlutils().images().at("explicacion" + to_string(dialogueNum_));
			}
			else {
				explicacionText_ = &sdlutils().images().at("explicacion" + to_string(dialogueNum_) + "alt");
			}
			isAlt_ = !isAlt_;
			altTime_ = sdlutils().currRealTime();
		}

		show();
	}
	else
		unshow();

	angelDest.y = angelDestI.y * position;
	barDest.y = barDestI.y * position;
	dialogoDest.y = dialogoDestI.y * position;
	explicacionDest.y = explicacionDestI.y * position;

	//Oculta el dialogo cuando termina el audio
	if (showDialogue_ && entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->emptyChannel())
	{
		//Cambiamos el estado de mostrarse a no mostrarse
		showDialogue_ = false;
	}
	if (ih().isKeyDown(SDL_SCANCODE_RETURN) || ih().isAnyBButtonDown()) {
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->StopTutorial();
		showDialogue_ = false;
	}
}
//Muestra los dialogos
void dialogos::show() {
	if (position > 1.1f)
		position = position - 0.1f;
	else
		position = 1.0f;
}

void dialogos::unshow() {
	if (position < 3.0f) {
		position = position + 0.1f;
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("stopTutorial");

	}
	else {
		renderDialogues = false;
	}
}

void dialogos::changeDialogue() {
	dialogueNum_++;
	//activamos el infarto, comienza la aventura
	if (dialogueNum_ == 2) {
		entity_->getMngr()->getStrokeActive() = true;
	}

	dialogoText_ = &sdlutils().images().at("dialogo" + to_string(dialogueNum_));
	explicacionText_ = &sdlutils().images().at("explicacion" + to_string(dialogueNum_));
}

//Controla toda la movida buena suerte lo programe hace 30 mins y no se que hice
void dialogos::dialogoStateChange() {
	entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("tutorial");
	//Cambiamos el dialogo cuando no se esta mostrando la movida
	if (!firstDialogue_)
		changeDialogue();

	altTime_ = sdlutils().currRealTime();

	//Cambiamos el estado de mostrarse a no mostrarse
	showDialogue_ = true;

	//Controla la primera vez, para que no te cambie de dialogo la primera vez que sale
	if (firstDialogue_)
		firstDialogue_ = false;
}

//"dialogo3" o "dialogo3singleplayer" dependiendo del num de jugadores
void dialogos::showStrokeTutorial(std::string text) {
	dialogueNum_++;
	//el sonido tendrá que ser diferente si es single o no
	if (text == "dialogo3")
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("tutorial");
	else
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("tutorialsingle");

	dialogoText_ = &sdlutils().images().at(text);
	explicacionText_ = &sdlutils().images().at("explicacion3");
	showDialogue_ = true;
	sdlutils().setTutorialDone();
}