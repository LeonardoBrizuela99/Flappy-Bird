#pragma once
#include "raylib.h"

struct Wall
{
	Vector2 pos;
	Vector2 size;
	Color color;
	int minHeight;
	int maxHeight;
	float speed;
	bool hit;
};

void initWall(Wall& wall);

void initWall(Wall& wall, Vector2 posOffset);
