#include "Pipe.h"
#include <ctime>
#include <vector>

Pipe::Pipe() : Width(84), Height(501), Space(225), h_speed(2), accelerator(1), v_speed(1) {
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

void Pipe::Horizontal_Move() {
    // Update horizontal position
    UpperPipeRect.x -= h_speed;
    LowerPipeRect.x -= h_speed;

    if(angle == 0) {
        if (UpperPipeRect.x + Width < 0) {
            UpperPipeRect.x = 812;
            LowerPipeRect.x = 812;
            GenerateRandomHeight();
        }
    }else
    {
        if (UpperPipeRect.x + 50 < 0) {
            UpperPipeRect.x = 812;
            LowerPipeRect.x = 812;
            GenerateRandomHeight();
        }
    }
}

void Pipe::Vertical_Move()
{
    accelerator = UpdateVerticalAcceleration(UpperPipeRect.y, -400, -200);
    UpperPipeRect.y += v_speed* accelerator;
    LowerPipeRect.y += v_speed* accelerator;
}

int Pipe::UpdateVerticalAcceleration(int current_y, int min_y, int max_y) {
    if (current_y <= min_y) {
        return 1;
    } else if (current_y >= max_y) {
        return -1;
    } else {
        return accelerator;
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
    isCollide = false;
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
    pipeHeight = 0;
    angle = 0;
    Space = 225;
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
    SDL_RenderCopyEx(renderer, getTexture(), &getSrc(), &getLowerDest(), angle, NULL, SDL_FLIP_NONE );
    if(angle == 0) {
        SDL_RenderCopyEx(renderer, getTexture(), &getSrc(), &getUpperDest(), angle, NULL, SDL_FLIP_VERTICAL );
    }else
    {
        SDL_RenderCopyEx(renderer, getTexture(), &getSrc(), &getUpperDest(), - angle, NULL, SDL_FLIP_VERTICAL );
    }
}
