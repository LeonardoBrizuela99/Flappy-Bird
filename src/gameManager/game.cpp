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

static void update(Bird& bird, Wall& wall, Wall& wall2, bool& isGameOver, bool& isPaused, GameScreen& currentScreen, RectangleButton continueButton, RectangleButton backButton, RectangleButton restartButton);
static float timeSinceLastCollision = 0.0f;
static float collisionTimer = 0.0f;
static float collisionInterval = 1.0f;

void runGame()
{
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Flappy Bird");

    Texture2D foreground = LoadTexture("res/textures/background1.png");
    Texture2D midground = LoadTexture("res/textures/background2.png");
    Texture2D background = LoadTexture("res/textures/far-buildings.png");
    Texture2D tree = LoadTexture("res/textures/trees.png");
    Texture2D bushTop = LoadTexture("res/textures/frontleaves.png");
    Texture2D bushDown = LoadTexture("res/textures/pushes.png");
    Texture2D texBirdOne = LoadTexture("res/textures/Bird2.png");
    Texture2D texBirdTwo = LoadTexture("res/textures/Bird1.png");

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
   // RectangleButton rbackButton = {};
    RectangleButton creditsOne = {};
    RectangleButton creditsTwo = {};
    RectangleButton creditsThree = {};
    RectangleButton creditsFour = {};
    RectangleButton restartButton = {};

   /* float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;
    float scrollingTree = 0.0f;
    float scrollingBushTop = 0.0f;
    float scrollingBushDown = 0.0f;*/

   // drawRules(rbackButton,mouse);

    initBird(bird);
    bird.textureOne = texBirdOne;
    bird.textureTwo = texBirdTwo;
    initWall(wall);
    Vector2 offSetWall2 = { wall.pos.x,100 };
    initWall(wall2, offSetWall2);

    Vector2 buttonSize = {220, 50};
    playButton = initButton(playButton, buttonSize);
    rulesButton = initButton(rulesButton, buttonSize);
    restartButton = initButton(restartButton, buttonSize);
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

        currentScreen = GameScreen::GAMEPLAY;
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
            update(bird, wall, wall2, isGameOver, isPaused, currentScreen, continueButton, backButton, restartButton);
            drawGame(bird, wall, wall2/*, scrollingBack, scrollingMid, scrollingFore, scrollingTree, scrollingBushTop, scrollingBushDown, background, midground, foreground,tree,bushTop,bushDown*/, isPaused/*, isGameOver*/,continueButton, backButton, restartButton, mouse);
            break;
        case GameScreen::RULES:
            drawRules(backButton,mouse);
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
    UnloadTexture(tree);
    UnloadTexture(bushTop);
    UnloadTexture(bushDown);
    UnloadTexture(texBirdOne);
    UnloadTexture(texBirdTwo);
    CloseWindow();        
}

void update(Bird& bird, Wall& wall, Wall& wall2, bool& isGameOver, bool& isPaused, GameScreen& currentScreen,RectangleButton continueButton, RectangleButton backButton, RectangleButton restartButton)
{
    /*if (IsKeyPressed(KEY_ESCAPE))
    {
        isPaused = true;
       
    }*/
    DrawText("V 0.1",10,10, 40, RED);
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
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && restartButton.isSelected == true)
        {
            restartGame(bird, wall, wall2, isPaused);

        }
    }
   
   

    if (!isGameOver && !isPaused)
    {
        timeSinceLastCollision += GetFrameTime();

        if (bird.pos.y<0)
        {
            bird.pos.y = 0;

        }
        if (IsKeyDown(KEY_UP) )
        {
           /* bird.aceleration = 0.0f;
            bird.speed = bird.gravity / 2;
            bird.isRaising = true;
            cout << bird.pos.y << endl;*/
            bird.pos.y-=500*GetFrameTime();
        }
        else if(IsKeyDown(KEY_DOWN))
        {
           // bird.pos.y -= bird.speed * GetFrameTime();
            /*if (bird.aceleration>=bird.gravity)
            {
                bird.aceleration = bird.gravity;
                bird.isRaising = false;
            }*/
            bird.pos.y += 500 * GetFrameTime();
           /* bird.aceleration += bird.gravity * GetFrameTime();
            bird.speed -= bird.aceleration * GetFrameTime();*/
           
        }
     /*   bird.pos.y -= bird.speed * GetFrameTime();
       */
        wall.pos.x -= wall.speed * GetFrameTime();
        wall2.pos.x -= wall2.speed * GetFrameTime();

        if (timeSinceLastCollision>collisionInterval)
        {
            if (!wall.hit && birdWallCollision(bird, wall) || birdWallCollision(bird, wall2) || bird.pos.y >= GetScreenHeight())
            {
                wall.hit = true;
                bird.pos = { static_cast<float>(GetScreenWidth() / 2 - 300), static_cast<float>(GetScreenHeight() / 2) };
                bird.color = BLUE;
                bird.lives -= 1;
                bird.speed = 0.0f;
                collisionTimer = 1.0f;
                cout << bird.lives << endl;

            }
            if (!wall2.hit && birdWallCollision(bird, wall) || birdWallCollision(bird, wall2) || bird.pos.y >= GetScreenHeight())
            {
                wall2.hit = true;
                bird.pos = { static_cast<float>(GetScreenWidth() / 2 - 300), static_cast<float>(GetScreenHeight() / 2) };
                bird.color = BLUE;
                bird.lives -= 1;
                bird.speed = 0.0f;
                collisionTimer = 1.0f;
                cout << bird.lives << endl;

            }
        }
        
        if (wall.hit == true/*||wall2.hit==true*/)
        {
            collisionTimer -= GetFrameTime();

            if (collisionTimer <= 0.0f)
            {
                wall.hit = false;
                bird.color = RED;
            }

        }

        if ( wall2.hit == true)
        {
            collisionTimer -= GetFrameTime();

            if (collisionTimer <= 0.0f)
            {
                wall2.hit = false;
                bird.color = RED;
            }

        }
        timeSinceLastCollision += GetFrameTime();
    

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



//timeSinceLastCollision += GetFrameTime();
//
//if (timeSinceLastCollision > collisionInterval)
//{
//    if (!obs.hit && CheckCollisionRecs(GetBirdRect(player), GetRecObstacle(obstacle)) || player.pos.y > GetScreenHeight())
//    {
//        obs.hit = true;
//        player.vidas -= 1;
//        player.color = BLUE;
//        player.speed = 0.0f;
//        collisionTimer = 1.0f;
//
//        // Restablecer la posición del jugador
//        player.pos = { static_cast<float>(GetScreenWidth() / 2) - 500, static_cast<float>(GetScreenHeight() / 2) };
//
//#ifdef _DEBUG
//        cout << "vidas: " << player.vidas << endl;
//#endif
//        // Reiniciar el tiempo desde la última colisión
//        timeSinceLastCollision = 0.0f;
//
//        if (player.vidas <= 0)
//        {
//            endmatch = true;
//        }
//    }
//}
//if (obs.hit == true)
//{
//    collisionTimer -= GetFrameTime();
//
//    if (collisionTimer <= 0.0f)
//    {
//        obs.hit = false;
//        player.color = RED;
//    }
//
//}
//timeSinceLastCollision += GetFrameTime();
//}