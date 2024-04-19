#ifndef MOUSE_H
#define MOUSE_H
#include "Object.h"

class Mouse: public Object
{
    public:
        SDL_Rect cursor, tip;
        Mouse();
        void Render(SDL_Renderer* renderer);
    private:
};

#endif // MOUSE_H
