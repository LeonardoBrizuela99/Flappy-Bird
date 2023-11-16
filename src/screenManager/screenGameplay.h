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
	RULES,
	CREDITS,
	EXIT
};

void drawGame(  Bird bird,
                Wall wall,
                Wall wall2,
                float scrollingBack,
                float scrollingMid,
                float scrollingFore,
                Texture2D background,
                Texture2D midground,
                Texture2D foreground,
                bool isPaused,
                RectangleButton& continueButton,
                RectangleButton& backButton,
                Vector2 mouse);