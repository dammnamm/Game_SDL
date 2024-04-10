#ifndef BUTTON_H
#define BUTTON_H
#include "Object.h"
#include "Mouse.h"
class Button:public Object
{
    public:
        Button();
        Button(int x, int y);
        SDL_Rect src, dest;
        void CheckSelected(Mouse* mouse);
        void Render(SDL_Renderer* renderer);
        bool isSellected;
    private:
};

#endif // BUTTON_H
