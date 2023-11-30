#pragma once
#include"raylib.h"
#include"utilsManager/rectangleButton.h"
#include"screenManager/screenGameplay.h"
namespace game
{
	struct GameTextures
	{
		    Texture2D foreground ;
			Texture2D midground  ;
			Texture2D background ;
			Texture2D  tree      ;
			Texture2D bushTop 	 ;
			Texture2D bushDown	 ;
			Texture2D texBirdOne ;
			Texture2D texBirdTwo ;
	};

	struct GameRectangleButton
	{
		RectangleButton playButton ;
		RectangleButton multiplayerButton ;
		RectangleButton backButton ;
		RectangleButton rulesButton ;
		RectangleButton creditsButton ;
		RectangleButton exitButton;
		RectangleButton continueButton ;
		RectangleButton creditsOne;
		RectangleButton creditsTwo ;
		RectangleButton creditsThree ;
		RectangleButton creditsFour ;
		RectangleButton restartButton ;

	};
	struct SoundsGame
	{
		Sound jumpSound;
		Sound fallSound;
		Sound loseLife;
		Sound lose;
	};
	
	void runGame();
	

}