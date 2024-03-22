#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "TextureManager.h"

#include "Background.h"
#include "Floor.h"
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
    Background background;
    Bird bird;
    Floor floor1;
    Floor floor2;
    Pipe upPipe[3];
    Pipe downPipe[3];


public:
    GameLoop();
    bool getGameState();
    void Update();
    void Initialize();
    void Event();
    void Render();
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    void Clear();
};
#endif // GAMELOOP_H
