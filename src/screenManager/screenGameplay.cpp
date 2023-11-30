#include "screenGameplay.h"
#include<iostream>
using namespace std;

void drawGame( 
                Texture2D background, 
                Texture2D midground,
                Texture2D foreground,
                Texture2D tree,
                Texture2D bushTop,
                Texture2D bushDown,
                bool isPaused,
                bool isGameOver)
{
    static float scrollingBack = 0.0f;
    static float scrollingMid = 0.0f;
    static float scrollingFore = 0.0f;
    static float scrollingTree = 0.0f;
    static float scrollingBushTop = 0.0f;
    static float scrollingBushDown = 0.0f;
    
    
    DrawTextureEx(background, Vector2{ scrollingBack, 200 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(background, Vector2{ background.width * 2 + scrollingBack, 200 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(background, Vector2{ static_cast<float>((background.width * 3 + scrollingBack) + (GetScreenWidth() / 4.0f)) , 300 }, 0.0f, 2.0f, WHITE);

    DrawTextureEx(midground, Vector2{ scrollingMid, 150 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(midground, Vector2{ midground.width * 2 + scrollingMid, 150 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(midground, Vector2{ static_cast<float>((midground.width * 3 + scrollingMid) + (GetScreenWidth() / 4.0f)) , 150 }, 0.0f, 2.0f, WHITE);

    DrawTextureEx(foreground, Vector2{ scrollingFore, 0 }, 0.0f, 3.0f, WHITE);
    DrawTextureEx(foreground, Vector2{ static_cast<float>((foreground.width * 2 + scrollingFore)), 0 }, 0.0f, 3.0f, WHITE);
    DrawTextureEx(foreground, Vector2{ static_cast<float>((foreground.width * 3 + scrollingFore) + (GetScreenWidth() / 2.91f)) , 0 }, 0.0f, 3.0f, WHITE);

    DrawTextureEx(tree, Vector2{ scrollingTree, 0 }, 0.0f, 2.8f, WHITE);
    DrawTextureEx(tree, Vector2{ static_cast<float>((tree.width * 2 + scrollingTree)), 0 }, 0.0f, 2.8f, WHITE);
    DrawTextureEx(tree, Vector2{ static_cast<float>((tree.width * 3 + scrollingTree) + (GetScreenWidth() / 2.91f)) , 0 }, 0.0f, 2.8f, WHITE);

    DrawTextureEx(bushTop, Vector2{ scrollingBushTop, 0 }, 0.0f, 3.0f, WHITE);
    DrawTextureEx(bushTop, Vector2{ static_cast<float>((bushTop.width * 2 + scrollingBushTop)), 0 }, 0.0f, 3.0f, WHITE);
    DrawTextureEx(bushTop, Vector2{ static_cast<float>((bushTop.width * 3 + scrollingBushTop) + (GetScreenWidth() / 2.91f)) , 0 }, 0.0f, 3.0f, WHITE);

    DrawTextureEx(bushDown, Vector2{ scrollingBushDown, 0 }, 0.0f, 3.0f, WHITE);
    DrawTextureEx(bushDown, Vector2{ static_cast<float>((bushDown.width * 2 + scrollingBushDown)), 0 }, 0.0f, 3.0f, WHITE);
    DrawTextureEx(bushDown, Vector2{ static_cast<float>((bushDown.width * 3 + scrollingBushDown) + (GetScreenWidth() / 2.91f)) , 0 }, 0.0f, 3.0f, WHITE);

    if (!isGameOver && !isPaused)
    {
        scrollingBack -= 10.0f * GetFrameTime();
        scrollingMid -= 25.0f * GetFrameTime();
        scrollingFore -= 50.0f * GetFrameTime();
        scrollingTree -= 100.0f * GetFrameTime();
        scrollingBushTop -= 100.0f * GetFrameTime();
        scrollingBushDown -= 100.0f * GetFrameTime();

        if (scrollingBack <= -background.width * 2) scrollingBack = 0;
        if (scrollingMid <= -midground.width * 2) scrollingMid = 0;
        if (scrollingFore <= -foreground.width * 2) scrollingFore = 0;
        if (scrollingTree <= -tree.width * 2.5) scrollingTree =0;
        if (scrollingBushTop <= -bushTop.width * 2) scrollingBushTop = 0;
        if (scrollingBushDown <= -bushDown.width * 2) scrollingBushDown = 0;
    }

    
}

