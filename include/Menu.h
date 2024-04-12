#ifndef MENU_H
#define MENU_H
#include "Button.h"

class Menu
{
    public:
        SDL_Texture* background;
        Menu();
        ~Menu();
        enum buttonName {PLAY, QUIT};
        Button* button[2];
        void
};

#endif // MENU_H
