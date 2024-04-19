#include "GameLoop.h"

using namespace std;

GameLoop* g = new GameLoop();

int main(int argc, char* argv[])
{
    const int FPS = 144;
    const int FrameDelay = 1000/FPS;
    Uint32 FrameStart;
    int FrameTime;

    g->Initialize();
    while(g->getGameState()){
        FrameStart = SDL_GetTicks();
        g->Render();
        g->Event();
        g->Update();
        FrameTime = SDL_GetTicks() - FrameStart;
        if (FrameDelay > FrameTime) {
            SDL_Delay(FrameDelay - FrameTime);
        }
    }
    g->Clear();
    return 0;
}
