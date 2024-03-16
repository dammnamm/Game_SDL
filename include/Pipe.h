#ifndef PIPE_H
#define PIPE_H

#include "Object.h"
#include <ctime>
#include <vector>

class Pipe : public Object
{
    public:
        int pipeWidth;
        int pipeHeight;
        int space;
        int xPos;
        Pipe();
        void Render(SDL_Renderer* renderer);
        int pipeRandomHeight();
        void move();
    private:
};

#endif // PIPE_H
