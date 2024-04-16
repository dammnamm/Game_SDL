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
	std::vector<int> height = {150, 160, 175, 200, 225, 250, 275, 280, 300, 325, 330, 340, 350};
	std::srand(std::time(0));
	int random_index = std::rand() % height.size(); // generate a random index
    return height[random_index]; // return the random element
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



