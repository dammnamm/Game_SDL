#ifndef GAMELOOP_H
#define GAMELOOP_H
#include <bits/stdc++.h>
#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "TextureManager.h"

#include "Background.h"
#include "Floor.h"
#include "Bird.h"
#include "Pipe.h"
#include "Mouse.h"
#include "Button.h"
#include "TextObject.h"
#include "Power.h"

#include "GameSetting.h"

class GameLoop
{
private:
    // Constants
    const int WIDTH = 432;
    const int HEIGHT = 768;
    const int fontsize = 24;
    const int textWidth = 64;
    const int textHeight = 100;

    // SDL Variables
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Game State
    bool GameState;

    // Background Objects
    Background background;
    Background gameOverBg;
    Background menuBg;
    Background settingBg;
    Background frame;

    // Bird and Floor
    Bird bird;
    Floor floor1;
    Floor floor2;

    // Pipes
    std::vector<Pipe> pipes;

    // Mouse
    Mouse* mouse = new Mouse;

    // Buttons
    Button* replayButton = new Button(0, 736);
    Button* exitButton = new Button(0, 368);
    Button* playButton = new Button(0, 0);
    Button* quitButton = new Button(0, 920);
    Button* settingButton = new Button(0, 1576);
    Button* backButton = new Button(0, 1751);
    Button* questionButton = new Button(0, 1400);
    Button* soundButton = new Button(0, 1100);
    Button* back_button = new Button(0, 1940);
    Button* next_button = new Button(0, 2100);
    // Game State Flags
    bool MenuState;
    bool GamePlayState;
    bool GameOverState;
    bool isPlaying = false;
    bool isGameOver = false;
    bool gameStarted = false;
    bool isBgSoundPlaying = false;
    bool isIngameSoundPlaying = false;
    bool SettingState = false;

    // Score
    int SCORE = 0;
    int highScore;
    TextObject highestScore;
    TextObject score;
    TTF_Font* scoreFont;
    SDL_Color white = { 250, 250, 250 };

    // Heart
    Power heart;
    int heart_cnt = 1;
    TextObject heart_object;
    Background heart_image;
    // Sound
    Mix_Chunk* scoreSound;
    Mix_Chunk* clickSound;
    Mix_Chunk* wingSound;
    Mix_Music* dieSound;
    Mix_Music* bgSound;
    Mix_Music* inGameSound;
    Mix_Chunk* power_collect_sounds;
    bool PlaySound = true;
    //Power
    Power titan;

    //Slow
    Power slow;
    int slow_timer = 0;
    bool is_slow = false;
    //Message
    TextObject message;
    TTF_Font*  message_font;
    const int messageWidth = 432;
    const int messageHeight = 50;
    std::string text = "PRESS SPACE TO JUMP";
public:
    // Constructor
    GameLoop();
    // Member functions
    void Initialize();
    void Event();
    void Update();
    void Render();
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    void CollisionManager();
    void ScoreUpdate();
    void HandleCollision();
    void NewGame();
    void Clear();
    bool getGameState();
};
#endif // GAMELOOP_H
