#ifndef FLOOR_H
#define FLOOR_H

#include "Object.h"

class Floor:public Object
{
    public:
        Floor();
        void Update1();
        void Update2();
        void Render(SDL_Renderer* renderer);
    private:
        const int floorWidth;
        const int floorHeight;
        int xPos1;
        int xPos2;

};

#endif // FLOOR_H
