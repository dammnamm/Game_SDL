#include "Pipe.h"
#include <ctime>
#include <vector>


Pipe::Pipe()
{
    pipeWidth = 82;
    pipeHeight = 506;
    space = 185;
}

void Pipe::setPipe(int i)
{
    std::srand(time(NULL));
    setSrc(0, 0, 41, 253);
    xPos[i] = (i+3)*300;
    upPipe_H[i] = pipeRandHeight();
    downPipe_H[i] = upPipe_H[i] + space;
}

int Pipe::pipeRandHeight()
{
	std::vector<int> height = {200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400};
	std::srand(std::time(0));
	int random_index = std::rand() % height.size(); // generate a random index
    return height[random_index]; // return the random element
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
    downPipe_H[i] = upPipe_H[i] + space;
    setDest(xPos[i], downPipe_H[i], pipeWidth, pipeHeight);
}

void Pipe::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}



