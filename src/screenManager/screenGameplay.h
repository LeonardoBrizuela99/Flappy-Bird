#pragma once
#include "raylib.h"
#include "elementsManager/bird.h"
#include "elementsManager/wall.h"
#include "utilsManager/rectangleButton.h"
#include "utilsManager/utils.h"

enum class GameScreen
{
	MENU,
	GAMEPLAY,
    MULTIPLAYER,
	RULES,
	CREDITS,
	EXIT
};

void drawGame(
    Texture2D background,
    Texture2D midground,
    Texture2D foreground,
    Texture2D tree,
    Texture2D bushTop,
    Texture2D bushDown,
    bool isPaused,
    bool isGameOver);