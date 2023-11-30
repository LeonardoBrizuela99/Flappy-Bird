#include "Wall.h"


	static int minHeight = 80;
	static int maxHeight = 400;
	static float screenOffset = 100.0f;

	Wall InitWall(float xPos)
	{
		Wall wall;

		wall.speed = 300.0f;

		wall.width = 90.0f;
		wall.topHeight = static_cast<float>(GetRandomValue(minHeight, maxHeight));

		wall.topPosition.x = xPos;
		wall.topPosition.y = 0.0f;

		wall.botHeight = GetScreenHeight() - wall.topHeight - wall.separation;

		wall.botPosition.x = wall.topPosition.x;
		wall.botPosition.y = static_cast<float>(GetScreenHeight() - wall.botHeight);

		return wall;
	}

	void UpdateWall(Wall& wall, bool& isPaused, bool& isGameOver)
	{
		if (isGameOver==false)
		{
			if (!isPaused)
			{
				wall.topPosition.x -= wall.speed * GetFrameTime();
				wall.botPosition.x = wall.topPosition.x;

				if (wall.topPosition.x + wall.width < 0)
				{
					wall.topHeight = static_cast<float>(GetRandomValue(minHeight, maxHeight));
					wall.topPosition.x = static_cast<float>(GetScreenWidth());

					wall.botHeight = GetScreenHeight() - wall.topHeight - wall.separation;
					wall.botPosition.y = static_cast<float>(GetScreenHeight() - wall.botHeight);
				}
			}
		}
		
		
	}

	void DrawWall(Wall wall)
	{
		DrawRectangle(static_cast<int>(wall.topPosition.x), static_cast<int>(wall.topPosition.y), static_cast<int>(wall.width), static_cast<int>(wall.topHeight), BROWN);
		DrawRectangle(static_cast<int>(wall.botPosition.x), static_cast<int>(wall.botPosition.y), static_cast<int>(wall.width), static_cast<int>(wall.botHeight), BROWN);
	}

	void ResetWall(Wall& firstWall, Wall& secondWall)
	{
		float wallDistance = static_cast<float>(GetScreenWidth()) / 1.5f;
		float wallWidth = 90.0f;
		float firstWallX = static_cast<float>(GetScreenWidth());
		float secondWallX = static_cast<float>(GetScreenWidth()) + wallDistance + wallWidth / 2;

		firstWall = InitWall(firstWallX);
		secondWall = InitWall(secondWallX);
	}
