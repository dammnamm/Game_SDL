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
    pipes.resize(3);
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

            // Load textures for floor
            floor1.CreateTexture("assets/image/land.png", renderer);
            floor2.CreateTexture("assets/image/land.png", renderer);

            // Load textures for pipes
            for(int i=0; i<3; i++)
            {
                pipes[i].CreateTexture("assets/image/pillarBottom.png", renderer);
            }

            //Load textures for power

            power.CreateTexture("assets/image/coin.png", renderer);

            // Set positions and create textures for pipes
            for(int i=0; i<3; i++)
            {
                pipes[i].SetPosition(i);
            }
            power.set_coordinate();

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
            dieSound = Mix_LoadMUS("assets/sound/sfx_hit.wav");
            bgSound = Mix_LoadMUS("assets/sound/8_bit_rainy_city_lofi.mp3");
            inGameSound = Mix_LoadMUS("assets/sound/ingame.mp3");
            scoreSound = Mix_LoadWAV("assets/sound/scoresound.wav");
            power_collect_sounds = Mix_LoadWAV("assets/sound/power_collection.wav");
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
                if (isPlaying) {
                    bird.Jump();
                    Mix_PlayChannel(-1, wingSound, 0);
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



void GameLoop::CollisionManager()
{
    // Check collision with upper and lower pipes if in GamePlayState
    if (GamePlayState) {
        for (int i = 0; i < 3; ++i) {
            if (CheckCollision(bird.getDest(), pipes[i].getUpperDest()) ||
                CheckCollision(bird.getDest(), pipes[i].getLowerDest())) {
                HandleCollision();
                break;
            }
            if(CheckCollision(power.get_power_dest(), pipes[i].getUpperDest()) ||
               CheckCollision(power.get_power_dest(), pipes[i].getLowerDest())) {
                    power.set_coordinate();
                    break;
               }
        }

        // Check collision with floor
        if (CheckCollision(bird.getDest(), floor1.getDest()) ||
            CheckCollision(bird.getDest(), floor2.getDest())) {
            HandleCollision();
        }
        if(CheckCollision(bird.getDest(), power.get_power_dest()))
        {
            Mix_PlayChannel(-1, power_collect_sounds, 0);
            power.isEated = true;
            power.set_coordinate();
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
            if(birdLeft== pipes[i].getUpperDest().x )
            {
                if (!CheckCollision((&bird)->getDest(), pipes[i].getUpperDest()) &&
                    !CheckCollision((&bird)->getDest(), pipes[i].getLowerDest()))
                {
                    SCORE += 1;
                    Mix_PlayChannel(-1, scoreSound, 0);
                    int scoreDigits = std::to_string(SCORE).length();
                    int textSizeMultiplier = scoreDigits;
                    int scoreTextWidth = textWidth * textSizeMultiplier;
                    int xCenter = (WIDTH - scoreTextWidth) / 2;
                    score.setDest(xCenter, 200, scoreTextWidth, textHeight);
                }
            }
        }
    }
    if(GameOverState)
    {
        //SCORE
        highestScore.WriteText(to_string(highScore), scoreFont, white, renderer);
        score.setDest((375 - 250 - 32*int(to_string(SCORE).length())) / 2 + 250, 277, int(to_string(SCORE).length())*32, 50);
        highestScore.setDest((375 - 250 - 32*int(to_string(highScore).length())) / 2 + 250, 366, int(to_string(highScore).length())*32, 50);
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
            pipes[0].Update();
            pipes[1].Update();
            pipes[2].Update();
            //Power
            power.Update();
            //Score
            ScoreUpdate();

            //Floor
            floor1.Update1();
            floor2.Update2();
            //Test
            score.WriteText(to_string(SCORE), scoreFont, white, renderer);
            CollisionManager();
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
            pipes[0].Render(renderer);
            pipes[1].Render(renderer);
            pipes[2].Render(renderer);
            if(power.isEated == false)
            {
                power.Render(renderer);
            }
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
    isBgSoundPlaying = false;
    isIngameSoundPlaying = false;

    floor1.setDest(0, 650, 672, 224);
    floor2.setDest(672, 650, 672, 224);
    // Reset pipes
    pipes.clear();
    for (int i = 0; i < 3; ++i) {
        pipes[i].Reset(i);
    }

    int xCenter = (WIDTH - textWidth) / 2;
    score.setDest(xCenter, 200, textWidth, textHeight);

    score.WriteText(to_string(SCORE), scoreFont, white, renderer);
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
