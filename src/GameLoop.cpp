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

            //Background
            background.CreateTexture("assets/background-night.png", renderer);

            //Bird
            bird.CreateTexture("assets/yellowbird-midflap.png", renderer);
            bird.CreateTexture1("assets/yellowbird-upflap.png", renderer);
            bird.CreateTexture2("assets/yellowbird-downflap.png", renderer);

            //Floor
            floor1.CreateTexture("assets/floor.png", renderer);
            floor2.CreateTexture("assets/floor.png", renderer);
            //Pipe
            for(int i=0; i < 3; i++)
            {
                upPipe[i].CreateTexture("assets/top-pipe.png", renderer);
                downPipe[i].CreateTexture("assets/bot-pipe.png", renderer);
            }
            for(int i=0; i<3; i++) {
                upPipe[i].setPipe(i);
                downPipe[i].setPipe(i);
            }
        }else {
            std::cout << "Not created!" <<std::endl;
        }
    }else{
        std::cout << "window not created!" << std::endl;
    }
}

void GameLoop::Event() {
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) {
        GameState = false;
    }
    if(event.type == SDL_MOUSEBUTTONDOWN) {
        std::cout << "Mouse Pressed" << std::endl;
    }
    if(event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_SPACE) {
            std::cout << "UP!" << std::endl;
            bird.Jump();
        }
    }
}

bool GameLoop::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    return SDL_HasIntersection(&object1, &object2);
}

void GameLoop::CollisionDetection()
{
    //upPipeCheck
    if(CheckCollision((&bird)->getDest(), (&upPipe[0])->getDest())||
       CheckCollision((&bird)->getDest(), (&upPipe[1])->getDest())||
       CheckCollision((&bird)->getDest(), (&upPipe[2])->getDest()))
    {
        GameActive = false;
    }
    //downPipeCheck
    if(CheckCollision((&bird)->getDest(), (&downPipe[0])->getDest())||
       CheckCollision((&bird)->getDest(), (&downPipe[1])->getDest())||
       CheckCollision((&bird)->getDest(), (&downPipe[2])->getDest()))
    {
        GameActive = false;
    }
}
void GameLoop::Update() {
    if(GameActive)
    {
        //Bird
        bird.Gravity();
        //Pipe
        upPipe[0].upPipeUpdate(0);
        upPipe[1].upPipeUpdate(1);
        upPipe[2].upPipeUpdate(2);
        downPipe[0].downPipeUpdate(0);
        downPipe[1].downPipeUpdate(1);
        downPipe[2].downPipeUpdate(2);
    }
    //Floor
    floor1.Update1();
    floor2.Update2();
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
    background.Render(renderer);
    floor1.Render(renderer);
    floor2.Render(renderer);
    if(GameActive)
    {
        upPipe[0].Render(renderer);
        upPipe[1].Render(renderer);
        upPipe[2].Render(renderer);
        downPipe[0].Render(renderer);
        downPipe[1].Render(renderer);
        downPipe[2].Render(renderer);
        bird.Render(renderer);
    }
    SDL_RenderPresent(renderer);

}

void GameLoop::Clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
