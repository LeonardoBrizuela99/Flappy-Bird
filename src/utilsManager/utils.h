#pragma once
#include "raylib.h"
#include "rectangleButton.h"
#include "elementsManager/bird.h"
#include "elementsManager/wall.h"

bool optionsCollision(Vector2 mouse, RectangleButton button);
bool birdWallCollision(Bird bird, Wall wall);
bool screenWallCollision(Wall& wall);
bool screenBirdCollision(Bird& bird);
void resetGame(Bird& bird, Wall& wall, Wall& wall2, bool& isPaused, bool& isGameOver);
void restartGame(Bird& bird, Wall& wall, Wall& wall2, bool& isPaused);