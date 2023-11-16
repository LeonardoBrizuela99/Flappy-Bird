#pragma once
#include "raylib.h"

struct Bird
{
	Vector2 pos;
	Vector2 size;
	float speed;
	Texture2D texture;
	bool isRaising;
};

void initBird(Bird& bird);