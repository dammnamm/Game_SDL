#include "Button.h"

Button::Button()
{
    isSellected = false;
}

Button::Button(int x, int y)
{
    src = {x, y, 240, 144};
    dest = {x, y, 240, 144};
    isSellected = false;
}


void Button::CheckSelected(Mouse* mouse)
{
    if (SDL_HasIntersection(&(mouse->tip), &dest))
    {
        isSellected = true;
        src.x = 248;
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
