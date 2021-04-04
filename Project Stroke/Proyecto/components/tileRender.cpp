#include "tileRender.h"
#include "../game/Game.h"

tileRender::tileRender(SDL_Rect source, SDL_Rect dest, Texture* tx)
{
	src = source;
	dst = dest;
	text = tx;

}

void tileRender::render() {
	Vector2D renderPos = Vector2D(dst.x - Game::camera_.x, dst.y - Game::camera_.y);
	SDL_Rect dstFijo = build_sdlrect(renderPos, dst.w, dst.h);

	text->render(src, dstFijo);
}