#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    score.setSrc(0, 0, NULL, NULL);
    highestScore.setSrc(0, 0, NULL, NULL);
    score.setDest(216, 100, 32, 50);
    highestScore.setDest(216, 150, 32, 50);
    upPipe.resize(3);
    downPipe.resize(3);
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
            SDL_ShowCursor(SDL_DISABLE);
            std::cout << "Succeeded!" << std::endl;
            GameState = true;

            //Background
            background.CreateTexture("assets/image/background-night.png", renderer);

            //Bird
            bird.CreateTexture("assets/image/yellowbird-midflap.png", renderer);
            bird.CreateTexture1("assets/image/yellowbird-upflap.png", renderer);
            bird.CreateTexture2("assets/image/yellowbird-downflap.png", renderer);

            //Floor
            floor1.CreateTexture("assets/image/floor.png", renderer);
            floor2.CreateTexture("assets/image/floor.png", renderer);
            //Pipe
            for(int i=0; i < 3; i++)
            {
                upPipe[i].CreateTexture("assets/image/top-pipe.png", renderer);
                downPipe[i].CreateTexture("assets/image/bot-pipe.png", renderer);
            }
            for(int i=0; i<3; i++) {
                upPipe[i].setPipe(i);
                downPipe[i].setPipe(i);
            }
            mouse->CreateTexture("assets/image/mouse.png", renderer);
        }else {
            std::cout << "Not created!" <<std::endl;
        }
    }else{
        std::cout << "window not created!" << std::endl;
    }
    std::ifstream file("assets/highscore.txt");
    file >> highScore;
    file.close();
    if(TTF_Init() < 0)
    {
        std::cout << "Text faile to initialize! Error: " << TTF_GetError() << std::endl;
        Clear();
    }
    else
    {
        scoreFont = TTF_OpenFont("assets/font/flappy-bird-font/flappy-bird-font.ttf", fontsize);
        score.WriteText(to_string(SCORE), scoreFont, white, renderer);
        highestScore.WriteText(to_string(highScore), scoreFont, white, renderer);
    }
}

void GameLoop::Event() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        if(!isPlaying) {
            std::cout << "ISDIE" << std::endl;
            break;
        }
    case SDL_KEYDOWN:
    {
        if(event.key.keysym.sym == SDLK_SPACE)
        {
            if(!bird.JumpState() && isPlaying) {
                bird.Jump();
            }
        }
        if(event.key.keysym.sym == SDLK_SPACE && isGameOver)
        {
            NewGame();
        }
        break;
    }
    case SDL_QUIT:
    {
        GameState = false;
        break;
    }
    default:
        {
            Update();
            CollisionDetection();
            if(isPlaying)
            {
                ScoreUpdate();
            }
        }
    }
}

bool GameLoop::CheckCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    if (a.x + a.w < b.x) return false; // a is left of b
    if (a.x > b.x + b.w) return false; // a is right of b
    if (a.y + a.h < b.y) return false; // a is above b
    if (a.y > b.y + b.h) return false; // a is below b
    return true; // rectangles overlap
}



void GameLoop::CollisionDetection()
{
    //Upper Pipe
    if(CheckCollision((&bird)->getDest(), (&upPipe[0])->getDest()) ||
       CheckCollision((&bird)->getDest(), (&upPipe[0])->getDest()) ||
       CheckCollision((&bird)->getDest(), (&upPipe[0])->getDest()) )
    {
        isPlaying = false;
        isGameOver = true;
        ScoreUpdate();
    }

    //DownPipe
    if(CheckCollision((&bird)->getDest(), (&downPipe[0])->getDest()) ||
       CheckCollision((&bird)->getDest(), (&downPipe[0])->getDest()) ||
       CheckCollision((&bird)->getDest(), (&downPipe[0])->getDest()) )
    {
        isPlaying = false;
        isGameOver = true;
        ScoreUpdate();
    }

    //Floor
    if(CheckCollision((&bird)->getDest(), (&floor1)->getDest()) ||
       CheckCollision((&bird)->getDest(), (&floor2)->getDest()))
    {
        isPlaying = false;
        isGameOver = true;
        ScoreUpdate();
    }
}


void GameLoop::ScoreUpdate()
{
    if(isPlaying)
    {
        const int birdLeft = bird.getDest().x;
        //const int birdRight = bird.getDest().x + bird.getDest().w;
        for(int i=0; i<3; i++) {
            if(birdLeft + bird.getDest().w == upPipe[i].getDest().x )
            {
                if(!CheckCollision((&bird)->getDest(), (&upPipe[i])->getDest()) &&
                    !CheckCollision((&bird)->getDest(), (&downPipe[i])->getDest()))
                {
                    SCORE += 1;
                }
            }
        }
    }
    if(isGameOver)
    {
        if(SCORE > highScore) {
            highScore = SCORE;
        }
        SCORE = 0;
        std::ofstream write("assets/highscore.txt");
        write << highScore;
        write.close();

        score.WriteText(to_string(SCORE), scoreFont, white, renderer);
    }
}
void GameLoop::Update() {
    if(isPlaying) {
        //Bird
        bird.Gravity(isPlaying);
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
    //Test
    score.WriteText(to_string(SCORE), scoreFont, white, renderer);
    SDL_GetMouseState(&(mouse->cursor.x), &(mouse->cursor.y));
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
    background.Render(renderer);

    if(!isGameOver)
    {
        upPipe[0].Render(renderer);
        upPipe[1].Render(renderer);
        upPipe[2].Render(renderer);
        downPipe[0].Render(renderer);
        downPipe[1].Render(renderer);
        downPipe[2].Render(renderer);
    }
    floor1.Render(renderer);
    floor2.Render(renderer);
    if(isPlaying)
    {
        bird.Render(renderer);
        score.Render(renderer);
        if(SCORE < highScore)
        {
            highestScore.Render(renderer);
        }
    }
    mouse->Render(renderer);
    SDL_RenderPresent(renderer);
}


void GameLoop::NewGame()
{
    isGameOver = false;
    isPlaying = true;
    bird.Reset();
    upPipe.clear();
    downPipe.clear();
    for(int i=0; i<3; i++) {
        upPipe[i].setSrc(0, 0, 41, 253);
        downPipe[i].setSrc(0, 0, 41, 253);
        upPipe[i].setPipe(i);
        downPipe[i].setPipe(i);
    }
    std::ifstream read("assets/highscore.txt");
    read >> highScore;
    highestScore.WriteText(to_string(highScore), scoreFont, white, renderer);
    read.close();

    Render();
}

void GameLoop::Clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
