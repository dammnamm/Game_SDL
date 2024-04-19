#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    // Game objects initialization
    floor1.setDest(0, 650, 672, 224);
    score.setSrc(0, 0, NULL, NULL);
    highestScore.setSrc(0, 0, NULL, NULL);
    score.setDest(184, 200, textWidth, textHeight);
    highestScore.setDest(184, 500, textWidth, textHeight);
    message.setSrc(0, 0, 146, 210);
    message.setDest(5, -40, 146 * 3 - 10, 210 * 3 - 10);
    // Game state flags
    bool MenuState = false;
    bool GamePlayState = false;
    bool GameOverState = false;

    // Sound initialization
    clickSound = NULL;
    wingSound = NULL;
    dieSound = NULL;
    bgSound = NULL;
    scoreSound = NULL;
    inGameSound = NULL;

    // Resize vectors
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
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer) {
            // Disable cursor and initialize game state variables
            SDL_ShowCursor(SDL_DISABLE);
            std::cout << "Succeeded!" << std::endl;
            GameState = true;
            MenuState = true;

            // Load textures for background, message, menu, and game over backgrounds
            background.CreateTexture("assets/image/background.png", renderer);
            message.CreateTexture("assets/image/message.png", renderer);
            menuBg.CreateTexture("assets/image/menubackground.png", renderer);
            gameOverBg.CreateTexture("assets/image/gameoverbackground.png", renderer);

            // Load textures for bird and its different states
            bird.CreateTexture("assets/image/player1.png", renderer);
            bird.CreateTexture1("assets/image/player2.png", renderer);
            bird.CreateTexture2("assets/image/player3.png", renderer);

            // Load textures for floor
            floor1.CreateTexture("assets/image/land.png", renderer);
            floor2.CreateTexture("assets/image/land.png", renderer);

            // Load textures for pipes
            for (int i = 0; i < 3; i++)
            {
                upPipe[i].CreateTexture("assets/image/pillarTop.png", renderer);
                downPipe[i].CreateTexture("assets/image/pillarBottom.png", renderer);
            }

            // Set positions and create textures for pipes
            for (int i = 0; i < 3; i++) {
                upPipe[i].setPipe(i);
                downPipe[i].setPipe(i);
            }

            // Load texture for mouse cursor
            mouse->CreateTexture("assets/image/mouse.png", renderer);

            // Load textures and set positions for buttons
            playButton->CreateTexture("assets/image/button.png", renderer);
            quitButton->CreateTexture("assets/image/button.png", renderer);
            replayButton->CreateTexture("assets/image/button.png", renderer);
            exitButton->CreateTexture("assets/image/button.png", renderer);

            // Set positions for buttons
            playButton->setCordinate(123, 320);
            quitButton->setCordinate(123, 420);
            replayButton->setCordinate(25, 550);
            exitButton->setCordinate(220, 550);
        }else {
            std::cout << "Not created!" <<std::endl;
        }
    }else{
        std::cout << "window not created!" << std::endl;
    }
    std::ifstream file("assets/highscore.txt");
    file >> highScore;
    file.close();

    //TTF
    if(TTF_Init() < 0)
    {
        std::cout << "Text failed to initialize! Error: " << TTF_GetError() << std::endl;
        Clear();
    }
    else
    {
        scoreFont = TTF_OpenFont("assets/font/flappy-bird-font/flappy-bird-font.ttf", fontsize);
        score.WriteText(to_string(SCORE), scoreFont, white, renderer);
        highestScore.WriteText(to_string(highScore), scoreFont, white, renderer);
    }

    //MIXER
    if(SDL_Init(SDL_INIT_AUDIO < 0))
    {
        std::cout << "Audio failed to initialize! Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cout << "SDL_mixer failed to initialize! Error: " << Mix_GetError() << std::endl;
        }
        else
        {
            clickSound = Mix_LoadWAV("assets/sound/mouse_click.wav");
            wingSound = Mix_LoadWAV("assets/sound/sfx_wing.wav");
            dieSound = Mix_LoadMUS("assets/sound/sfx_die.wav");
            bgSound = Mix_LoadMUS("assets/sound/8_bit_rainy_city_lofi.mp3");
            inGameSound = Mix_LoadMUS("assets/sound/ingame.mp3");
            scoreSound = Mix_LoadWAV("assets/sound/scoresound.wav");
        }
    }
}

void GameLoop::Event() {
    SDL_Event event;
    SDL_PollEvent(&event);

    if (MenuState) {
        if (!isBgSoundPlaying) {
            Mix_PlayMusic(bgSound,-1);
            isBgSoundPlaying = true;
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (playButton->isSellected) {
                    GamePlayState = true;
                    MenuState = false;
                    GameOverState = false;
                }
                if (quitButton->isSellected) {
                    GameState = false;
                }
            }
        }
    }
    if (GamePlayState) {
        if (!isIngameSoundPlaying)
        {
            Mix_PlayMusic(inGameSound,-1);
            isIngameSoundPlaying = true;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE) {
                if (!bird.JumpState() && isPlaying) {
                    bird.Jump();
                    Mix_PlayChannel(-1, wingSound, 0);;
                }
                if (!isPlaying || isGameOver) {
                    isPlaying = true;
                    isGameOver = false;
                }
            }
        }
    }
    if (GameOverState) {
        if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (replayButton->isSellected)
                {
                    isIngameSoundPlaying = false;
                    MenuState = false;
                    GamePlayState = true;
                    GameOverState = false;
                    NewGame();
                }
                if (exitButton->isSellected) {
                    MenuState = true;
                    GameOverState = false;
                    GamePlayState = false;
                    isBgSoundPlaying = false;
                    NewGame();
                }
            }
        }
    }

    if (event.type == SDL_QUIT) {
        GameState = false;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            Mix_PlayChannel(-1, clickSound, 0);
            std::cout << mouse->cursor.x << " " << mouse->cursor.y << std::endl;
        }
    }
}


bool GameLoop::CheckCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    return SDL_HasIntersection(&a, &b);
}



void GameLoop::CollisionDetection()
{
    // Check collision with upper and lower pipes if in GamePlayState
    if (GamePlayState) {
        for (int i = 0; i < 3; ++i) {
            if (CheckCollision(bird.getDest(), upPipe[i].getDest()) ||
                CheckCollision(bird.getDest(), downPipe[i].getDest())) {
                HandleCollision();
                break;
            }
        }

        // Check collision with floor
        if (CheckCollision(bird.getDest(), floor1.getDest()) ||
            CheckCollision(bird.getDest(), floor2.getDest())) {
            HandleCollision();
        }
    }
}

void GameLoop::HandleCollision()
{
    if (GamePlayState) {
        isPlaying = false;
        isGameOver = true;
        GamePlayState = false;
        GameOverState = true;
        Mix_PlayMusic(dieSound, 1);
        ScoreUpdate();
    }
}




void GameLoop::ScoreUpdate()
{
    if(GamePlayState)
    {
        const int birdLeft = bird.getDest().x;
        for(int i=0; i<3; i++) {
            if(birdLeft== upPipe[i].getDest().x )
            {
                if(!CheckCollision((&bird)->getDest(), (&upPipe[i])->getDest()) &&
                    !CheckCollision((&bird)->getDest(), (&downPipe[i])->getDest()))
                {
                    SCORE += 1;
                    Mix_PlayChannel(-1, scoreSound, 0);
                    // Adjust score text size based on the number of digits in the score
                    int scoreDigits = std::to_string(SCORE).length();
                    int textSizeMultiplier = scoreDigits > 1 ? 2 : 1; // Increase text size for two or more digits
                    int scoreTextWidth = textWidth * textSizeMultiplier;
                    // Calculate x-coordinate to center the score text
                    int xCenter = (WIDTH - scoreTextWidth) / 2;
                    score.setDest(xCenter, 200, scoreTextWidth, textHeight);
                }
            }
        }
    }
    if(GameOverState)
    {
        //SCORE
        score.setDest((375 - 250 - 32*int(to_string(SCORE).length())) / 2 + 250, 277, int(to_string(SCORE).length())*32, 50);
        highestScore.setDest((375 - 250 - 32*int(to_string(highScore).length())) / 2 + 250, 370, int(to_string(highScore).length())*32 - 5, 50);
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
    }
}


void GameLoop::Update() {
    if(GamePlayState)
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

            //Floor
            floor1.Update1();
            floor2.Update2();
            //Test
            score.WriteText(to_string(SCORE), scoreFont, white, renderer);
            CollisionDetection();
        }

    }
    if(MenuState)
    {
        playButton->CheckSelected(mouse);
        quitButton->CheckSelected(mouse);
    }
    if(GameOverState)
    {
        replayButton->CheckSelected(mouse);
        exitButton->CheckSelected(mouse);
    }
    SDL_GetMouseState(&(mouse->cursor.x), &(mouse->cursor.y));
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);

    if(MenuState)
    {
        menuBg.Render(renderer);
        playButton->Render(renderer);
        quitButton->Render(renderer);
    }
    if(GamePlayState)
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
        score.Render(renderer);
        if(!isPlaying)
        {
            message.Render(renderer);
        }
        floor1.Render(renderer);
        floor2.Render(renderer);
        bird.Render(renderer);
    }
    if(GameOverState)
    {
        gameOverBg.Render(renderer);
        replayButton->Render(renderer);
        exitButton->Render(renderer);
        score.Render(renderer);
        highestScore.Render(renderer);
    }
    mouse->Render(renderer);
    SDL_RenderPresent(renderer);
}


void GameLoop::NewGame() {
    isGameOver = false;
    isPlaying = false;
    bird.Reset();
    floor1.setDest(0, 650, 672, 224);
    floor2.setDest(672, 650, 672, 224);
    upPipe.clear();
    downPipe.clear();
    // Reset pipes
    for (int i = 0; i < 3; ++i) {
        upPipe[i].setSrc(0, 0, 84, 501);
        downPipe[i].setSrc(0, 0, 84, 501);
        upPipe[i].setPipe(i);
        downPipe[i].setPipe(i);
    }

    int xCenter = (WIDTH - textWidth) / 2;
    score.setDest(xCenter, 200, textWidth, textHeight);

    score.WriteText(to_string(SCORE), scoreFont, white, renderer);
    // Read high score from file
    std::ifstream read("assets/highscore.txt");
    read >> highScore;
    highestScore.WriteText(std::to_string(highScore), scoreFont, white, renderer);
    read.close();
}


void GameLoop::Clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
