#include "Button.h"

Button::Button()
{
    selected = false;
}

void Button::setCoordinates(int x, int y)
{
    setDest(x, y, NULL, NULL);
}

void Button::CheckSelected(Mouse* mouse)
{
    SDL_Rect& dest = getDest();
    SDL_Rect& src = getSrc();
    if (SDL_HasIntersection(&(mouse->tip), &dest))
    {
        selected = true;
        src.x = 400;
    }
    else
    {
        selected = false;
        src.x = 0;
    }
}

void Button::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}
