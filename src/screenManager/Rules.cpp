#include "Rules.h"
#include"utilsManager/rectangleButton.h"

//static Vector2 mouse;
//static RectangleButton backButton = {};
//RectangleButton rulesButton = {};
//Vector2 buttonSize = { 220, 50 };

//void init()
//{
//    mouse = { static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()) };
//}

void drawRules(RectangleButton& backButton, Vector2 mouse)
{
    
    
        ClearBackground(BLACK);

        const int fontSize = 40;

        DrawRectangle((GetScreenWidth() / 2) - 300, GetScreenHeight() / 2 - 200, 600, 400, BLACK);

        DrawText("RULES", (GetScreenWidth() / 2) - 120, (GetScreenHeight() / 2) - 140, 60, WHITE);

       // DrawText("Ezequiel Prieto", (GetScreenWidth() / 2) - 200, (GetScreenHeight() / 2) - 20, fontSize, WHITE);

        //DrawText("Fiorella Gaston", (GetScreenWidth() / 2) - 200, (GetScreenHeight() / 2) + 20, fontSize, WHITE);

        backButton.pos.x = static_cast<float>((GetScreenWidth() / 2) - 270);
        backButton.pos.y = static_cast<float>((GetScreenHeight() / 2) + 80);

        DrawRectangle(static_cast<int>(backButton.pos.x), static_cast<int>(backButton.pos.y), static_cast<int>(backButton.size.x), static_cast<int>(backButton.size.y), WHITE);

        DrawText("BACK",
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

        
    
}

