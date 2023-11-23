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
	Color color;
	short int lives;
	float aceleration;
	float gravity;

};

void initBird(Bird& bird);