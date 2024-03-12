#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"

#include "Bird.h"



class GameLoop
{
private:
    const int HEIGHT = 768;
    const int WIDTH = 432;
    bool GameState;
    SDL_Window* window;
    SDL_Event event1;
    SDL_Renderer* renderer;

    Bird bird;



public:
    GameLoop();
    bool getGameState();
    void Update();
    void Initialize();
    void Event();
    void Render();
    void Clear();
};
#endif // GAMELOOP_H
