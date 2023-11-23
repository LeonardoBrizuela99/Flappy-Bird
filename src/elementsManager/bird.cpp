#include "bird.h"

void initBird(Bird& bird)
{
	bird.pos = {static_cast<float>(GetScreenWidth() / 2 - 300), static_cast<float>(GetScreenHeight() / 2) };
	bird.size = { 45.0f, 43.0f };
	bird.speed = 550.0f;
	bird.aceleration = 0.0f;
	bird.gravity = 400.0f;
	bird.isRaising = false;
	bird.lives = 3;
}