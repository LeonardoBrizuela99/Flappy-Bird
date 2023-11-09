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

    Bird bird;
    Wall wall;
    Wall wall2;

    initBird(bird);
    initWall(wall);
    Vector2 offSetWall2 = { -500,100 };
    initWall(wall2, offSetWall2);

    while (!WindowShouldClose())
    {
        update(bird, wall, wall2);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        drawGame(bird, wall,wall2);

        EndDrawing();
    }
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