#pragma once
#include "raylib.h"

struct Bird
{
	Vector2 pos;
	Vector2 size;
	float speed;
};

void initBird(Bird& bird);