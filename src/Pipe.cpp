#include "Pipe.h"
#include <ctime>
#include <vector>


Pipe::Pipe()
{
    pipeWidth = 84;
    pipeHeight = 501;
    space = 185;
}

void Pipe::setPipe(int i)
{
    std::srand(time(NULL));
    setSrc(0, 0, pipeWidth, pipeHeight);
    pipePos[i] = (i+3)*300;
    upPipe_H[i] = pipeRandHeight();
    downPipe_H[i] = upPipe_H[i] + space;
    setDest(pipePos[i], upPipe_H[i] - pipeHeight, pipeWidth, pipeHeight);
}

int Pipe::pipeRandHeight()
{
	std::vector<int> height = {150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350};
	std::srand(std::time(0));
	int random_index = std::rand() % height.size();
    return height[random_index];
}

void Pipe::upPipeUpdate(int i)
{
    if(pipePos[i] + pipeWidth <= 0 )
    {
        upPipe_H[i] = pipeRandHeight();
        pipePos[i] = 812;
    }
    else
    {
        pipePos[i] -= 1;
        setDest(pipePos[i], upPipe_H[i] - pipeHeight, pipeWidth, pipeHeight);
    }
}

void Pipe::downPipeUpdate(int i)
{
    downPipe_H[i] = upPipe_H[i] + space;
    setDest(pipePos[i], downPipe_H[i], pipeWidth, pipeHeight);
}


void Pipe::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}



