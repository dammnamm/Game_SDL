#ifndef PIPE_H
#define PIPE_H

#include "Object.h"
#include <ctime>
#include <vector>

static int upPipeHeight[3];
static int pipePosition[3];

class Pipe : public Object
{
    public:
        Pipe();
        void setPipe(int i);
        int pipeWidth;
        int pipeHeight;
        int space = 300;
        int downPipeHeight[3];
        int generateRandomHeight();
        void updateUpPipe(int i);
        void updateDownPipe(int i);
        void reset();
        void render(SDL_Renderer* renderer);

};

#endif // PIPE_H
