#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    score.setSrc(0, 0, NULL, NULL);
    highestScore.setSrc(0, 0, NULL, NULL);
    score.setDest(184, 100, textWidth, textHeight);
    highestScore.setDest(216, 150, textWidth, textHeight);
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
            background.CreateTexture("assets/image/background.png", renderer);
            menuBg.CreateTexture("assets/image/menubackground.png", renderer);
            gameOverBg.CreateTexture("assets/image/gameoverbackground.png", renderer);

            //Bird
            bird.CreateTexture("assets/image/player1.png", renderer);
            bird.CreateTexture1("assets/image/player2.png", renderer);
            bird.CreateTexture2("assets/image/player3.png", renderer);

            //Floor
            floor1.CreateTexture("assets/image/land.png", renderer);
            floor2.CreateTexture("assets/image/land.png", renderer);
            //Pipe
            for(int i=0; i < 3; i++)
            {
                upPipe[i].CreateTexture("assets/image/pillarTop.png", renderer);
                downPipe[i].CreateTexture("assets/image/pillarBottom.png", renderer);
            }
            for(int i=0; i<3; i++) {
                upPipe[i].setPipe(i);
                downPipe[i].setPipe(i);
            }
            //Mouse
            mouse->CreateTexture("assets/image/mouse.png", renderer);
            //Button
            playButton->CreateTexture("assets/image/button.png",renderer);
            quitButton->CreateTexture("assets/image/button.png",renderer);
            replayButton->CreateTexture("assets/image/button.png", renderer);
            playButton->setCordinate(123,320);
            quitButton->setCordinate(123,420);
            replayButton->setCordinate(123,550);
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
    switch (currentState)
    {
        case MENU:
        {
            if(event.type == SDL_MOUSEBUTTONUP)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if(playButton->isSellected)
                    {
                        currentState = GAMEPLAY;
                    }
                    if(quitButton->isSellected)
                    {
                        GameState = false;
                    }
                }
            }
            break;
        }
        case GAMEPLAY:
        {
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_SPACE)
                {
                    if(!bird.JumpState() && isPlaying)
                    {
                        bird.Jump();
                    }
                    if(!isPlaying)
                    {
                        isPlaying = true;
                    }
                }
            }

            break;
        }
        case GAMEOVER:
        {
            if(event.type == SDL_MOUSEBUTTONUP)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if(replayButton->isSellected)
                    {
                        NewGame();
                        currentState = GAMEPLAY;
                    }
                }
            }
            break;
        }

    }
    if(event.type == SDL_QUIT)
    {
        GameState = false;
    }
}

bool GameLoop::CheckCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    return SDL_HasIntersection(&a, &b);
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
        currentState = GAMEOVER;
        ScoreUpdate();
    }

    //DownPipe
    if(CheckCollision((&bird)->getDest(), (&downPipe[0])->getDest()) ||
       CheckCollision((&bird)->getDest(), (&downPipe[0])->getDest()) ||
       CheckCollision((&bird)->getDest(), (&downPipe[0])->getDest()) )
    {
        isPlaying = false;
        isGameOver = true;
        currentState = GAMEOVER;
        ScoreUpdate();
    }

    //Floor
    if(CheckCollision((&bird)->getDest(), (&floor1)->getDest()) ||
       CheckCollision((&bird)->getDest(), (&floor2)->getDest()))
    {
        isPlaying = false;
        isGameOver = true;
        currentState = GAMEOVER;
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
                    // Adjust score text size based on the number of digits in the score
                    int scoreDigits = std::to_string(SCORE).length();
                    int textSizeMultiplier = scoreDigits > 1 ? 2 : 1; // Increase text size for two or more digits
                    int scoreTextWidth = textWidth * textSizeMultiplier;
                    // Calculate x-coordinate to center the score text
                    int xCenter = (WIDTH - scoreTextWidth) / 2;
                    score.setDest(xCenter, 100, scoreTextWidth, textHeight);
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

        // Reset score text size and position to default
        int xCenter = (WIDTH - textWidth) / 2;
        score.setDest(xCenter, 100, textWidth, textHeight);

        score.WriteText(to_string(SCORE), scoreFont, white, renderer);
    }
}




void GameLoop::Update() {
    if(currentState == GAMEPLAY)
    {
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
            ScoreUpdate();
        }

        //Floor
        floor1.Update1();
        floor2.Update2();
        //Test
        score.WriteText(to_string(SCORE), scoreFont, white, renderer);
        CollisionDetection();
    }
    if(currentState == MENU)
    {
        playButton->CheckSelected(mouse);
        quitButton->CheckSelected(mouse);
    }
    if(currentState == GAMEOVER)
    {
        replayButton->CheckSelected(mouse);
    }
    SDL_GetMouseState(&(mouse->cursor.x), &(mouse->cursor.y));
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);

    if(currentState == MENU)
    {
        menuBg.Render(renderer);
        playButton->Render(renderer);
        quitButton->Render(renderer);
    }
    else if(currentState == GAMEPLAY)
    {
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
        if(isPlaying && !isGameOver)
        {
            bird.Render(renderer);
            score.Render(renderer);
        }
    }else
    {
        gameOverBg.Render(renderer);
        replayButton->Render(renderer);
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
