#ifndef PIPE_H
#define PIPE_H

#include "Object.h"
#include <ctime>
#include <vector>


class Pipe : public Object
{
public:
    Pipe();
    void Update();
    void Render(SDL_Renderer* renderer);
    void SetPosition(int index);
    int GetWidth() const;
    int GetHeight() const;
    void Reset(int index);
    SDL_Rect& getUpperDest();
    SDL_Rect& getLowerDest();
private:
    SDL_Rect UpperPipeRect;
    SDL_Rect LowerPipeRect;
    int Width;
    int Height;
    int pipeHeight;
    int Space;
    int Speed;
    void GenerateRandomHeight();
};

#endif // PIPE_H
