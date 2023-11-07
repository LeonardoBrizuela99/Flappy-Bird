#include "wall.h"

void initWall(Wall& wall)
{
	wall.pos = { static_cast<float>(GetScreenWidth() - 200, GetScreenHeight() - 100) };
	wall.size = { 150.0f, 400.0f };
	wall.color = BROWN;
}