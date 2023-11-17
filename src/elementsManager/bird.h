#pragma once
#include "raylib.h"

struct Bird
{
	Vector2 pos;
	Vector2 size;
	float speed;
	Texture2D textureOne;
	Texture2D textureTwo;
	bool isRaising;
};

void initBird(Bird& bird);