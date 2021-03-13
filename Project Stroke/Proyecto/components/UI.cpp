#include "UI.h"

UI::UI(Texture* face) :
	face_(face), //
	hearth_(&sdlutils().images().at("heart1")),
	bar_(&sdlutils().images().at("bar"))
{}

void UI::render() {
	Vector2D renderPos = Vector2D(50, 50);	// Vector2D(sdlutils().width() / 4, 50);
	SDL_Rect dest = build_sdlrect(renderPos, bar_->width(), bar_->height());
	SDL_Rect dest2 = build_sdlrect(renderPos, face_->width(), face_->height());
	SDL_Rect dest3 = build_sdlrect(renderPos, hearth_->width(), hearth_->height());

	bar_->render(dest);
	face_->render(dest2);
	hearth_->render(dest3);
}

void UI::changeText() {
	//Si el hamster muere cambiar textura a muerto
	if (entity_->getComponent<Life>()->getLife() < 0) {
		hearth_ = &sdlutils().images().at("sardinillaHead2");
	}
	else {
		hearth_ = &sdlutils().images().at("sardinillaHead1");
	}
}