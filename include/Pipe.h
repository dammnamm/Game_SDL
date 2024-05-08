#ifndef PIPE_H
#define PIPE_H

#include "Object.h"
#include <ctime>
#include <vector>


class Pipe : public Object
{
public:
    Pipe();
    void Horizontal_Move();
    void Vertical_Move();
    void Render(SDL_Renderer* renderer);
    void SetPosition(int index);
    int GetWidth();
    int GetHeight();
    int GetPipeHeight();
    void Reset(int index);
    SDL_Rect& getUpperDest();
    SDL_Rect& getLowerDest();
    int UpdateVerticalAcceleration(int current_y, int min_y, int max_y);
    void Angle_Update();
    bool isCollide = false;
private:
    int accelerator;
    SDL_Rect UpperPipeRect;
    SDL_Rect LowerPipeRect;
    int angle = 0;
    int Width;
    int Height;
    int pipeHeight;
    int Space;
    int h_speed;
    int v_speed;
    void GenerateRandomHeight();
};

#endif // PIPE_H
