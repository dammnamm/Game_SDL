#include "Floor.h"

Floor::Floor() : floorWidth(672) , floorHeight(224)
{

    xPos1 = 0;
    xPos2 = 672;
    setSrc(0, 0, 336, 112);
}

void Floor::Update1()
{
    if(xPos1 + floorWidth <= 0 )
    {
        xPos1 = 0;
    }else
    {
        xPos1 -= 1;
    }
    setDest(xPos1, 650, floorWidth, floorHeight);
}

void Floor::Update2()
{
    if(xPos2 <= 0 )
    {
        xPos2 = 672;
    }else
    {
        xPos2 -= 1;
    }
    setDest(xPos2, 650, floorWidth, floorHeight);
}

void Floor::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}

