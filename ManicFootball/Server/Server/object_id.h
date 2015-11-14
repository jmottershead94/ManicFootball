// Jason Mottershead, 1300455.

// Object ID header file.
// This is not a class, but just a header file containing some information.
// The information provides ID's to objects in the game.
// This will be used for identifying certain collisions, and creating the game objects.

// Header guard.
#ifndef _OBJECT_ID_H_
#define _OBJECT_ID_H_

// Object ID enum.
enum ObjectID
{

	playerOne = 0,
	playerTwo,
	enemy,
	ball,
	surface,
	redNet,
	blueNet
	
};

#endif