// Network Programming Coursework by Jason Mottershead, Student Number 1300455.
// This project will use the SFML library and Box2D physics library, as well as a cubic spline header file.
// Credit to the SFML team and developers for SFML.
// Credit to Erin Catto for Box2D.
// Credit to Tino Kluge for tk_spline.

// Include files here.
#include "game.h"

// The main function.
void main()
{

	// Initialising a game window with a resolution of 1280 x 720.
	Game game(1280, 720);

	// The main game loop runs from here.
	// While the game window is open/in use.
	while (true)
	{
		// Update the game.
		game.Update();
	}

}