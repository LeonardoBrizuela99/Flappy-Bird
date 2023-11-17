#include "bird.h"

void initBird(Bird& bird)
{
	bird.pos = {static_cast<float>(GetScreenWidth() / 2 - 300), static_cast<float>(GetScreenHeight() / 2) };
	bird.size = { static_cast<float>(bird.textureOne.width), static_cast<float>(bird.textureOne.height) };
	bird.speed = 150.0f;
	bird.isRaising = false;
}