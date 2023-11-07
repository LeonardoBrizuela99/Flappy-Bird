#pragma once
#include "raylib.h"

struct Wall
{
	Vector2 pos;
	Vector2 size;
	Color color;
};

void initWall(Wall& wall);