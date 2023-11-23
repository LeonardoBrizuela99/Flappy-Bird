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
              /*  float& scrollingBack,
                float& scrollingMid,
                float& scrollingFore,
                float& scrollingTree,
                float& scrollingBushTop,
                float& scrollingBushDown,
                Texture2D background,
                Texture2D midground,
                Texture2D foreground,
                Texture2D tree,
                Texture2D bushTop,
                Texture2D bushDown,*/
                bool isPaused,
                //bool isGameOver,
                RectangleButton& continueButton,
                RectangleButton& backButton,
                RectangleButton& restartButton,
                Vector2 mouse);