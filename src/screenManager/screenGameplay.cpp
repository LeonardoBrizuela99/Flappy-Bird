#include "screenGameplay.h"

void drawGame(  Bird bird, 
                Wall wall, 
                Wall wall2, 
                float& scrollingBack, 
                float& scrollingMid, 
                float& scrollingFore, 
                Texture2D background,
                Texture2D midground,
                Texture2D foreground,
                bool isPaused,
                bool isGameOver,
                RectangleButton& continueButton,
                RectangleButton& backButton,
                Vector2 mouse)
{
    const int fontSize = 40;
    float count = 0.0f;
    float stopAnimation = 2.0f;

    DrawTextureEx(background, Vector2{ scrollingBack, 300 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(background, Vector2{ background.width * 2 + scrollingBack, 300 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(background, Vector2{ static_cast<float>((background.width * 3 + scrollingBack) + (GetScreenWidth() / 4.0f)) , 300 }, 0.0f, 2.0f, WHITE);

    DrawTextureEx(midground, Vector2{ scrollingMid, 300 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(midground, Vector2{ midground.width * 2 + scrollingMid, 300 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(midground, Vector2{ static_cast<float>((midground.width * 3 + scrollingMid) + (GetScreenWidth() / 4.0f)) , 300 }, 0.0f, 2.0f, WHITE);

    DrawTextureEx(foreground, Vector2{ scrollingFore, 390 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(foreground, Vector2{ static_cast<float>((foreground.width * 2 + scrollingFore)), 390 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(foreground, Vector2{ static_cast<float>((foreground.width * 3 + scrollingFore) + (GetScreenWidth() / 2.91f)) , 390 }, 0.0f, 2.0f, WHITE);

    if (!isGameOver && !isPaused)
    {
        scrollingBack -= 10.0f * GetFrameTime();
        scrollingMid -= 50.0f * GetFrameTime();
        scrollingFore -= 100.0f * GetFrameTime();

        if (scrollingBack <= -background.width * 2) scrollingBack = 0;
        if (scrollingMid <= -midground.width * 2) scrollingMid = 0;
        if (scrollingFore <= -foreground.width * 2) scrollingFore = 0;

        DrawRectangle(static_cast<int>(bird.pos.x), static_cast<int>(bird.pos.y), static_cast<int>(bird.size.x), static_cast<int>(bird.size.y), RED);

        if (!bird.isRaising)
        {
            DrawTexture(bird.textureOne, static_cast<int>(bird.pos.x), static_cast<int>(bird.pos.y), RAYWHITE);
            /*DrawTexturePro(bird.textureOne,
                { 0.0f, 0.0f, static_cast<float>(bird.textureOne.width), static_cast<float>(bird.textureOne.height) },
                { static_cast<float>(bird.pos.x), static_cast<float>(bird.pos.y), static_cast<float>(bird.size.x), static_cast<float>(bird.size.y) },
                { static_cast<float>(bird.size.x / 2), static_cast<float>(bird.size.y / 2) },
                0.0f,
                RAYWHITE);*/
        }

        if (bird.isRaising)
        {
            count += GetFrameTime();
            DrawTexture(bird.textureTwo, static_cast<int>(bird.pos.x), static_cast<int>(bird.pos.y), RAYWHITE);
            /*DrawTexturePro(bird.textureTwo,
                { 0.0f, 0.0f, static_cast<float>(bird.textureTwo.width), static_cast<float>(bird.textureTwo.height) },
                { static_cast<float>(bird.pos.x), static_cast<float>(bird.pos.y), static_cast<float>(bird.size.x), static_cast<float>(bird.size.y) },
                { static_cast<float>(bird.size.x), static_cast<float>(bird.size.y) },
                0.0f,
                RAYWHITE);*/
            if (count >= stopAnimation)
            {
                count -= stopAnimation;
                bird.isRaising = false;
            }
        }
        DrawRectangle(static_cast<int>(wall.pos.x), static_cast<int>(wall.pos.y), static_cast<int>(wall.size.x), static_cast<int>(wall.size.y), wall.color);
        DrawRectangle(static_cast<int>(wall2.pos.x), static_cast<int>(wall2.pos.y), static_cast<int>(wall2.size.x), static_cast<int>(wall2.size.y), wall2.color);

    }

    
    
    if (isPaused)
    {
        DrawRectangle((GetScreenWidth() / 2) - 300, GetScreenHeight() / 2 - 200, 600, 400, BLACK);

        DrawText("PAUSED", (GetScreenWidth() / 2) - 120, (GetScreenHeight() / 2) - 140, 60, WHITE);

        backButton.pos.x = static_cast<float>((GetScreenWidth() / 2) - 270);
        backButton.pos.y = static_cast<float>((GetScreenHeight() / 2) + 80);

        DrawRectangle(static_cast<int>(backButton.pos.x), static_cast<int>(backButton.pos.y), static_cast<int>(backButton.size.x), static_cast<int>(backButton.size.y), WHITE);

        DrawText(   "BACK",
                    static_cast<int>(backButton.pos.x + 20),
                    static_cast<int>(backButton.pos.y + 5),
                    fontSize,
                    RED);

        if (optionsCollision(mouse, backButton))
        {
            backButton.isSelected = true;
            DrawRectangle(static_cast<int>(backButton.pos.x),
                static_cast<int>(backButton.pos.y),
                static_cast<int>(backButton.size.x),
                static_cast<int>(backButton.size.y),
                GRAY);

            DrawText("BACK",
                static_cast<int>(backButton.pos.x + 20),
                static_cast<int>(backButton.pos.y + 5),
                fontSize,
                RED);
        }
        else if (!optionsCollision(mouse, backButton))
        {
            backButton.isSelected = false;
        }

        continueButton.pos.x = static_cast<float>((GetScreenWidth() / 2) + 50);
        continueButton.pos.y = static_cast<float>((GetScreenHeight() / 2) + 80);

        DrawRectangle(  static_cast<int>(continueButton.pos.x),
                        static_cast<int>(continueButton.pos.y),
                        static_cast<int>(continueButton.size.x),
                        static_cast<int>(continueButton.size.y),
                        WHITE);

        DrawText(   "CONTINUE",
                    static_cast<int>(continueButton.pos.x + 5),
                    static_cast<int>(continueButton.pos.y + 5),
                    fontSize,
                    RED);

        if (optionsCollision(mouse, continueButton))
        {
            continueButton.isSelected = true;
            DrawRectangle(static_cast<int>(continueButton.pos.x),
                static_cast<int>(continueButton.pos.y),
                static_cast<int>(continueButton.size.x),
                static_cast<int>(continueButton.size.y),
                GRAY);

            DrawText("CONTINUE",
                static_cast<int>(continueButton.pos.x + 5),
                static_cast<int>(continueButton.pos.y + 5),
                fontSize,
                RED);
        }
        else if (!optionsCollision(mouse, continueButton))
        {
            continueButton.isSelected = false;
        }
    }
}