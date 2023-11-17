#include "wall.h"

void initWall(Wall& wall)
{
	wall.pos = { static_cast<float>(GetScreenWidth() - 100, GetScreenHeight() - 100) };
	wall.size = { 150.0f, 400.0f };
	wall.color = BROWN;
	wall.minHeight = 150;
	wall.maxHeight = 500;
	wall.speed = 150.0f;
}
void initWall(Wall& wall,Vector2 posOffset)
{
	wall.pos = { static_cast<float>(posOffset.x),  static_cast<float>(GetScreenHeight() - posOffset.y)};
	wall.size = { 150.0f, 400.0f };
	wall.color = BROWN;
	wall.minHeight = 150;
	wall.maxHeight = 500;
	wall.speed = 150.0f;
}