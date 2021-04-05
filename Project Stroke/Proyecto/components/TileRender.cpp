#include "TileRender.h"
#include "../game/Game.h"

TileRender::TileRender(SDL_Rect source, SDL_Rect dest, Texture* tx)
{
	src = source;
	dst = dest;
	text = tx;

}

void TileRender::render() {
	Vector2D renderPos = Vector2D(dst.x - Game::camera_.x, dst.y - Game::camera_.y);
	SDL_Rect dstFijo = build_sdlrect(renderPos, dst.w, dst.h);

	text->render(src, dstFijo);
}