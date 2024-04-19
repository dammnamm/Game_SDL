#include "Bird.h"

Bird::Bird()
{
    animationTimer = 0;
    birdWidth = 96;
    birdHeight = 78;
    Ypos = 384;
    speed = 0;
    gravity = 0.3;
    inJump = false;
    jumpHeight = -7.5;
    jumpTimer;
    lastJump = 0;
    setSrc(0,0, birdWidth, birdHeight);
    setDest(50,Ypos, birdWidth, birdHeight);
}

void Bird::Gravity(bool isPlaying)
{
    if(JumpState())
    {
        speed = jumpHeight;
        inJump = false;
    }
    Ypos += speed/4;
    speed += gravity/2;
    setDest(100, Ypos, birdWidth, birdHeight);


    //setAngle
    angle = speed*5 - 10;
	if (angle <= -30)
    {
        angle = -30;
    }
	else if (angle >= 30)
	{
		angle = 30 ;
	}

	if(!isPlaying)
    {
        angle = 0;
    }
}

double Bird::GetTimeJump(double jumpTimer)
{
    return SDL_GetTicks();
}

void Bird::Jump()
{
    jumpTimer = SDL_GetTicks();
    if(jumpTimer - lastJump > 180)
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


void Bird::Reset()
{
    animationTimer = 0;
    Ypos = 384;
    speed = 0;
    gravity = 0.3;
    inJump = false;
    jumpHeight = -7.5;
    jumpTimer;
    lastJump = 0;
    setSrc(0,0, birdWidth, birdHeight);
    setDest(50,Ypos, birdWidth, birdHeight);
}


void Bird::Render(SDL_Renderer* renderer)
{
    animationTimer++;
    if(animationTimer <= 25) {
        SDL_RenderCopyEx(renderer, getTexture(), &getSrc(), &getDest(), angle, NULL, SDL_FLIP_NONE);
    }else if(animationTimer <= 50) {
        SDL_RenderCopyEx(renderer, Tex1, &getSrc(), &getDest(), angle, NULL, SDL_FLIP_NONE);
    }else if(animationTimer <= 75) {
        SDL_RenderCopyEx(renderer, Tex2, &getSrc(), &getDest(), angle, NULL, SDL_FLIP_NONE);
    }else {
        animationTimer = 0;
    }
}

