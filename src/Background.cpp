#include "Background.h"

Background::Background()
{
    bgWidth = 432;
    bgHeight = 768;
    setSrc(0, 0, 216, 384);
    setDest(0, 0, 432, 768);
}

void Background::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}

