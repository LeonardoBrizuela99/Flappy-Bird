#pragma once
#include "raylib.h"
#include"wall.h"


struct Bird
{
	Vector2 pos;
	Vector2 size;
	float speed;
	Texture2D textureOne;
	Texture2D textureTwo;
	Sound soundJump;
	Sound soundFall;
	Sound loseLifeSound;
	bool isRaising;
	Color color;
	short int lives;
	float aceleration;
	float gravity;
	float score;
	bool hasPlayedFallSound;
	bool hasloseLife;
	bool passedObstacle;

};

static float timeSinceLastCollision = 0.0f;
static float collisionTimer = 0.0f;
static float collisionInterval = 1.0f;
static float screenExitInterval = 1.0f;
static float timeSinceLastScreenExit = 0.0f;
static bool limitJump = false;


Bird InitBird(Bird& bird);
Bird RestartBird(Bird& bird);
Bird CreateBird(Texture2D birdTextureOne, Texture2D birdTextureTwo, Sound jumpSound, Sound fall, Sound loseLife);
void DrawBird(Bird& bird, bool& isPaused);
void UpdateBird(Bird& bird, bool& isPaused, bool& isGameOver, Wall& firstPipe, Wall& secondPipe);
void UpdateBird_2(Bird& bird, bool& isPaused, bool& isGameOver, Wall& firstPipe, Wall& secondPipe);
void MoveBird(Bird& bird);
void MoveBird_2(Bird& bird);

Rectangle GetBirdRect(Bird bird);
bool BirdPipeCollision(Bird bird, Wall pipe);
bool BirdPassesObstacle(Bird bird, Wall& pipe);

