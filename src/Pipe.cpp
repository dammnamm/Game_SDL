#include "Pipe.h"
#include <ctime>
#include <vector>


Pipe::Pipe()
{
    pipeWidth = 82;
    pipeHeight = 506;
    space = 200;
}

void Pipe::setPipe(int i)
{
	srand(time(NULL));
	setSrc(0, 0, 41, 253);
	xPos[i] = (i+3)*300;
	upPipe_H[i] = pipeRandHeight();
	downPipe_H[i] = upPipe_H[i] + space;
	setDest(xPos[i], upPipe_H[i] - pipeHeight, pipeWidth, pipeHeight);
}

int Pipe::pipeRandHeight()
{
	std::vector<int> height = {150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400};

    // Seed the random number generator
    std::srand(std::time(0));

    // Generate a random index
    int randomIndex = std::rand() % height.size();

    // Get the random element from the vector
    int randomHeight = height[randomIndex];
    return randomHeight;

}

void Pipe::upPipeUpdate(int i)
{
    if(xPos[i] + 82 <= 0 )
    {
        upPipe_H[i] = pipeRandHeight();
        xPos[i] = 812;
    }
    else
    {
        xPos[i] -= 1;
        setDest(xPos[i], upPipe_H[i] - pipeHeight, pipeWidth, pipeHeight);
    }
}

void Pipe::downPipeUpdate(int i)
{
    if(xPos[i] + 82 <= 0 )
    {
        downPipe_H[i] = upPipe_H[i] + space;
        xPos[i] = 812;
    }
    else
    {
        xPos[i] -= 1;
        setDest(xPos[i], downPipe_H[i], pipeWidth, pipeHeight);
    }
}

void Pipe::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}



