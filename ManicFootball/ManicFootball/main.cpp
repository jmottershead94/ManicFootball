// Network Programming Coursework by Jason Mottershead, Student Number 1300455.
// This project will use the SFML library, I am not the creator of the SFML library.
// Credit to the SFML team and developers.

// Include files here.
#include "game.h"

// The main function.
void main()
{

	// Initialising a game window with a resolution of 1280 x 720.
	Game game(1280.0f, 720.0f);

	// The main game loop runs from here.
	// While the game window is open/in use.
	while (game.getWindow()->isOpen())
	{
		// Update the game.
		game.Update();

		// Render the game.
		game.Render();
	}

}