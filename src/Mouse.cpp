#include "Mouse.h"

Mouse::Mouse()
{
	cursor = { 0, 0, 30, 30 };
	tip = { 0, 0, 1, 1};
}


void Mouse::Render(SDL_Renderer* renderer)
{
    tip.x = cursor.x;
    tip.y = cursor.y;
    SDL_RenderCopy(renderer, getTexture(), NULL, &cursor);
}
