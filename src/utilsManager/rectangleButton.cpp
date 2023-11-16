#include "rectangleButton.h"

RectangleButton initButton(RectangleButton button, Vector2 buttonSize)
{
	button.size.x = buttonSize.x;
	button.size.y = buttonSize.y;
	button.isSelected = false;

	return button;
}