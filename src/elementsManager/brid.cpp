#include "bird.h"

void initBird(Bird& bird)
{
	bird.pos = {static_cast<float>(GetScreenWidth() / 2 - 300), static_cast<float>(GetScreenHeight() / 2) };
	bird.size = { 46.0f, 32.0f };
	bird.speed = 150.0f;
	bird.isRaising = false;
}