#include "game.h"
#include "raylib.h"
#include "utilsManager/utils.h"
#include "screenManager/screenGameplay.h"
#include "screenManager/screenMenu.h"
#include "screenManager/screenCredits.h"
#include "elementsManager/bird.h"
#include "elementsManager/wall.h"
#include"screenManager/Rules.h"
#include<iostream>
#include"elementsManager/bird.h"
using namespace std;


namespace game
{

	void InitTextures(GameTextures& gameTextures);
	void InitSounds(SoundsGame& soundsGame);
	void InitButtons(GameRectangleButton& gameButtons);
	void GameScreenMenu(GameRectangleButton& gameButtons, GameScreen& currentScreen, Vector2& mouse);
	void GameScreenMultiplayer(SoundsGame& soundsGame, Bird& bird, Bird& bird2, Wall& firstPipe, Wall& secondPipe, bool& isPaused, bool& isGameOver, GameRectangleButton& gameButtons, GameTextures& gameTextures, GameScreen& currentScreen, Vector2 mouse);
	void GameScreenSingleplayer(SoundsGame& soundsGame, Bird& bird, Wall& firstWall, Wall& secondWall, bool& isPaused, bool& isGameOver, GameRectangleButton& gameButtons, GameTextures& gameTextures, GameScreen& currentScreen, Vector2 mouse);
	void GameScreenCredits(GameRectangleButton& gameButtons, GameScreen& currentScreen, Vector2& mouse);
	void GameScreenRules(GameRectangleButton& gameButtons, GameScreen& currentScreen, Vector2& mouse);
	void DeInitTextures(GameTextures& gameTextures);
	void DeInitSounds(SoundsGame& soundsGame);
	void PauseScreen(GameRectangleButton& gameButtons, Vector2& mouse, bool& isPaused);
	void GameOverScreen(GameRectangleButton& gameButtons, Vector2& mouse, bool& isGameOver,Bird& bird);
	
    
	static int fontSize = 40;


	 bool isGameRunning = true;
	
	void runGame()
	{
       
		const int screenWidth = 1024;
		const int screenHeight = 768;

		bool isPaused = false;
		bool musicPaused = false;
	    bool isGameOver = false;
		InitWindow(screenWidth, screenHeight, "Flappy Bird");
		InitAudioDevice();
		Music music = LoadMusicStream("res/sounds/snowfall-final.mp3");
		Music musicGameplay = LoadMusicStream("res/sounds/music.mp3");
		PlayMusicStream(music);
		PlayMusicStream(musicGameplay);
		SoundsGame soundsGame;
		InitSounds(soundsGame);
		GameTextures gameTextures;
		InitTextures(gameTextures);
		GameRectangleButton gameButtons;
		InitButtons(gameButtons);
		Bird bird, bird2;
		bird = CreateBird(gameTextures.texBirdOne, gameTextures.texBirdTwo,soundsGame.jumpSound, soundsGame.fallSound, soundsGame.loseLife);
		bird2 = CreateBird(gameTextures.texBirdOne, gameTextures.texBirdTwo,soundsGame.jumpSound, soundsGame.fallSound, soundsGame.loseLife);
		
		 Wall firstWall;
		 Wall secondWall;
		 float wallDistance = static_cast<float>(GetScreenWidth()) / 1.5f;
		 float wallWidth = 90.0f;
		 float firstWallX = static_cast<float>(GetScreenWidth());
		 float secondWallX = static_cast<float>(GetScreenWidth()) + wallDistance + wallWidth / 2;

		
		 firstWall = InitWall(firstWallX);
		 secondWall = InitWall(secondWallX);
		

		GameScreen currentScreen = GameScreen::MENU;

		while (!WindowShouldClose() && isGameRunning)
		{
			SetExitKey(NULL);

				
			BeginDrawing();
			ClearBackground(BLACK);
			Vector2 mouse = { static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()) };
			switch (currentScreen)
			{
			case GameScreen::MENU:
				
				UpdateMusicStream(music);
				GameScreenMenu(gameButtons, currentScreen, mouse);
				break;
			case GameScreen::MULTIPLAYER:

				UpdateMusicStream(musicGameplay);
				GameScreenMultiplayer(soundsGame, bird,bird2, firstWall, secondWall, isPaused,isGameOver, gameButtons, gameTextures, currentScreen, mouse);
				
				break;
			case GameScreen::GAMEPLAY:
				UpdateMusicStream(musicGameplay);
				GameScreenSingleplayer(soundsGame,bird, firstWall,secondWall, isPaused,isGameOver,gameButtons,gameTextures, currentScreen, mouse);
				break;
			case GameScreen::RULES:
				UpdateMusicStream(music);
				GameScreenRules(gameButtons,currentScreen,mouse);
				break;
			case GameScreen::CREDITS:
				UpdateMusicStream(music);
				GameScreenCredits(gameButtons, currentScreen, mouse);
				break;
			case GameScreen::EXIT:
				isGameRunning = false;
				break;
			default:
				break;
			}
			EndDrawing();
		}
		
		UnloadMusicStream(music);
		UnloadMusicStream(musicGameplay);
		DeInitSounds(soundsGame);
		CloseAudioDevice();
		DeInitTextures(gameTextures);
		CloseWindow();
	}
	void InitTextures(GameTextures& gameTextures)
	{
		gameTextures.foreground = LoadTexture("res/textures/background1.png");
		gameTextures.midground = LoadTexture("res/textures/background2.png");
		gameTextures.background = LoadTexture("res/textures/background4.png");
		gameTextures.tree = LoadTexture("res/textures/trees.png");
		gameTextures.bushTop = LoadTexture("res/textures/frontleaves.png");
		gameTextures.bushDown = LoadTexture("res/textures/pushes.png");
		gameTextures.texBirdOne = LoadTexture("res/textures/Bird2.png");
		gameTextures.texBirdTwo = LoadTexture("res/textures/Bird1.png");
	}
	void InitSounds(SoundsGame& soundsGame)
	{
		soundsGame.jumpSound=LoadSound("res/sounds/jumping.wav");
		soundsGame.fallSound=LoadSound("res/sounds/fall.wav");
		soundsGame.loseLife=LoadSound("res/sounds/loseLife.wav");
		soundsGame.lose=LoadSound("res/sounds/lose.wav");
		soundsGame.pause=LoadSound("res/sounds/pop.wav");

	}
	void DeInitTextures(GameTextures& gameTextures)
	{
		UnloadTexture(gameTextures.background);
		UnloadTexture(gameTextures.midground);
		UnloadTexture(gameTextures.foreground);
		UnloadTexture(gameTextures.tree);
		UnloadTexture(gameTextures.bushTop);
		UnloadTexture(gameTextures.bushDown);
		UnloadTexture(gameTextures.texBirdOne);
		UnloadTexture(gameTextures.texBirdTwo);
	}
	void DeInitSounds(SoundsGame& soundsGame)
	{
		UnloadSound(soundsGame.jumpSound);
		UnloadSound(soundsGame.fallSound);
		UnloadSound(soundsGame.loseLife);
		UnloadSound(soundsGame.lose);
		UnloadSound(soundsGame.pause);
	}
	void PauseScreen(GameRectangleButton& gameButtons, Vector2& mouse,bool& isPaused)
	{
		if (isPaused)
		{
			DrawRectangle((GetScreenWidth() / 2) - 300, GetScreenHeight() / 2 - 200, 600, 500, BLACK);

			DrawText("PAUSED", (GetScreenWidth() / 2) - 120, (GetScreenHeight() / 2) - 140, 60, WHITE);

			gameButtons.backButton.pos.x = static_cast<float>((GetScreenWidth() / 2) - 270);
			gameButtons.backButton.pos.y = static_cast<float>((GetScreenHeight() / 2) + 80);

			DrawRectangle(static_cast<int>(gameButtons.backButton.pos.x), static_cast<int>(gameButtons.backButton.pos.y), static_cast<int>(gameButtons.backButton.size.x), static_cast<int>(gameButtons.backButton.size.y), WHITE);

			DrawText("BACK",
				static_cast<int>(gameButtons.backButton.pos.x + 20),
				static_cast<int>(gameButtons.backButton.pos.y + 5),
				fontSize,
				RED);

			if (optionsCollision(mouse, gameButtons.backButton))
			{
				gameButtons.backButton.isSelected = true;
				DrawRectangle(static_cast<int>(gameButtons.backButton.pos.x),
					static_cast<int>(gameButtons.backButton.pos.y),
					static_cast<int>(gameButtons.backButton.size.x),
					static_cast<int>(gameButtons.backButton.size.y),
					GRAY);

				DrawText("BACK",
					static_cast<int>(gameButtons.backButton.pos.x + 20),
					static_cast<int>(gameButtons.backButton.pos.y + 5),
					fontSize,
					RED);
			}
			else if (!optionsCollision(mouse, gameButtons.backButton))
			{
				gameButtons.backButton.isSelected = false;
			}

			gameButtons.continueButton.pos.x = static_cast<float>((GetScreenWidth() / 2) + 50);
			gameButtons.continueButton.pos.y = static_cast<float>((GetScreenHeight() / 2) + 80);

			DrawRectangle(static_cast<int>(gameButtons.continueButton.pos.x),
				static_cast<int>(gameButtons.continueButton.pos.y),
				static_cast<int>(gameButtons.continueButton.size.x),
				static_cast<int>(gameButtons.continueButton.size.y),
				WHITE);

			DrawText("CONTINUE",
				static_cast<int>(gameButtons.continueButton.pos.x + 5),
				static_cast<int>(gameButtons.continueButton.pos.y + 5),
				fontSize,
				RED);

			if (optionsCollision(mouse, gameButtons.continueButton))
			{
				gameButtons.continueButton.isSelected = true;
				DrawRectangle(static_cast<int>(gameButtons.continueButton.pos.x),
					static_cast<int>(gameButtons.continueButton.pos.y),
					static_cast<int>(gameButtons.continueButton.size.x),
					static_cast<int>(gameButtons.continueButton.size.y),
					GRAY);

				DrawText("CONTINUE",
					static_cast<int>(gameButtons.continueButton.pos.x + 5),
					static_cast<int>(gameButtons.continueButton.pos.y + 5),
					fontSize,
					RED);
			}
			else if (!optionsCollision(mouse, gameButtons.continueButton))
			{
				gameButtons.continueButton.isSelected = false;
			}

			gameButtons.restartButton.pos.x = static_cast<float>((GetScreenWidth() / 2) - 100);
			gameButtons.restartButton.pos.y = static_cast<float>((GetScreenHeight() / 2) + 200);

			DrawRectangle(static_cast<int>(gameButtons.restartButton.pos.x),
				static_cast<int>(gameButtons.restartButton.pos.y),
				static_cast<int>(gameButtons.restartButton.size.x),
				static_cast<int>(gameButtons.restartButton.size.y),
				WHITE);

			DrawText("RESTART",
				static_cast<int>(gameButtons.restartButton.pos.x + 10),
				static_cast<int>(gameButtons.restartButton.pos.y + 10),
				fontSize,
				RED);

			if (optionsCollision(mouse, gameButtons.restartButton))
			{
				gameButtons.restartButton.isSelected = true;
				DrawRectangle(static_cast<int>(gameButtons.restartButton.pos.x),
					static_cast<int>(gameButtons.restartButton.pos.y),
					static_cast<int>(gameButtons.restartButton.size.x),
					static_cast<int>(gameButtons.restartButton.size.y),
					GRAY);

				DrawText("RESTART",
					static_cast<int>(gameButtons.restartButton.pos.x + 10),
					static_cast<int>(gameButtons.restartButton.pos.y + 10),
					fontSize,
					RED);
			}
			else if (!optionsCollision(mouse, gameButtons.restartButton))
			{
				gameButtons.restartButton.isSelected = false;
			}
		}
	}
	void GameOverScreen(GameRectangleButton& gameButtons, Vector2& mouse, bool& isGameOver, Bird& bird)
	{
		if (isGameOver)
		{
			int score = bird.score;
			int playerScore =score;
		
			DrawRectangle((GetScreenWidth() / 2) - 300, GetScreenHeight() / 2 - 200, 600, 500, BLACK);
			DrawText(TextFormat(" Score: %02i", playerScore), (GetScreenWidth() / 2-100) , (GetScreenHeight() / 2) + 200, 40, WHITE);

			DrawText("GAME OVER", (GetScreenWidth() / 2) - 200, (GetScreenHeight() / 2) - 140, 60, WHITE);

			gameButtons.backButton.pos.x = static_cast<float>((GetScreenWidth() / 2) - 270);
			gameButtons.backButton.pos.y = static_cast<float>((GetScreenHeight() / 2) + 80);

			DrawRectangle(static_cast<int>(gameButtons.backButton.pos.x), static_cast<int>(gameButtons.backButton.pos.y), static_cast<int>(gameButtons.backButton.size.x), static_cast<int>(gameButtons.backButton.size.y), WHITE);
	
			DrawText("BACK",
				static_cast<int>(gameButtons.backButton.pos.x + 20),
				static_cast<int>(gameButtons.backButton.pos.y + 5),
				fontSize,
				RED);

			if (optionsCollision(mouse, gameButtons.backButton))
			{
				gameButtons.backButton.isSelected = true;
				DrawRectangle(static_cast<int>(gameButtons.backButton.pos.x),
					static_cast<int>(gameButtons.backButton.pos.y),
					static_cast<int>(gameButtons.backButton.size.x),
					static_cast<int>(gameButtons.backButton.size.y),
					GRAY);

				DrawText("BACK",
					static_cast<int>(gameButtons.backButton.pos.x + 20),
					static_cast<int>(gameButtons.backButton.pos.y + 5),
					fontSize,
					RED);
			}
			else if (!optionsCollision(mouse, gameButtons.backButton))
			{
				gameButtons.backButton.isSelected = false;
			}
			gameButtons.restartButton.pos.x = static_cast<float>((GetScreenWidth() / 2) + 50);
			gameButtons.restartButton.pos.y = static_cast<float>((GetScreenHeight() / 2) + 80);
			
			DrawRectangle(static_cast<int>(gameButtons.restartButton.pos.x),
				static_cast<int>(gameButtons.restartButton.pos.y),
				static_cast<int>(gameButtons.restartButton.size.x),
				static_cast<int>(gameButtons.restartButton.size.y),
				WHITE);

			DrawText("RESTART",
				static_cast<int>(gameButtons.restartButton.pos.x + 5),
				static_cast<int>(gameButtons.restartButton.pos.y + 5),
				fontSize,
				RED);

			if (optionsCollision(mouse, gameButtons.restartButton))
			{
				gameButtons.restartButton.isSelected = true;
				DrawRectangle(static_cast<int>(gameButtons.restartButton.pos.x),
					static_cast<int>(gameButtons.restartButton.pos.y),
					static_cast<int>(gameButtons.restartButton.size.x),
					static_cast<int>(gameButtons.restartButton.size.y),
					GRAY);

				DrawText("RESTART",
					static_cast<int>(gameButtons.restartButton.pos.x + 5),
					static_cast<int>(gameButtons.restartButton.pos.y + 5),
					fontSize,
					RED);
			}
			else if (!optionsCollision(mouse, gameButtons.restartButton))
			{
				gameButtons.restartButton.isSelected = false;
			}
			
		}


	}
	
	void InitButtons(GameRectangleButton& gameButtons)
	{
		Vector2 buttonSize = { 220, 50 };

		gameButtons.playButton = {};
		gameButtons.multiplayerButton = {};
		gameButtons.backButton = {};
		gameButtons.rulesButton = {};
		gameButtons.creditsButton = {};
		gameButtons.exitButton = {};
		gameButtons.continueButton = {};
		gameButtons.restartButton = {};

		gameButtons.playButton = initButton(gameButtons.playButton, buttonSize);
		gameButtons.multiplayerButton = initButton(gameButtons.multiplayerButton, buttonSize);
		gameButtons.rulesButton = initButton(gameButtons.rulesButton, buttonSize);
		gameButtons.restartButton = initButton(gameButtons.restartButton, buttonSize);
		gameButtons.creditsButton = initButton(gameButtons.creditsButton, buttonSize);
		gameButtons.exitButton = initButton(gameButtons.exitButton, buttonSize);
		gameButtons.continueButton = initButton(gameButtons.continueButton, buttonSize);
		gameButtons.backButton = initButton(gameButtons.backButton, buttonSize);
	

	}
	void GameScreenMenu(GameRectangleButton& gameButtons, GameScreen& currentScreen, Vector2& mouse)
	{
		
		drawMenu(gameButtons.playButton, gameButtons.multiplayerButton, gameButtons.rulesButton, gameButtons.creditsButton, gameButtons.exitButton, mouse);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.multiplayerButton.isSelected == true)
		{
			currentScreen = GameScreen::MULTIPLAYER;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.playButton.isSelected == true)
		{
			currentScreen = GameScreen::GAMEPLAY;
			
		}
		else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.rulesButton.isSelected == true)
		{
			currentScreen = GameScreen::RULES;
		}
		else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.creditsButton.isSelected == true)
		{
			currentScreen = GameScreen::CREDITS;
		}
		else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.exitButton.isSelected == true)
		{
			currentScreen = GameScreen::EXIT;
		}
	}
	void GameScreenMultiplayer(SoundsGame& soundsGame, Bird& bird,Bird& bird2, Wall& firstWall, Wall& secondWall, bool& isPaused, bool& isGameOver, GameRectangleButton& gameButtons, GameTextures& gameTextures, GameScreen& currentScreen, Vector2 mouse)
	{
		if (isPaused)
		{
			static bool pauseSound = false;
			if (!pauseSound)
			{
				PlaySound(soundsGame.pause);
				pauseSound = true;
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.backButton.isSelected == true)
			{
				InitBird(bird);
				InitBird(bird2);
				ResetWall(firstWall, secondWall);
				pauseSound = false;
				currentScreen = GameScreen::MENU;
				isPaused = false;
			}
			else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.continueButton.isSelected == true)
			{
				isPaused = false;
				pauseSound = false;

			}
			else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.restartButton.isSelected == true)
			{
				InitBird(bird2);
				ResetWall(firstWall, secondWall);
				isPaused = false;
				pauseSound = false;

			}

		}
		if (isGameOver)
		{
			static bool hasPlayedLoseSound = false;

			DrawText(TextFormat(" Score: %i", bird.score), 0, 0, 40, WHITE);
			if (!hasPlayedLoseSound)
			{
				PlaySound(soundsGame.lose);
				hasPlayedLoseSound = true;
			}
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.backButton.isSelected == true)
			{
				
				currentScreen = GameScreen::MENU;
				isGameOver = false;
				hasPlayedLoseSound = false;
				InitBird(bird);
				InitBird(bird2);
				ResetWall(firstWall, secondWall);

			}
			else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.restartButton.isSelected == true)
			{
				
				isGameOver = false;
				hasPlayedLoseSound = false;
				RestartBird(bird);
				RestartBird(bird2);
				ResetWall(firstWall, secondWall);

			}
		}
		if (IsKeyPressed(KEY_ESCAPE))
		{
			isPaused = !isPaused;
			PlaySound(soundsGame.pause);
		}
		else
		{
			UpdateWall(firstWall, isPaused, isGameOver);
			UpdateWall(secondWall, isPaused, isGameOver);
			UpdateBird(bird, isPaused, isGameOver, firstWall, secondWall);
			UpdateBird_2(bird2, isPaused, isGameOver, firstWall, secondWall);
			drawGame(gameTextures.background, gameTextures.midground, gameTextures.foreground, gameTextures.tree, gameTextures.bushTop, gameTextures.bushDown, isPaused, isGameOver);
			DrawBird(bird, isPaused);
			DrawBird(bird2, isPaused);
			DrawWall(firstWall);
			DrawWall(secondWall);
			PauseScreen(gameButtons,mouse,isPaused);
			GameOverScreen(gameButtons, mouse, isGameOver, bird);
			DrawText(TextFormat(" Score: %i", bird.score), 0, 0, 40, WHITE);

		}
	}
	void GameScreenSingleplayer(SoundsGame& soundsGame,Bird& bird, Wall& firstWall, Wall& secondWall,bool &isPaused, bool& isGameOver, GameRectangleButton& gameButtons, GameTextures& gameTextures, GameScreen& currentScreen, Vector2 mouse)
	{
		if (isPaused)
		{
			static bool pauseSound = false;
			if (!pauseSound)
			{
				PlaySound(soundsGame.pause);
				pauseSound = true;
			}
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.backButton.isSelected == true)
			{
				InitBird(bird);
				ResetWall(firstWall, secondWall);

				pauseSound = false;
				currentScreen = GameScreen::MENU;
				isPaused = false;
			}
			else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.continueButton.isSelected == true)
			{
				isPaused = false;
				pauseSound = false;
			}
			else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.restartButton.isSelected == true)
			{
				pauseSound =false;
				InitBird(bird);
				ResetWall(firstWall, secondWall);
				isPaused = false;

			}

		}
		if (isGameOver)
		{
			static bool hasPlayedLoseSound = false;
			

			
			DrawText(TextFormat("Score: %i", bird.score), 0, 0, 40, WHITE);


			if (!hasPlayedLoseSound)
			{
				PlaySound(soundsGame.lose);
				hasPlayedLoseSound = true;
			}
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.backButton.isSelected == true)
			{
				
				currentScreen = GameScreen::MENU;
				isGameOver = false;
				hasPlayedLoseSound = false;
				InitBird(bird);
				ResetWall(firstWall, secondWall);

			}
			else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.restartButton.isSelected == true)
			{
				bird.score = bird.score;
				isGameOver = false;
				hasPlayedLoseSound = false;
				RestartBird(bird);
				ResetWall(firstWall, secondWall);


			}
		}
		if (IsKeyPressed(KEY_ESCAPE))
		{
			isPaused=!isPaused;
			PlaySound(soundsGame.pause);
		}
		else
		{
			UpdateWall(firstWall, isPaused,isGameOver);
			UpdateWall(secondWall,isPaused,isGameOver);
			UpdateBird(bird, isPaused, isGameOver, firstWall,secondWall);
			drawGame(gameTextures.background,gameTextures.midground, gameTextures.foreground, gameTextures.tree, gameTextures.bushTop, gameTextures.bushDown, isPaused, isGameOver);
			DrawBird(bird,isPaused);
			DrawWall(firstWall);
			DrawWall(secondWall);
			PauseScreen(gameButtons, mouse, isPaused);
			GameOverScreen(gameButtons,mouse,isGameOver, bird);
			DrawText(TextFormat(" Score: %i", bird.score), 0, 0, 40, WHITE);
			cout << bird.score << endl;
			
		}	
	}
	void GameScreenRules(GameRectangleButton& gameButtons, GameScreen& currentScreen, Vector2& mouse)
	{
		drawRules(gameButtons.backButton, mouse);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.backButton.isSelected == true)
		{
			currentScreen = GameScreen::MENU;
			

		}
	}
	void GameScreenCredits(GameRectangleButton& gameButtons, GameScreen& currentScreen, Vector2& mouse)
	{
		drawCredits(gameButtons.backButton, mouse);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameButtons.backButton.isSelected == true)
		{
			currentScreen = GameScreen::MENU;
		}
	}
	
}

