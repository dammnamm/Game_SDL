#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    // Game objects initialization
    floor1.setDest(0, 650, 672, 224);
    heart_image.setSrc(0,0, 47, 41);
    heart_image.setDest(10,10, 30, 30);
    //TextObject
    score.setSrc(0, 0, NULL, NULL);
    highestScore.setSrc(0, 0, NULL, NULL);
    heart_object.setSrc(0,0, NULL, NULL);
    score.setDest(184, 200, textWidth, textHeight);
    highestScore.setDest(184, 500, textWidth, textHeight);
    heart_object.setDest(45, 10 , textWidth/3, textHeight/3);
    message.setSrc(0,0, NULL, NULL);
    message.setDest(0,590,messageWidth, messageHeight);
    settingBg.setSrc(0 ,0, 216, 384);
    settingBg.setDest(105, 177, 216, 394);
    background.setSrc(0, 0, 432, 768);
    gameOverBg.setSrc(0,0, 384, 768);
    gameOverBg.setDest(0,0, 432, 768);
    menuBg.setSrc(0,0, 384, 768);
    menuBg.setDest(0,0, 432, 768);
    frame.setSrc(0,0, 220, 384);
    frame.setDest(103, 175, 220, 394);
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
    //Power
    powers.push_back(titan);
    powers.push_back(heart);
    powers.push_back(slow);
    current_power = rand()%3;
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
            menuBg.CreateTexture("assets/image/menubackground.png", renderer);
            gameOverBg.CreateTexture("assets/image/gameoverbackground.png", renderer);
            settingBg.CreateTexture("assets/image/theme_setting.png", renderer);
            frame.CreateTexture("assets/image/frame.png", renderer);

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
            powers[0].CreateTexture("assets/image/titan.png", renderer);
            powers[1].CreateTexture("assets/image/heart.png", renderer);
            heart_image.CreateTexture("assets/image/_heart.png", renderer);
            powers[2].CreateTexture("assets/image/slow.png", renderer);

            // Set positions and create textures for pipes
            for(int i=0; i<3; i++)
            {
                pipes[i].SetPosition(i);
            }
            // Set positions and create textures for powers
            powers[current_power].set_coordinate();
            // Load texture for mouse cursor
            mouse->CreateTexture("assets/image/mouse.png", renderer);

            // Load textures and set positions for buttons
            playButton->CreateTexture("assets/image/button.png", renderer);
            quitButton->CreateTexture("assets/image/button.png", renderer);
            replayButton->CreateTexture("assets/image/button.png", renderer);
            exitButton->CreateTexture("assets/image/button.png", renderer);
            settingButton->CreateTexture("assets/image/button.png", renderer);
            backButton->CreateTexture("assets/image/button.png", renderer);
            questionButton->CreateTexture("assets/image/button.png", renderer);
            soundButton->CreateTexture("assets/image/button.png", renderer);
            back_button->CreateTexture("assets/image/button.png", renderer);
            next_button->CreateTexture("assets/image/button.png", renderer);

            // Set positions for buttons
            playButton->setCordinate(123, 320);
            quitButton->setCordinate(123, 420);
            replayButton->setCordinate(25, 550);
            exitButton->setCordinate(220, 550);
            settingButton->setCordinate(360,0);
            backButton->setCordinate(0,0);
            questionButton->setCordinate(360,650);
            soundButton->setCordinate(10,682);
            back_button->setCordinate(10, 385);
            next_button->setCordinate(355, 385);
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
        message_font = TTF_OpenFont("assets/font/flappy-bird-font/CottonCloud.ttf", 20);
        score.WriteText(to_string(SCORE), scoreFont, white, renderer);
        highestScore.WriteText(to_string(highScore), scoreFont, white, renderer);
        message.WriteText(text, message_font, white, renderer);
        heart_object.WriteText("x" + to_string(heart_cnt), scoreFont, white, renderer);
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
            Mix_VolumeMusic(50);
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
                if(settingButton->isSellected) {
                    SettingState = true;
                    MenuState = false;
                }
                if(soundButton->isSellected)
                {
                    if(PlaySound)
                    {
                        soundButton->set_src_xy(0, 1280);
                        soundButton->setCordinate(10, 682);
                        PlaySound = false;
                        Mix_VolumeMusic(0);
                        Mix_Volume(-1, 0);
                    }else {
                        soundButton->set_src_xy(0, 1100);
                        soundButton->setCordinate(10, 682);
                        PlaySound = true;
                        soundButton->Render(renderer);
                        Mix_VolumeMusic(50);
                        Mix_Volume(-1, 50);
                    }
                }
            }
        }
    }
    if (SettingState)
    {
        if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (backButton->isSellected)
                {
                    MenuState = true;
                    SettingState = false;
                    backButton->isSellected = false;
                }
                if(next_button->isSellected)
                {
                    settingBg.scroll(216,648);
                    background.scroll(432, 1296);
                    gameOverBg.scroll(384, 1152);
                    menuBg.scroll(384, 1152);
                    floor1.scroll(396, 1188);
                    floor2.scroll(396, 1188);
                    for(int i=0; i<3; i++)
                    {
                        pipes[i].scroll(84, 252);
                    }
                    next_button->isSellected = false;
                }
                if(back_button->isSellected)
                {
                    settingBg.scroll(-216,648);
                    background.scroll(-432,1296);
                    gameOverBg.scroll(-384,1152);
                    menuBg.scroll(-384, 1152);
                    floor1.scroll(-396, 1188);
                    floor2.scroll(-396, 1188);
                    for(int i=0; i<3; i++)
                    {
                        pipes[i].scroll(-84, 252);
                    }
                    back_button->isSellected = false;
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
            std::cout << mouse->tip.x << " " << mouse->tip.y << std::endl;
        }
    }
}


bool GameLoop::CheckCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    SDL_Rect a_temp = {a.x, a.y, a.w, a.h};
    a_temp.w = a_temp.w * 0.8;
    a_temp.h = a_temp.h * 0.8;
    SDL_Rect b_temp = {b.x, b.y, b.w, b.h};

    return SDL_HasIntersection(&a_temp, &b);
}



void GameLoop::CollisionManager() {
    if (GamePlayState) {
        for (int i = 0; i < 3; ++i) {
            if (CheckCollision(bird.getDest(), pipes[i].getUpperDest()) ||
                CheckCollision(bird.getDest(), pipes[i].getLowerDest())) {
                if (!pipes[i].isCollide) {
                    heart_cnt -= 1;
                    pipes[i].isCollide = true;
                }
                break;
            }
        }

        // Check collision with floor
        if (CheckCollision(bird.getDest(), floor1.getDest()) ||
            CheckCollision(bird.getDest(), floor2.getDest())) {
            heart_cnt--;
        }

        for (int i = 0; i < 3; ++i) {
            if (CheckCollision(powers[current_power].get_power_dest(), pipes[i].getUpperDest()) ||
                CheckCollision(powers[current_power].get_power_dest(), pipes[i].getLowerDest())) {
                powers[current_power].set_coordinate();
                break;
            }
        }



        if (CheckCollision(bird.getDest(), powers[current_power].get_power_dest())) {
            if (!powers[current_power].isEated) {
                powers[current_power].isEated = true;
                if (current_power == 0) {
                    isTitan = true;
                } else if (current_power == 1) {
                        isHeart = true;
                } else if (current_power == 2) {
                        is_slow = true;
                }
                current_power = rand() % 3;
                Mix_PlayChannel(-1, power_collect_sounds, 0);
                }
        }

        PowerManager();
        //HandleCollision();
    }
}


void GameLoop::HandleCollision()
{
    if(heart_cnt == 0) {
        isPlaying = false;
        isGameOver = true;
        GamePlayState = false;
        GameOverState = true;
        Mix_PlayMusic(dieSound, 1);
        ScoreUpdate();
        SDL_Delay(500);
        FPS = 144;
    }
}

void GameLoop::PowerManager()
{
    if(isTitan)
    {
        bird.Grow();
        isTitan = false;
    }
    if(isHeart)
    {
        heart_cnt++;
        isHeart = false;
    }
    if(is_slow)
    {
        if(slow_timer == 0)
        {
            slow_timer  = 200;
        }
        FPS = 60;
        slow_timer--;
        if(slow_timer <= 0)
        {
            slow_timer = 0;
            FPS = 144;
            is_slow = false;
        }
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
            pipes[0].Horizontal_Move();
            pipes[1].Horizontal_Move();
            pipes[2].Horizontal_Move();
            if(SCORE >=8 && SCORE <= 15)
            {
                pipes[0].Vertical_Move();
                pipes[1].Vertical_Move();
                pipes[2].Vertical_Move();
            }
            if(SCORE >=15)
            {
                pipes[0].Vertical_Move();
                pipes[1].Vertical_Move();
                pipes[2].Vertical_Move();
                pipes[0].Angle_Update();
                pipes[1].Angle_Update();
                pipes[2].Angle_Update();
            }
            //Power
            powers[current_power].Update();
            //Score
            ScoreUpdate();

            //Floor
            floor1.Update1();
            floor2.Update2();
            //Test
            score.WriteText(to_string(SCORE), scoreFont, white, renderer);
            highestScore.WriteText(to_string(SCORE), scoreFont, white, renderer);
            heart_object.WriteText("x" + to_string(heart_cnt), scoreFont, white, renderer);
            CollisionManager();
        }

    }
    if(MenuState)
    {
        playButton->CheckSelected(mouse);
        quitButton->CheckSelected(mouse);
        settingButton->CheckSelected(mouse);
        questionButton->CheckSelected(mouse);
        soundButton->CheckSelected(mouse);
    }
    if(SettingState)
    {
        backButton->CheckSelected(mouse);
        back_button->CheckSelected(mouse);
        next_button->CheckSelected(mouse);
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
        settingButton->Render(renderer);
        questionButton->Render(renderer);
        if(questionButton->isSellected)
        {
            message.Render(renderer);
        }
        soundButton->Render(renderer);
    }

    if(SettingState)
    {
        background.Render(renderer);
        settingBg.Render(renderer);
        backButton->Render(renderer);
        back_button->Render(renderer);
        next_button->Render(renderer);
        frame.Render(renderer);
    }
    if(GamePlayState)
    {
        background.Render(renderer);
        if(!isGameOver)
        {
            pipes[0].Render(renderer);
            pipes[1].Render(renderer);
            pipes[2].Render(renderer);
            if(!powers[current_power].isEated)
            {
                powers[current_power].Render(renderer);
            }
        }
        score.Render(renderer);
        heart_object.Render(renderer);
        floor1.Render(renderer);
        floor2.Render(renderer);
        bird.Render(renderer);
        heart_image.Render(renderer);
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
    heart_cnt = 1;
    floor1.setDest(0, 650, 672, 224);
    floor2.setDest(672, 650, 672, 224);
    isTitan = false;
    is_slow = false;
    isHeart = false;
    slow_timer = 0;
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
