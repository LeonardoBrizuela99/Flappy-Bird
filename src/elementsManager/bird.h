#pragma once
#include "raylib.h"

struct Bird
{
	Vector2 pos;
	Vector2 size;
};

void initBird(Bird& bird);