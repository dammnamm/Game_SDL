#ifndef BUTTON_H
#define BUTTON_H
#include "Object.h"
#include "Mouse.h"
class Button:public Object
{
    public:
        Button();
        Button(int x, int y);
        void setCordinate(int _x, int _y);
        void CheckSelected(const Mouse* mouse);
        void Render(SDL_Renderer* renderer);
        bool isSellected;
};

#endif // BUTTON_H
