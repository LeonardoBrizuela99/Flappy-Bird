#pragma once
#include "raylib.h"

struct RectangleButton
{
	Vector2 pos;
	Vector2 size;
	bool isSelected;
};

RectangleButton initButton(RectangleButton button, Vector2 buttonSize);
