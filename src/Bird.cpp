#include "Bird.h"

Bird::Bird()
{
    animationTimer = 0;
    birdWidth = 96;
    birdHeight = 78;
    Ypos = 384;
    ver_speed = 0;
    gravity = 0.1;
    jumpHeight = -4;
    setSrc(0,0, birdWidth, birdHeight);
    setDest(50,Ypos, birdWidth, birdHeight);
}

void Bird::Gravity(bool isPlaying)
{
    if (isPlaying)
    {
        ver_speed += gravity;
        Ypos += ver_speed;
        setDest(50, Ypos, birdWidth, birdHeight);
        if(ver_speed >=5)
        {
            ver_speed = 5;
        }
    }

    angle = ver_speed*10 - 5;
    if(angle <= -20)
    {
        angle = -20;
    }else if(angle >= 20) {
        angle = 20;
    }
}


void Bird::Jump()
{
    ver_speed = jumpHeight;
}

void Bird::CreateTexture1(const char* filePath, SDL_Renderer* renderer)
{
    bird1 = TextureManager::Texture(filePath, renderer);
}

void Bird::Reset()
{
    animationTimer = 0;
    birdWidth = 96;
    birdHeight = 78;
    Ypos = 384;
    ver_speed = 0;
    angle = 0;
    gravity = 0.1;
    jumpHeight = -4;
    setSrc(0,0, birdWidth, birdHeight);
    setDest(50,Ypos, birdWidth, birdHeight);
}

void Bird::Grow()
{
    birdWidth += 5;
    birdHeight += 5;
    setDest(50,Ypos, birdWidth, birdHeight);
}

void Bird::Render(SDL_Renderer* renderer)
{
    animationTimer++;

    int frameDuration = 80 / 3;

    int frameIndex = (animationTimer / frameDuration) % 2;
    switch (frameIndex)
    {
    case 0:
        SDL_RenderCopyEx(renderer, bird1, &getSrc(), &getDest(), angle, NULL, SDL_FLIP_NONE);
        break;
    case 1:
        SDL_RenderCopyEx(renderer, getTexture(), &getSrc(), &getDest(), angle, NULL, SDL_FLIP_NONE);
        break;
    }
    if (animationTimer >= frameDuration * 2)
    {
        animationTimer = 0;
    }
}



