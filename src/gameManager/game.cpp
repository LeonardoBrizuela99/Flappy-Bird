#include "game.h"
#include "raylib.h"
#include "screenManager/screenGameplay.h"
#include "elementsManager/bird.h"
#include "elementsManager/wall.h"

static void update(Bird& bird, Wall& wall, Wall& wall2);
static bool birdCollision(Bird bird, Wall wall);
static bool screenWallCollision(Wall& wall);
void resetGame(Bird& bird, Wall& wall, Wall& wall2);
 void resetGame(Bird& bird, Wall& wall, Wall& wall2);

void runGame()
{
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Flappy Bird");

    Texture2D foreground = LoadTexture("res/textures/foreground.png");
    Texture2D midground = LoadTexture("res/textures/back-buildings.png");
    Texture2D background = LoadTexture("res/textures/far-buildings.png");

    Bird bird;
    Wall wall;
    Wall wall2;

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

    initBird(bird);
    initWall(wall);
    Vector2 offSetWall2 = { -500,100 };
    initWall(wall2, offSetWall2);

    while (!WindowShouldClose())
    {
        scrollingBack -= 10.0f * GetFrameTime();
        scrollingMid -= 50.0f * GetFrameTime();
        scrollingFore -= 100.0f * GetFrameTime();

        /*if (scrollingBack <= -background.width * 2) scrollingBack = 0;
        if (scrollingMid <= -midground.width * 2) scrollingMid = 0;*/
        if (scrollingFore <= -foreground.width * 2) scrollingFore = static_cast<float>((foreground.width * 2 / scrollingFore));

        update(bird, wall, wall2);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        //xcopy /y /i /s "$(ProjectDir)res" "$(OutDir)res"
        /*DrawTextureEx(background, Vector2 { scrollingBack, 300 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background, Vector2 { background.width * 2 + scrollingBack, 300}, 0.0f, 2.0f, WHITE);

        DrawTextureEx(midground, Vector2 { scrollingMid, 300 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(midground, Vector2 { midground.width * 2 + scrollingMid, 300 }, 0.0f, 2.0f, WHITE);*/

        DrawTextureEx(foreground, Vector2 { scrollingFore, 350 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(foreground, Vector2 { static_cast<float>(foreground.width * 2 + scrollingFore), 350 }, 0.0f, 2.0f, WHITE);

        /*
        @echo off

echo Configurando git...

git config --global user.email "zequiprieto@gmail.com"
git config --global user.name "zequi-pv"

echo Git configurado correctamente
        */

        drawGame(bird, wall,wall2);

        EndDrawing();
    }

    UnloadTexture(background);  
    UnloadTexture(midground);   
    UnloadTexture(foreground);
    CloseWindow();        
}

void update(Bird& bird, Wall& wall, Wall& wall2)
{
    if (IsKeyDown(KEY_UP)) bird.pos.y -= bird.speed * GetFrameTime();
    if (IsKeyDown(KEY_DOWN)) bird.pos.y += bird.speed * GetFrameTime();

    wall.pos.x -= wall.speed * GetFrameTime();
    wall2.pos.x -= wall2.speed * GetFrameTime();

    if (birdCollision(bird, wall) || birdCollision(bird, wall2))
    {
        resetGame(bird, wall, wall2);
    
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
}

bool birdCollision(Bird bird, Wall wall)
{
    return	bird.pos.x + bird.size.x > wall.pos.x
        && bird.pos.x < wall.pos.x + wall.size.x
        && bird.pos.y > wall.pos.y
        && bird.pos.y < wall.pos.y + wall.size.y;
}

bool screenWallCollision(Wall& wall)
{
    return wall.pos.x + wall.size.x <= 0;
}

void resetGame(Bird& bird, Wall& wall, Wall& wall2)
{
    initBird(bird);
    initWall(wall);
    initWall(wall2);
}