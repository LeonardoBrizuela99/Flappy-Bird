#include "utils.h"

bool optionsCollision(Vector2 mouse, RectangleButton button)
{
	return	mouse.x > button.pos.x
		&& mouse.x < button.pos.x + button.size.x
		&& mouse.y > button.pos.y
		&& mouse.y < button.pos.y + button.size.y;
}

bool birdWallCollision(Bird bird, Wall wall)
{
	return	bird.pos.x + bird.size.x > wall.pos.x
		&& bird.pos.x < wall.pos.x + wall.size.x
		&& bird.pos.y > wall.pos.y
		&& bird.pos.y < wall.pos.y + wall.size.y;
}

bool screenWallCollision(Wall& wall)
{
	return wall.pos.x + wall.size.x <= 0;
}

bool screenBirdCollision(Bird& bird)
{
	return bird.pos.y <= 0 && bird.pos.y >= GetScreenHeight();
}

void resetGame(Bird& bird, Wall& wall, Wall& wall2, bool& isPaused)
{
	initBird(bird);
	initWall(wall);
	initWall(wall2);
	isPaused = false;
}