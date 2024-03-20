#ifndef PIPE_H
#define PIPE_H

#include "Object.h"
#include <ctime>
#include <vector>

static int upPipe_H[3]; //Height of up pipe;
static int xPos[3];

class Pipe : public Object
{
    private:
    public:
        Pipe();
        void setPipe(int i);
        int pipeWidth;
        int pipeHeight;
        int space = 100;
        int downPipe_H[3];
        int pipeRandHeight();
        void upPipeUpdate(int i);
        void downPipeUpdate(int i);
        void Render(SDL_Renderer* renderer);

};

#endif // PIPE_H
