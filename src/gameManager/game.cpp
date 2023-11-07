#include "game.h"
#include "raylib.h"
#include "screenManager/screenGameplay.h"
#include "elementsManager/bird.h"
#include "elementsManager/wall.h"

static void update(Bird& bird, Wall& wall);
static bool birdCollision(Bird bird, Wall wall);
static bool screenWallCollision(Wall& wall);
static void resetGame(Bird& bird, Wall& wall);

void runGame()
{
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Flappy Bird");

    Bird bird;
    Wall wall;

    initBird(bird);
    initWall(wall);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        drawGame(bird, wall);

        update(bird, wall);

        EndDrawing();
    }
    CloseWindow();        
}

void update(Bird& bird, Wall& wall)
{
    if (IsKeyDown(KEY_UP)) bird.pos.y -= 100.0f * GetFrameTime();
    if (IsKeyDown(KEY_DOWN)) bird.pos.y += 100.0f * GetFrameTime();

    wall.pos.x -= 100.0f * GetFrameTime();

    if (birdCollision(bird, wall))
    {
        resetGame(bird, wall);
    }

    if (screenWallCollision(wall))
    {
        wall.pos.x = GetScreenWidth() - wall.size.x;
        int randSize = GetRandomValue(150, 500);
        wall.size.y = static_cast<float>(randSize);
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
    return wall.pos.x <= 0;
}

void resetGame(Bird& bird, Wall& wall)
{
    initBird(bird);
    initWall(wall);
}