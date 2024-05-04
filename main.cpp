#include "GameLoop.h"
#include "GameSetting.h"
using namespace std;

GameLoop* g = new GameLoop();

int main(int argc, char* argv[])
{
    Uint32 FrameStart;
    int FrameTime;
    g->Initialize();
    while(g->getGameState()){
        const int FrameDelay = 1000/FPS;
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
