#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;

}

bool GameLoop::getGameState() {
    return GameState;
}

void GameLoop::Initialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if(window){
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            std::cout << "Succeeded!" << std::endl;
            GameState = true;
            bg.CreateTexture("assets/background-night.png", renderer);
        }else {
            std::cout << "Not created!" <<std::endl;
        }
    }else{
        std::cout << "window not created!" << std::endl;
    }
}

void GameLoop::Event() {
    SDL_PollEvent(&event1);
    if(event1.type == SDL_QUIT) {
        GameState = false;
    }
    if(event1.type == SDL_MOUSEMOTION)
    {
        std::cout << event1.motion.x << " " << event1.motion.y << std::endl;
    }
    if(event1.type == SDL_MOUSEBUTTONDOWN) {
        std::cout << "Mouse Pressed" << std::endl;
    }
    if(event1.type == SDL_KEYDOWN) {
        if(event1.key.keysym.sym == SDLK_SPACE) {
            std::cout << "UP!" << std::endl;
        }

    }
}
void GameLoop::Update() {


}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bg.getTexture(), NULL, NULL);
    SDL_RenderPresent(renderer);

}

void GameLoop::Clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
