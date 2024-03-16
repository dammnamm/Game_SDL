#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "TextureManager.h"

#include "Bird.h"
#include "Pipe.h"


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

    Pipe pipe[3];


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
