#include "subtitulos.h"
#include "ControlHandler.h"
#include "SoundManager.h"

Subtitulos::Subtitulos(std::string actualSub, int transitionNum)
{
	actualSub_ = actualSub;
	transitionNum_ = transitionNum;
	//Texturas
	barText_ = &sdlutils().images().at("dialogoBarra");
	dialogoText_ = &sdlutils().images().at(actualSub_ + std::to_string(dialogueNum));

	//Positions
	barRenderPos = Vector2D(0, sdlutils().height() - barText_->height());
	dialogueRenderPos = Vector2D((sdlutils().width() / 2) - (dialogoText_->width() / 2) - 100, sdlutils().height() - dialogoText_->height() - 25);

	//DestRects
	barDestI = build_sdlrect(barRenderPos, barText_->width(), barText_->height());
	dialogoDestI = build_sdlrect(dialogueRenderPos, dialogoText_->width(), dialogoText_->height());

	barDest = barDestI;
	dialogoDest = dialogoDestI;
}

void Subtitulos::render() {
	//Controlamos que solo se renderice cuando se tenga que mostrar
	if (renderDialogues) {
		barText_->render(barDest);
		dialogoText_->render(dialogoDest);
	}
}

void Subtitulos::update() {
	if (showDialogue) {
		renderDialogues = true;
		show();
	}
	else
		unshow();

	barDest.y = barDestI.y * position;
	dialogoDest.y = dialogoDestI.y * position;

}
//Muestra los dialogos
void Subtitulos::show() {
	if (position > 1.1f)
		position = position - 0.1f;
	else position = 1.0f;
}

void Subtitulos::unshow() {
	if (position < 3.0f) {
		entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("stopTutorial");
		position = position + 0.1f;
	}
	else {
		renderDialogues = false;
	}
}

void Subtitulos::changeDialogue() {
	if (dialogueNum < transitionNum_- 1) {
		dialogueNum++;
		dialogoText_ = &sdlutils().images().at(actualSub_ + std::to_string(dialogueNum));
	}
}

//Controla toda la movida buena suerte lo programe hace 30 mins y no se que hice
void Subtitulos::dialogoStateChange() {
	//Cambiamos el dialogo cuando no se esta mostrando la movida
	if (!firstDialogue)
		changeDialogue();
	//Cambiamos el estado de mostrarse a no mostrarse
	showDialogue = true;

	//Controla la primera vez, para que no te cambie de dialogo la primera vez que sale
	if (firstDialogue)
		firstDialogue = false;
}