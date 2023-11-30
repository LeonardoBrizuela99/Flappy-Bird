#include "utils.h"

bool optionsCollision(Vector2 mouse, RectangleButton button)
{
	return	mouse.x > button.pos.x
		&& mouse.x < button.pos.x + button.size.x
		&& mouse.y > button.pos.y
		&& mouse.y < button.pos.y + button.size.y;
}