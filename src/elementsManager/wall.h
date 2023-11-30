#pragma once
#include "raylib.h"

	struct Wall
	{
		Vector2 topPosition = { 0, 0 };
		Vector2 botPosition = { 0, 0 };

		float separation = 160.0f;

		float speed = 0.0f;
		float topHeight = 0.0f;
		float botHeight = 0.0f;
		float width = 0.0f;
	};

	Wall InitWall(float xPos);
	void UpdateWall(Wall& wall,bool& isPaused,bool& isGameOver);
	void DrawWall(Wall wall);
	void ResetWall(Wall& firstWall, Wall& secondWall); 
