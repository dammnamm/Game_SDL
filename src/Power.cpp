#include "Power.h"

Power::Power():power_width(55), power_height(55)
{
    setSrc(0, 0, 80, 80);
    power_dest = {0, 0 , power_width, power_height};
}

void Power::set_coordinate()
{
    isEated = false;
    power_dest.x = rand() % 101 + 800;
    power_dest.y = rand() % 201 + 200;
}
void Power::Update()
{
    power_dest.x -= 2;
    if(power_dest.x + power_width <= 0)
    {
        set_coordinate();
    }
}

SDL_Rect& Power::get_power_dest()
{
    return power_dest;
}

void Power::Render(SDL_Renderer* renderer)
{
    timer++;
    set_y_src(80 * (timer / 10));
    if (getSrc().y >= 720) {
        set_y_src(720);
        if (timer >= 100) {
            set_y_src(0);
            timer = 0;
        }
    }
    SDL_RenderCopy(renderer, getTexture(), &getSrc(), &power_dest);
}
