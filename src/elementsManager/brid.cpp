#include "bird.h"

void initBird(Bird& bird)
{
	bird.pos = {static_cast<float>(GetScreenWidth() / 2 - 300), static_cast<float>(GetScreenHeight() / 2) };
	bird.size = { 70.0f, 70.0f };
	bird.speed = 150.0f;
	bird.isRaising = false;
}