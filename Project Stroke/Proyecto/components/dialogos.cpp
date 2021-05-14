#include "dialogos.h"
#include "../sdlutils/InputHandler.h"
#include "ControlHandler.h"

dialogos::dialogos()
{
	//Texturas
	angelText_ = &sdlutils().images().at("dialogoAngel");
	barText_ = &sdlutils().images().at("dialogoBarra");
	dialogoText_ = &sdlutils().images().at("dialogo" + to_string(dialogueNum));
	explicacionText_ = &sdlutils().images().at("explicacion" + to_string(dialogueNum));

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
}
void dialogos::init() {
	keymap.insert({ UP, SDL_SCANCODE_W });
	keymap.insert({ DOWN, SDL_SCANCODE_S });
	keymap.insert({ LEFT, SDL_SCANCODE_A });
	keymap.insert({ RIGHT, SDL_SCANCODE_D });
	keymap.insert({ SPACE, SDL_SCANCODE_SPACE });
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
	if (showDialogue) {
		renderDialogues = true;
		show();
	}
	else
		unshow();

	angelDest.y = angelDestI.y * position;
	barDest.y = barDestI.y * position;
	dialogoDest.y = dialogoDestI.y * position;
	explicacionDest.y = explicacionDestI.y * position;

	//Oculta el dialogo
	if (ih().isKeyDown(keymap.at(SPACE)))
	{
		//Cambiamos el estado de mostrarse a no mostrarse
		showDialogue = false;
	}
}
//Muestra los dialogos
void dialogos::show() {
	if (position > 1.0f)
		position = position - 0.1f;
}

void dialogos::unshow() {
	if (position < 3.0f)
		position = position + 0.1f;
	else {
		renderDialogues = false;
	}
}

void dialogos::changeDialogue() {
	dialogueNum++;
	dialogoText_ = &sdlutils().images().at("dialogo" + to_string(dialogueNum));
	explicacionText_ = &sdlutils().images().at("explicacion" + to_string(dialogueNum));
}

//Controla toda la movida buena suerte lo programe hace 30 mins y no se que hice
void dialogos::dialogoStateChange() {
	//Cambiamos el dialogo cuando no se esta mostrando la movida
	if (!showDialogue && !firstDialogue)
		changeDialogue();
	//Cambiamos el estado de mostrarse a no mostrarse
	showDialogue = !showDialogue;

	//Controla la primera vez, para que no te cambie de dialogo la primera vez que sale
	if (firstDialogue)
		firstDialogue = false;
}