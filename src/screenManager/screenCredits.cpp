#include "screenCredits.h"

void drawCredits(RectangleButton& backButton,
    Vector2 mouse)
{
    ClearBackground(BLACK);

    const int fontSize = 20;

    DrawRectangle((GetScreenWidth() / 2) - 300, GetScreenHeight() / 2 - 200, 600, 400, BLACK);


  
    const int creditsHeight = 80;

    
    int creditsTextWidth = MeasureText("CREDITS", 60);

   
    DrawText("CREDITS", (GetScreenWidth() - creditsTextWidth) / 2, 20, 60, WHITE);

    
    int nameLeftOffset = 40; 
    DrawText("code: Ezequiel Prieto / Leonardo Brizuela", nameLeftOffset, creditsHeight, fontSize, WHITE);
    DrawText("Parallax: https://gowldev.itch.io/gardens-forest ", nameLeftOffset, creditsHeight + 60, fontSize, WHITE);
    DrawText("Bird: Leonardo Brizuela ", nameLeftOffset, creditsHeight + 140, fontSize, WHITE);
    DrawText("sounds: https://freesound.org/people/oganesson/sounds/555015/", nameLeftOffset, creditsHeight + 220, fontSize, WHITE);
    DrawText("sounds:https://freesound.org/people/Lefty_Studios/sounds/369515/", nameLeftOffset, creditsHeight + 240, fontSize, WHITE);
    DrawText("sounds:https://freesound.org/people/MATRIXXX_/sounds/506546/", nameLeftOffset, creditsHeight + 280, fontSize, WHITE);
    DrawText("sounds:https://freesound.org/people/MATRIXXX_/sounds/415991/", nameLeftOffset, creditsHeight + 320, fontSize, WHITE);
    DrawText("sounds:https://freesound.org/people/cabled_mess/sounds/350981/", nameLeftOffset, creditsHeight + 360, fontSize, WHITE);
    DrawText("menuMusic:https://freesound.org/people/ShadyDave/sounds/262259/", nameLeftOffset, creditsHeight + 480, fontSize, WHITE);
    DrawText("GamplayMusic: https://freesound.org/people/ZHR%C3%98/sounds/614096/", nameLeftOffset, creditsHeight + 540, fontSize, WHITE);

    backButton.pos.x = 0;
    backButton.pos.y = static_cast<float>(GetScreenHeight() - backButton.size.y); 

    DrawRectangle(static_cast<int>(backButton.pos.x), static_cast<int>(backButton.pos.y), static_cast<int>(backButton.size.x), static_cast<int>(backButton.size.y), WHITE);

    DrawText("BACK",
        static_cast<int>(backButton.pos.x + 20),
        static_cast<int>(backButton.pos.y + 5),
        40,
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