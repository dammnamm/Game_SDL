#include "Button.h"

Button::Button()
{
    isSellected = false;
}

Button::Button(int x, int y)
{
    src = {x, y, 384, 168};
    dest = {x, y, 185, 81};
    isSellected = false;
}

void Button::setCordinate(int _x, int _y)
{
    dest.x = _x;
    dest.y = _y;
}


void Button::CheckSelected(const Mouse* mouse)
{
    if (SDL_HasIntersection(&(mouse->tip), &dest))
    {
        isSellected = true;
        src.x = 400;
    }
    else
    {
        isSellected = false;
        src.x = 0;
    }
}

void Button::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, getTexture(), &src, &dest);
}
