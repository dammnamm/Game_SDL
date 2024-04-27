#ifndef POWER_H
#define POWER_H

#include "Object.h"
#include "Pipe.h"
class Power:public Object
{
private:
    int timer = 0;
    const int power_width;
    const int power_height;
    int xPos;
public:
    SDL_Rect power_dest;
    bool isEated = false;
    Power();
    SDL_Rect &get_power_dest();
    void set_coordinate();
    void Update();
    void Render(SDL_Renderer* renderer);
};

#endif // POWER_H
