// Network Programming Coursework by Jason Mottershead, Student Number 1300455.
// This project will use the SFML library and Box2D physics library.
// Credit to the SFML team and developers for SFML.
// Credit to Erin Catto for Box2D.

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