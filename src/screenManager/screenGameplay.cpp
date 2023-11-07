#include "screenGameplay.h"

void drawGame(Bird bird, Wall wall)
{
	DrawRectangle(static_cast<int>(bird.pos.x), static_cast<int>(bird.pos.y), static_cast<int>(bird.size.x), static_cast<int>(bird.size.y), RED);
	DrawRectangle(static_cast<int>(wall.pos.x), static_cast<int>(wall.pos.y), static_cast<int>(wall.size.x), static_cast<int>(wall.size.y), wall.color);
	DrawText("Version 0.1", GetScreenWidth() - 120, GetScreenHeight() - 30, 20, BLACK);
}