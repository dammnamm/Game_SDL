#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    for(int i=0; i<3; i++) {
        upPipe[i].setSrc(0,0,41,253);
    }
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

            //Bird
            bird.CreateTexture("assets/yellowbird-midflap.png", renderer);
            bird.CreateTexture1("assets/yellowbird-upflap.png", renderer);
            bird.CreateTexture2("assets/yellowbird-downflap.png", renderer);

            //Pipe
            for(int i=0; i < 3; i++)
            {
                upPipe[i].CreateTexture("assets/top-pipe.png", renderer);
            }
            for(int i=0; i<3; i++) {
                upPipe[i].setPipe(i);
            }
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
            bird.Jump();
        }

    }
}
void GameLoop::Update() {

    bird.Gravity();
    upPipe[0].upPipeUpdate(0);
    upPipe[1].upPipeUpdate(1);
    upPipe[2].upPipeUpdate(2);
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);

    for(Pipe x: upPipe) {
        x.Render(renderer);
    }


    bird.Render(renderer);
    SDL_RenderPresent(renderer);

}

void GameLoop::Clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
