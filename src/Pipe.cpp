#include "Pipe.h"
#include <ctime>
#include <vector>

Pipe::Pipe()
{
    pipeWidth = 41;
    pipeHeight = 253;
    space = 150;
    xPos = 432;
    setSrc(0,0,pipeWidth, pipeHeight);
    setDest(xPos, 300, 2*pipeWidth, 2*pipeHeight);
}

void Pipe::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}

int Pipe::pipeRandomHeight()
{
    std::vector<int> height = {100, 150, 200, 250, 300, 350, 400};
    std::srand(std::time(0));
    int randomIndex = std::rand() % height.size();
    int randomHeight = height[randomIndex];
    return randomHeight;
}

void Pipe::move()
{
    xPos -= 1;
    setDest(xPos, 732 - pipeRandomHeight(), 2*pipeWidth, 2*pipeHeight);
    if(xPos + 2*pipeWidth < 0) {
        xPos = 432;
    }
}


