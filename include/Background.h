#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Object.h"

class Background: public Object
{
    public:
        Background();
        void Render(SDL_Renderer* renderer);

    private:
        int bgWidth;
        int bgHeight;
};

#endif // BACKGROUND_H
