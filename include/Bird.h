#ifndef BIRD_H
#define BIRD_H

#include "Object.h"

class Bird:public Object
{
private:
    int angle = 0;
    int birdWidth = 96;
    int birdHeight = 78;
    double Ypos;
    double jumpHeight;
    SDL_Texture* bird1;
    double gravity;
    double ver_speed;
    int animationTimer = 0;

public:
    Bird();
    void Gravity(bool isPlaying);
    void Jump();
    void CreateTexture1(const char* filePath, SDL_Renderer* renderer);
    void CreateTexture2(const char* filePath, SDL_Renderer* renderer);
    void Reset();
    void Render(SDL_Renderer* renderer);

};

#endif // BIRD_H
