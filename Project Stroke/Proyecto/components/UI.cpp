#include "UI.h"

UI::UI(std::string n) :
	face_(&sdlutils().images().at(n + "Head1")), //
	hearth_(&sdlutils().images().at("heart1")),
	bar_(&sdlutils().images().at("bar")),
	scale(2),
	name(n)
{}

void UI::render() {
	Vector2D renderPos = Vector2D(50, 50);	// Vector2D(sdlutils().width() / 4, 50);
	Vector2D renderPosHeart = renderPos - Vector2D(10, -10);
	Vector2D renderPosBar = renderPos + Vector2D(25, 5);
	SDL_Rect dest = build_sdlrect(renderPosBar, bar_->width(), bar_->height());
	SDL_Rect dest2 = build_sdlrect(renderPos, face_->width() * 1.5, face_->height() * 1.5);
	SDL_Rect dest3 = build_sdlrect(renderPosHeart, hearth_->width(), hearth_->height());

	bar_->render(dest);
	face_->render(dest2);
	hearth_->render(dest3);
}

//Si el hamster muere cambiar textura a muerto
void UI::dep() {
	hearth_ = &sdlutils().images().at("heart3");
	face_ = &sdlutils().images().at(name + "Head2");
}

void UI::bar() {

}