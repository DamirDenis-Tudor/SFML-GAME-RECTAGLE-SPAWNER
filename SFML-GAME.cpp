/*
	Concepts:
	-> update game cycle :
		1. process input and events ; example : it takes a keyboard command
		2. update the game state ; example : take that command and makes player to move
		3. render the frame of current game state

	-rendering : the process of drawing a frame to the screen ;
*/

#include "game_engine.h"

int main()
{
	//init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//init game
	Game myGame;
	

	/*
		create the GameLoop
			- mantain the window open
			- update ; " eveniments while eye are closed "
			- render ; " open the eyes "
	*/

	while ( myGame.windowIsOpen() && !myGame.endGameEv() )
	{
		//game update
		myGame.update();

		//game render
		myGame.render();

	}

	return 0;
}

