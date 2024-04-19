#include "Pipe.h"
#include <ctime>
#include <vector>

Pipe::Pipe() : pipeWidth(84), pipeHeight(501), space(185) {}

void Pipe::setPipe(int i)
{
    std::srand(time(NULL));
    setSrc(0, 0, pipeWidth, pipeHeight);
    pipePosition[i] = (i+3)*300;
    upPipeHeight[i] = generateRandomHeight();
    downPipeHeight[i] = upPipeHeight[i] + space;
    setDest(pipePosition[i], upPipeHeight[i] - pipeHeight, pipeWidth, pipeHeight);
}

int Pipe::generateRandomHeight()
{
	std::vector<int> height = {150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350};
	std::srand(std::time(0));
	int random_index = std::rand() % height.size();
    return height[random_index];
}

void Pipe::updateUpPipe(int i)
{
    if(pipePosition[i] + pipeWidth <= 0 )
    {
        upPipeHeight[i] = generateRandomHeight();
        pipePosition[i] = 812;
    }
    else
    {
        pipePosition[i] -= 1;
        setDest(pipePosition[i], upPipeHeight[i] - pipeHeight, pipeWidth, pipeHeight);
    }
}

void Pipe::updateDownPipe(int i)
{
    downPipeHeight[i] = upPipeHeight[i] + space;
    setDest(pipePosition[i], downPipeHeight[i], pipeWidth, pipeHeight);
}

void Pipe::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}
