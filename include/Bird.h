#ifndef BIRD_H
#define BIRD_H

#include "Object.h"

class Bird:public Object
{
private:
    SDL_Texture* Tex1;
    SDL_Texture* Tex2;

    int animationTimer;
    SDL_Point flipPoint;
    double angle;
    SDL_Point coordinate;

    double speed;
    double gravity;
    int Ypos;
    bool inJump;
    double jumpHeight;
    double jumpTimer;
    double lastJump;
public:
    Bird();
    void Gravity(bool isPlaying);
    double GetTimeJump(double jumpTimer);
    bool JumpState();
    void Jump();
    SDL_Point* getPoint();
    void setPoint(int _x, int _y);
    void CreateTexture1(const char* filePath, SDL_Renderer* renderer);
    void CreateTexture2(const char* filePath, SDL_Renderer* renderer);
    void Reset();
    void Render(SDL_Renderer* renderer);

};

#endif // BIRD_H
