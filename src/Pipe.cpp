#include "Pipe.h"
#include <ctime>
#include <vector>

Pipe::Pipe() : Width(84), Height(501), Space(250), Speed(2) {
    setSrc(0, 0 , Width, Height );
    pipeHeight = 0;
    UpperPipeRect = {0, 0 , Width, Height};
    LowerPipeRect = {0, 0 , Width, Height};
}

int Pipe::GetWidth() {
    return Width;
}

int Pipe::GetHeight()
{
return Height;
}

int Pipe::GetPipeHeight()
{
    return pipeHeight;
}

void Pipe::Update() {
    // Update horizontal position
    UpperPipeRect.x -= Speed;
    LowerPipeRect.x -= Speed;


    if (UpperPipeRect.x + Width < 0) {
        UpperPipeRect.x = 812;
        LowerPipeRect.x = 812;
        GenerateRandomHeight();
    }

}


void Pipe::GenerateRandomHeight()
{
	std::vector<int> height = {150,160,170,180,190,200,210,220,230,240,250,};
	std::srand(std::time(0));
	int random_index = std::rand() % height.size();
    pipeHeight = height[random_index];
    UpperPipeRect.y = pipeHeight - Height;
    LowerPipeRect.y =  pipeHeight + Space;
}

void Pipe::SetPosition( int index) {
    UpperPipeRect.x = (index+3)*300;
    LowerPipeRect.x  = (index+3)*300;
    if (pipeHeight == 0) {
        GenerateRandomHeight();
    }
}

void Pipe::Reset(int index)
{
    setSrc(0, 0 , Width, Height );
    pipeHeight = 0;
    UpperPipeRect = {0, 0 , Width, Height};
    LowerPipeRect = {0, 0 , Width, Height};
    SetPosition(index);
    if (pipeHeight == 0) {
        GenerateRandomHeight();
    }
}

SDL_Rect& Pipe::getLowerDest()
{
    return LowerPipeRect;
}

SDL_Rect& Pipe::getUpperDest()
{
    return UpperPipeRect;
}

void Pipe::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, getTexture(), &getSrc(), &getLowerDest(), 0, NULL, SDL_FLIP_NONE );
    SDL_RenderCopyEx(renderer, getTexture(), &getSrc(), &getUpperDest(), 0, NULL, SDL_FLIP_VERTICAL );
}
