#ifndef BUTTON_H
#define BUTTON_H
#include "Object.h"
#include "Mouse.h"
class Button:public Object
{
    public:
        bool selected;
        Button();
        void setCoordinates(int x, int y);
        void CheckSelected(Mouse* mouse);
        void Render(SDL_Renderer* ren);
    private:
};

#endif // BUTTON_H
