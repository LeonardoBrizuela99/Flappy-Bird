#include "bird.h"
#include <iostream>

using namespace std;
static float count_Timer = 0.0f;
static float stopAnimation = 2.0f;
static int maxScore = 0;

Bird InitBird(Bird& bird)
{
	bird.pos = { static_cast<float>(GetScreenWidth() / 2 - 100),static_cast<float>(GetScreenHeight() / 2) };
	bird.size = { 40.0f,35.0f };
	bird.speed = 0.0f;
	bird.isRaising = false;
	bird.aceleration = 0.0f;
	bird.gravity = 400.f;
	bird.lives = 3;
	bird.score = 0;

	return bird;
}

Bird ResetBird(Bird& bird)
{
	bird.pos = { static_cast<float>(GetScreenWidth() / 2 - 100),static_cast<float>(GetScreenHeight() / 2) };
	bird.size = { 40.0f,35.0f };
	bird.speed = 0.0f;
	bird.isRaising = false;
	bird.aceleration = 0.0f;
	bird.gravity = 400.f;
	bird.lives = 3;
	bird.score = bird.score;
	return bird;
}

Bird RestartBird(Bird& bird)
{
	bird.pos = { static_cast<float>(GetScreenWidth() / 2 - 100),static_cast<float>(GetScreenHeight() / 2) };
	bird.size = { 45.0f,43.0f };
	bird.speed = 0.0f;
	bird.isRaising = false;
	bird.aceleration = 0.0f;
	bird.gravity = 400.f;
	return bird;
}

Bird CreateBird(Texture2D birdTextureOne, Texture2D birdTextureTwo, Sound jumpSound, Sound fall, Sound loseLife)
{
	Bird bird;
	bird.pos = { static_cast<float>(GetScreenWidth() / 2 - 100),static_cast<float>(GetScreenHeight() / 2) };
	bird.size = { 45.0f,43.0f };
	bird.speed = 0.0f;
	bird.textureOne = birdTextureOne;
	bird.textureTwo = birdTextureTwo;
	bird.soundJump = jumpSound;
	bird.soundFall =fall;
	bird.loseLifeSound =loseLife;
	bird.isRaising = false;
	bird.aceleration = 0.0f;
	bird.gravity = 400.f;
	bird.lives = 3;
	bird.score = 0;

	return bird;
}

void DrawBird(Bird& bird, bool& isPaused)
{
	if (!isPaused)
	{
		
		//DrawRectangle(static_cast<int>(bird.pos.x), static_cast<int>(bird.pos.y), static_cast<int>(bird.size.x), static_cast<int>(bird.size.y), RED);
		if (!bird.isRaising)
		{
			DrawTexture(bird.textureOne, static_cast<int>(bird.pos.x), static_cast<int>(bird.pos.y), RAYWHITE);

		}

		if (bird.isRaising)
		{
			count_Timer += GetFrameTime() * 2;
			DrawTexture(bird.textureTwo, static_cast<int>(bird.pos.x), static_cast<int>(bird.pos.y), RAYWHITE);

			if (count_Timer == stopAnimation)
			{
				count_Timer -= stopAnimation;
				bird.isRaising = false;
			}
		}
	}

}

void MoveBird(Bird& bird)
{
	if (bird.pos.y < 0)
	{
		bird.pos.y = 0;
		limitJump = true;
		bird.aceleration += bird.gravity * GetFrameTime();
		bird.speed -= bird.aceleration * GetFrameTime();
		bird.pos.y -= bird.speed * GetFrameTime();
	}
	else
	{	
		limitJump = false;
	}
	if (IsKeyPressed(KEY_UP) && limitJump == false)
	{
		PlaySound(bird.soundJump);

		bird.aceleration = 0.0f;
		bird.speed = bird.gravity / 2;
		bird.isRaising = true;

	}
	else
	{
		
		if (bird.aceleration >= bird.gravity)
		{
			if (!bird.hasPlayedFallSound)
			{
			PlaySound(bird.soundFall);
			bird.hasPlayedFallSound = true;
			}
			bird.aceleration = bird.gravity;
			bird.isRaising = false;
			
		}
		else
		{
			bird.hasPlayedFallSound = false;
			
		}
		bird.pos.y -= bird.speed * GetFrameTime();
		bird.aceleration += bird.gravity * GetFrameTime();
		bird.speed -= bird.aceleration * GetFrameTime();
	}
}

void MoveBird_2(Bird& bird)
{
	if (bird.pos.y < 0)
	{
		bird.pos.y = 0;
		limitJump = true;
		bird.aceleration += bird.gravity * GetFrameTime();
		bird.speed -= bird.aceleration * GetFrameTime();
		bird.pos.y -= bird.speed * GetFrameTime();
	}
	else
	{
		limitJump = false;
	}
	if (IsKeyPressed(KEY_SPACE) && limitJump == false)
	{
		PlaySound(bird.soundJump);

		bird.aceleration = 0.0f;
		bird.speed = bird.gravity / 2;
		bird.isRaising = true;

	}
	else
	{

		if (bird.aceleration >= bird.gravity)
		{
			if (!bird.hasPlayedFallSound)
			{
				PlaySound(bird.soundFall);
				bird.hasPlayedFallSound = true;
			}
			bird.aceleration = bird.gravity;
			bird.isRaising = false;

		}
		else
		{
			bird.hasPlayedFallSound = false;

		}
		bird.pos.y -= bird.speed * GetFrameTime();
		bird.aceleration += bird.gravity * GetFrameTime();
		bird.speed -= bird.aceleration * GetFrameTime();
	}
}

Rectangle GetBirdRect(Bird bird)
{
	return Rectangle{ bird.pos.x ,bird.pos.y , bird.size.x,bird.size.y };
}

bool BirdPipeCollision(Bird bird, Wall pipe)
{
	Rectangle birdRect = GetBirdRect(bird);
	Rectangle pipeTopRect = { pipe.topPosition.x, pipe.topPosition.y, pipe.width, pipe.topHeight };
	Rectangle pipeBotRect = { pipe.botPosition.x, pipe.botPosition.y, pipe.width, pipe.botHeight };

	
	if (CheckCollisionRecs(birdRect, pipeTopRect)) {
		return true;
	}

	
	if (CheckCollisionRecs(birdRect, pipeBotRect)) {
		return true;
	}

	return false;
}

void UpdateBird(Bird& bird, bool& isPaused, bool& isGameOver,Wall& firstPipe, Wall& secondPipe)
{
	if (isGameOver==false)
	{
		if (!isPaused)
		{
			MoveBird(bird);
					
			if (BirdPassesObstacle(bird, firstPipe) || BirdPassesObstacle(bird, secondPipe)) {
				if (!bird.passedObstacle) {  // Si el obstáculo no ha sido pasado previamente
					bird.passedObstacle = true;  // Marcar que se pasó el obstáculo
					bird.score += 100;  // Incrementar el puntaje

					cout<<bird.score<<endl;  // Incrementar el puntaje
				}
			}
			else {
				bird.passedObstacle = false;  // Resetear el marcador si no se pasa el obstáculo
			}
			if (bird.pos.y > GetScreenHeight())
			{
				if (timeSinceLastCollision>=screenExitInterval)
				{
					bird.lives--;
					cout << bird.lives << endl;
					RestartBird(bird);
					
					bird.hasloseLife = true;
					timeSinceLastScreenExit = 0.0f;
				}
				else
				{
					timeSinceLastScreenExit += GetFrameTime();
				}
				
				if (bird.hasloseLife)
				{
					PlaySound(bird.loseLifeSound);
					bird.hasloseLife = false;
				}
				
			}
			if (timeSinceLastCollision >= collisionInterval) {
				if (BirdPipeCollision(bird, firstPipe) || BirdPipeCollision(bird, secondPipe)) {
					bird.lives--;
					cout << bird.lives << endl;
					RestartBird(bird);
					timeSinceLastCollision = 0.0f; 
				}
			}

			timeSinceLastCollision += GetFrameTime(); // Incrementar el tiempo transcurrido
			if (bird.lives <= 0)
			{
		
				isGameOver = true;
				ResetWall(firstPipe, secondPipe);
				ResetBird(bird);
			}
		}
	}

	
}

void UpdateBird_2(Bird& bird, bool& isPaused, bool& isGameOver, Wall& firstPipe, Wall& secondPipe)
{

	if (isGameOver == false)
	{
		if (!isPaused)
		{
			MoveBird_2(bird);
			if (BirdPassesObstacle(bird, firstPipe) || BirdPassesObstacle(bird, secondPipe)) {
				if (!bird.passedObstacle) {  
					bird.passedObstacle = true;  
					cout << bird.score << endl;  
				}
			}
			else {
				bird.passedObstacle = false;  
			}
			if (bird.pos.y > GetScreenHeight())
			{
				if (timeSinceLastCollision >= screenExitInterval)
				{
					bird.lives--;
					cout << bird.lives << endl;
					RestartBird(bird);

					bird.hasloseLife = true;
					timeSinceLastScreenExit = 0.0f;
				}
				else
				{
					timeSinceLastScreenExit += GetFrameTime();
				}

				if (bird.hasloseLife)
				{
					PlaySound(bird.loseLifeSound);
					bird.hasloseLife = false;
				}

			}
			if (timeSinceLastCollision >= collisionInterval) {
				if (BirdPipeCollision(bird, firstPipe) || BirdPipeCollision(bird, secondPipe)) {
					bird.lives--;
					cout << bird.lives << endl;
					RestartBird(bird);
					timeSinceLastCollision = 0.0f;
				}
			}

			timeSinceLastCollision += GetFrameTime(); 
			if (bird.lives <= 0)
			{
				isGameOver = true;
				ResetWall(firstPipe, secondPipe);
				ResetBird(bird);
			}
		}
	}

}

bool BirdPassesObstacle(Bird bird, Wall& pipe) 
{
	
	if (bird.pos.x > pipe.topPosition.x + pipe.width) {
		return true; 
	}

	return false; 
}