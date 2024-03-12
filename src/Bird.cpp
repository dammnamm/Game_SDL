#include "Bird.h"

Bird::Bird()
{
    animationTimer = 0;
    Ypos = 100;
    speed = 0;
    gravity = 0.3;
    inJump = false;
    jumpHeight = -7.5;
    jumpTimer;
    lastJump = 0;
    setSrc(0,0, 34, 24);
    setDest(100,Ypos, 68, 48);
}

void Bird::Gravity()
{
    if(JumpState())
    {
        speed = jumpHeight; //reset speed;
        inJump = false;
    }
    if(true) {
        Ypos += speed/4.55;
    }
    speed += gravity/2.5;
    setDest(100, Ypos, 68, 48);
}

double Bird::GetTimeJump(double jumpTimer)
{
    return SDL_GetTicks();
}

void Bird::Jump()
{
    jumpTimer = GetTimeJump(jumpTimer);
    if(jumpTimer - lastJump > 165)
    {
        inJump = true;
        lastJump = jumpTimer;
    }
    else
    {
        inJump = false;
    }
}

bool Bird::JumpState()
{
    return inJump;
}

void Bird::CreateTexture1(const char* filePath, SDL_Renderer* renderer)
{
    Tex1 = TextureManager::Texture(filePath, renderer);
}

void Bird::CreateTexture2 (const char* filePath, SDL_Renderer* renderer)
{
    Tex2 = TextureManager::Texture(filePath, renderer);
}

void Bird::Render(SDL_Renderer* renderer)
{
    animationTimer++;
    if(animationTimer <= 25) {
        SDL_RenderCopyEx(renderer, getTexture(), &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
    }else if(animationTimer <= 50) {
        SDL_RenderCopyEx(renderer, Tex1, &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
    }else if(animationTimer <= 75) {
        SDL_RenderCopyEx(renderer, Tex2, &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
    }else {
        animationTimer = 0;
    }
}

