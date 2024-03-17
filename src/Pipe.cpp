#include "Pipe.h"
#include <ctime>
#include <vector>


Pipe::Pipe()
{
    pipeWidth = 82;
    pipeHeight = 506;
    space = 150;
}

void Pipe::setPipe(int i)
{
	srand(time(NULL));
	xPos[i] = i*200 + 432;
	upPipe_H[i] = pipeRandHeight();
	setDest(xPos[i], upPipe_H[i] - pipeHeight, pipeWidth, pipeHeight);
}

int Pipe::pipeRandHeight()
{
	return rand() * rand() % (330 - 100 + 1) + 100;
}

void Pipe::upPipeUpdate(int i)
{
    if(xPos[i] + 82 <= 0 )
    {
        upPipe_H[i] = pipeRandHeight();
        xPos[i] = 660;
    }
    else
    {
        xPos[i] -= 1;
        setDest(xPos[i], upPipe_H[i] - pipeHeight, 82, 506);
    }
}

void Pipe::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}



