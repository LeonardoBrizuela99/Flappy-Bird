#include "game.h"
#include "raylib.h"
#include "utilsManager/utils.h"
#include "screenManager/screenGameplay.h"
#include "screenManager/screenMenu.h"
#include "screenManager/screenCredits.h"
#include "elementsManager/bird.h"
#include "elementsManager/wall.h"
#include"screenManager/Rules.h"
#include<iostream>
using namespace std;

static void update(Bird& bird, Wall& wall, Wall& wall2, bool& isGameOver, bool& isPaused, GameScreen& currentScreen, RectangleButton continueButton, RectangleButton backButton);

void runGame()
{
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Flappy Bird");

    Texture2D foreground = LoadTexture("res/textures/foreground.png");
    Texture2D midground = LoadTexture("res/textures/back-buildings.png");
    Texture2D background = LoadTexture("res/textures/far-buildings.png");
    Texture2D texBirdOne = LoadTexture("res/textures/birdOne.png");
    Texture2D texBirdTwo = LoadTexture("res/textures/birdTwo.png");

    bool isGameRunning = true;
    bool isPaused = false;
    bool isGameOver = false;

    Bird bird;
    Wall wall;
    Wall wall2;
    GameScreen currentScreen = GameScreen::MENU;

    RectangleButton playButton = {};
    RectangleButton backButton = {};
    RectangleButton rulesButton = {};
    RectangleButton creditsButton = {};
    RectangleButton exitButton = {};
    RectangleButton continueButton = {};
    //RectangleButton backButton = {};
    RectangleButton creditsOne = {};
    RectangleButton creditsTwo = {};
    RectangleButton creditsThree = {};
    RectangleButton creditsFour = {};

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

    drawRules();

    initBird(bird);
    bird.textureOne = texBirdOne;
    bird.textureTwo = texBirdTwo;
    initWall(wall);
    Vector2 offSetWall2 = { wall.pos.x,100 };
    initWall(wall2, offSetWall2);

    Vector2 buttonSize = {220, 50};
    playButton = initButton(playButton, buttonSize);
    rulesButton = initButton(rulesButton, buttonSize);
    creditsButton = initButton(creditsButton, buttonSize);
    exitButton = initButton(exitButton, buttonSize);
    continueButton = initButton(continueButton, buttonSize);
    backButton = initButton(backButton, buttonSize);
    creditsOne = initButton(creditsOne, buttonSize);
    creditsTwo = initButton(creditsTwo, buttonSize);
    creditsThree = initButton(creditsThree, buttonSize);
    creditsFour = initButton(creditsFour, buttonSize);

    while (!WindowShouldClose() && isGameRunning)
    {
        SetExitKey(NULL);

        BeginDrawing();

        ClearBackground(BLACK);

        Vector2 mouse = { static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()) };

        switch (currentScreen)
        {
        case GameScreen::MENU:
            drawMenu(playButton,rulesButton, creditsButton, exitButton, mouse);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && playButton.isSelected == true)
            {
                currentScreen = GameScreen::GAMEPLAY;
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && rulesButton.isSelected == true)
            {
                currentScreen = GameScreen::RULES;
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && creditsButton.isSelected == true)
            {
                currentScreen = GameScreen::CREDITS;
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && exitButton.isSelected == true)
            {
                currentScreen = GameScreen::EXIT;
            }
            break;
        case GameScreen::GAMEPLAY:
            update(bird, wall, wall2, isGameOver, isPaused, currentScreen, continueButton, backButton);
            drawGame(bird, wall, wall2, scrollingBack, scrollingMid, scrollingFore, background, midground, foreground, isPaused, isGameOver,continueButton, backButton, mouse);
            break;
        case GameScreen::RULES:
            drawRules(/*backButton,mouse*/);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && backButton.isSelected == true)
            {
                currentScreen = GameScreen::MENU;
            }
            
            break;
        case GameScreen::CREDITS:
            drawCredits(backButton, creditsOne, creditsTwo, creditsThree, creditsFour, mouse);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && backButton.isSelected == true)
            {
                currentScreen = GameScreen::MENU;
            }
            break;
        case GameScreen::EXIT:
            isGameRunning = false;
            break;
        default:
            break;
        }
        EndDrawing();
    }

    UnloadTexture(background);  
    UnloadTexture(midground);   
    UnloadTexture(foreground);
    UnloadTexture(texBirdOne);
    UnloadTexture(texBirdTwo);
    CloseWindow();        
}

void update(Bird& bird, Wall& wall, Wall& wall2, bool& isGameOver, bool& isPaused, GameScreen& currentScreen,RectangleButton continueButton, RectangleButton backButton)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        isPaused = true;
       
    }
    if (isPaused)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && backButton.isSelected == true)
        {
            restartGame(bird, wall, wall2, isPaused);
            currentScreen = GameScreen::MENU;
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && continueButton.isSelected == true)
        {
            isPaused = false;
        }
    }
   
   

    if (!isGameOver && !isPaused)
    {
        if (bird.pos.y<0)
        {
            bird.pos.y = 0;

        }
        if (IsKeyPressed(KEY_UP) )
        {
            bird.aceleration = 0.0f;
            bird.speed = bird.gravity / 2;
            bird.isRaising = true;
            cout << bird.pos.y << endl;
        }
        else
        {

            if (bird.aceleration>=bird.gravity)
            {
                bird.aceleration = bird.gravity;
                bird.isRaising = false;
            }
           
            bird.aceleration += bird.gravity * GetFrameTime();
            bird.speed -= bird.aceleration * GetFrameTime();
            bird.pos.y -= bird.speed * GetFrameTime();
        }

       
        wall.pos.x -= wall.speed * GetFrameTime();
        wall2.pos.x -= wall2.speed * GetFrameTime();

        if (birdWallCollision(bird, wall) || birdWallCollision(bird, wall2)|| bird.pos.y>=GetScreenHeight())
        {
            bird.pos = { static_cast<float>(GetScreenWidth() / 2 - 300), static_cast<float>(GetScreenHeight() / 2) };
            bird.lives -= 1;
            cout << bird.lives << endl;
           
        }

        if (screenWallCollision(wall))
        {
            wall.pos.x = static_cast<float>(GetScreenWidth());
            int randSize = GetRandomValue(wall.minHeight, wall.maxHeight);
            wall.size.y = static_cast<float>(randSize);
        }

        if (screenWallCollision(wall2))
        {
            wall2.pos.x = static_cast<float>(GetScreenWidth());
            int randSize = GetRandomValue(wall2.minHeight, wall2.maxHeight);
            wall2.size.y = static_cast<float>(randSize);
        }

       /* if (screenBirdCollision(bird))
        {
            restartGame(bird, wall, wall2, isPaused);
        }*/
        if (bird.lives<=0)
        {
            isGameOver = true;
            resetGame(bird, wall, wall2, isPaused,isGameOver);
            currentScreen = GameScreen::MENU;
        }
    }
}